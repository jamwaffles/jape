#include "japeEngine.h"
#include <stdio.h>
#include <malloc.h>
#include <cstdlib>

int japeEmitter::createParticles(int numParticles)
{
	malloc(sizeof(japeParticle[numParticles]));
	particles = new japeParticle[numParticles];
	
	for(int pCount = 0; pCount <= numParticles; pCount++)
	{
		particles[pCount].posx = 0;
		particles[pCount].posy = 0;
		particles[pCount].posz = 0;
		
		particles[pCount].velx = 0;
		particles[pCount].vely = 0;
		particles[pCount].velz = 0;
		
		particles[pCount].accx = 0;
		particles[pCount].accy = 0;
		particles[pCount].accz = 0;
		
		particles[pCount].colr = 0;
		particles[pCount].colg = 0;
		particles[pCount].colb = 0;
		
		particles[pCount].fade = 0;
		particles[pCount].life = 0;
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
		particles[y].vely += particles[y].accy;
		particles[y].velz += particles[y].accz;
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
