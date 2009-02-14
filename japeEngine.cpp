#include "japeEngine.h"
#include <stdio.h>
#include <malloc.h>
#include <cstdlib>

float particleGravity = -0.0001f;

int japeEmitter::createParticles(int numParticles, float x, float y, float z)
{
	pointx = x;
	pointy = y;
	pointz = z;

	malloc(sizeof(japeParticle[numParticles]));
	particles = new japeParticle[numParticles];
	
	for(int pCount = 0; pCount <= numParticles; pCount++)
	{
		particles[pCount].posx = x;
		particles[pCount].posy = y;
		particles[pCount].posz = z;
		
		particles[pCount].accx = 0;
		particles[pCount].accy = 0;
		particles[pCount].accz = 0;
		
		particles[pCount].velx = 0;
		particles[pCount].vely = 0;
		particles[pCount].velz = 0;
		
		particles[pCount].colr = 0;
		particles[pCount].colg = 0;;
		particles[pCount].colb = 0;
		
		particles[pCount].fade = 1 + rand() % 100;
		particles[pCount].life = 1;
	}
	
	particleCount = numParticles;
}

void japeEmitter::colorParticles(float r, float g, float b)
{
	for(int x = 0; x <= particleCount; x++)
	{	
		particles[x].colr = r;
		particles[x].colg = g;
		particles[x].colb = b;
		
		EmitterProperties.colr = r;
		EmitterProperties.colg = g;
		EmitterProperties.colb = b;
	}
}

void japeEmitter::updateParticles()
{
	for(int y = 0; y <= particleCount; y++)
	{	
		particles[y].posx += particles[y].velx;
		particles[y].posy += particles[y].vely;
		particles[y].posz += particles[y].velz;
		//
    	particles[y].velx += particles[y].accx;
		particles[y].vely += particles[y].accy;
		particles[y].velz += particles[y].accz;
		
		particles[y].life -= particles[y].fade;
		
		if(particles[y].life < 0)
		{
			particles[y].posx = pointx;
			particles[y].posy = pointy;
			particles[y].posz = pointz;
			
			particles[y].accx = 0;
			particles[y].accy = particleGravity;
			particles[y].accz = 0;
		
			particles[y].velx = 1 + rand() % 100;
			particles[y].velx -= EmitterProperties.xdir;
			particles[y].velx /= EmitterProperties.xspeed;
		
			particles[y].vely = 1 + rand() % 100;
			particles[y].vely -= EmitterProperties.ydir;
			particles[y].vely /= EmitterProperties.yspeed;
		
			particles[y].velz = 1 + rand() % 100;
			particles[y].velz -= EmitterProperties.zdir;
			particles[y].velz /= EmitterProperties.zspeed;
		
			particles[y].colr = EmitterProperties.colr;
			particles[y].colg = EmitterProperties.colg;
			particles[y].colb = EmitterProperties.colb;
		
			particles[y].life = 5.0f;
			particles[y].fade = float(rand() % 100) / 1000.0f + 0.003f;
		}
	}
}

void japeEmitter::drawParticles()
{
	for(int i = 0; i <= particleCount; i++)
	{	
		glPointSize(5);
		glColor4f(particles[i].colr, particles[i].colg, particles[i].colb, particles[i].life);
		glBegin(GL_POINTS);
			glVertex3f(particles[i].posx, particles[i].posy, particles[i].posz);
		glEnd();
	}
}

void japeEmitter::movePoint(float x, float y, float z)
{
	pointx = x;
	pointy = y;
	pointz = z;
}

void japeEmitter::vectorParticles(float x, float y, float z)
{
	/*x *= 100;
	y *= 100;
	z *= 100;*/

	EmitterProperties.xdir = x;
	EmitterProperties.ydir = y;
	EmitterProperties.zdir = z;
}

void japeEmitter::speedParticles(float x, float y, float z)
{
	EmitterProperties.xspeed = x;
	EmitterProperties.yspeed = y;
	EmitterProperties.zspeed = z;
}
