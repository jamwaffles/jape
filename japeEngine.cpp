#include "japeEngine.h"
#include <stdio.h>
#include <malloc.h>
#include <cstdlib>

float particleGravity = 0.0001f;

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
		
		particles[pCount].velx = 0;
		particles[pCount].vely = 0;
		particles[pCount].velz = 0;
		
		particles[pCount].accx = 1 + rand() % 100;
		particles[pCount].accx -= 50;
		particles[pCount].accx /= 10000;
		
		particles[pCount].accy = 1 + rand() % 100;
		particles[pCount].accy -= 50;
		particles[pCount].accy /= 10000;
		
		particles[pCount].accz = 1 + rand() % 100;
		particles[pCount].accz -= 50;
		particles[pCount].accz /= 10000;
		
		particles[pCount].colr = 0;
		particles[pCount].colg = 0;;
		particles[pCount].colb = 0;
		
		particles[pCount].fade = 1 + rand() % 100;
		particles[pCount].fade /= 1000;
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
		particles[y].vely += particles[y].accy - particleGravity;
		particles[y].velz += particles[y].accz;
		
		particles[y].life -= particles[y].fade;
		
		if(particles[y].life <= 0)
		{
			particles[y].posx = pointx;
			particles[y].posy = pointy;
			particles[y].posz = pointz;
		
			particles[y].velx = 0;
			particles[y].vely = 0;
			particles[y].velz = 0;
		
			particles[y].accx = 1 + rand() % 100;
			particles[y].accx -= 50;
			particles[y].accx /= 100000;
		
			particles[y].accy = 1 + rand() % 100;
			particles[y].accy -= 50;
			particles[y].accy /= 100000;
		
			particles[y].accz = 1 + rand() % 100;
			particles[y].accz -= 50;
			particles[y].accz /= 100000;
		
			particles[y].colr = 1;
			particles[y].colg = 1;
			particles[y].colb = 1;
		
			particles[y].fade = 1 + rand() % 100;
			particles[y].fade /= 1000;
			particles[y].life = 1;
		}
	}
}

void japeEmitter::drawParticles()
{
	for(int i = 0; i <= particleCount; i++)
	{	
		glPointSize(5);
		glColor3f(particles[i].colr, particles[i].colg, particles[i].colb);
		glBegin(GL_POINTS);
			glVertex3f(particles[i].posx, particles[i].posy, particles[i].posz);
		glEnd();
	}
}

void japeEmitter::randSet(int vel, int acc)
{
	/*for(int z = 0; z <= particleCount; z++)
	{	
		particles[z].posx = float((rand() % vel) / 10000);
		particles[z].posy = float((rand() % vel) / 10000);
		particles[z].posz = float((rand() % vel) / 10000);
		
		particles[z].accx = float((rand() % acc) / 10000);
		particles[z].accy = float((rand() % acc) / 10000);
		particles[z].accz = float((rand() % acc) / 10000);
	}*/
}

void japeEmitter::movePoint(float x, float y, float z)
{
	pointx = x;
	pointy = y;
	pointz = z;
}
