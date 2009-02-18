#include "japeEngine.h"
#include <stdio.h>
#include <malloc.h>
#include <cstdlib>
#include <assert.h>
#include <gc/gc.h>

float particleGravity = -0.0001f;
bool globalGravity;
float fadeAmount = 1000.0f;

int japeEmitter::createParticles(int numParticles, float x, float y, float z)
{
	pointx = x;
	pointy = y;
	pointz = z;	
	
	particleCount = numParticles;
    particles = new japeParticle[particleCount + 1];
	
	for(int pCount = 0; pCount < numParticles; pCount++)
	{
		if(type == JAPE_POINT)
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
			particles[pCount].life = 0;
		}
		else if(type == JAPE_EXPLOSION)
		{
			particles[pCount].posx = x;
			particles[pCount].posy = y;
			particles[pCount].posz = z;
		
			particles[pCount].accx = 0;
			if(globalGravity)
			{
				particles[pCount].accy = particleGravity;
			}
			else if(!globalGravity)
			{
				particles[pCount].accy = 0;
			}
			particles[pCount].accz = 0;
		
			particles[pCount].velx = 1 + rand() % 100;
			particles[pCount].velx -= EmitterProperties.xdir;
			particles[pCount].velx /= EmitterProperties.xspeed;
	
			particles[pCount].vely = 1 + rand() % 100;
			particles[pCount].vely -= EmitterProperties.ydir;
			particles[pCount].vely /= EmitterProperties.yspeed;
	
			particles[pCount].velz = 1 + rand() % 100;
			particles[pCount].velz -= EmitterProperties.zdir;
			particles[pCount].velz /= EmitterProperties.zspeed;
	
			particles[pCount].colr = EmitterProperties.colr;
			particles[pCount].colg = EmitterProperties.colg;
			particles[pCount].colb = EmitterProperties.colb;
	
			particles[pCount].life = 5.0f;
			particles[pCount].fade = float(rand() % 100) / 1000.0f + 0.003f;
		}
	}
	
	particleCount = numParticles;
}

void japeEmitter::texture(char *filename, float size)
{
	pngInfo info;
	
	EmitterProperties.texsize = size;
	
	textureID = pngBind(filename, PNG_NOMIPMAP, PNG_ALPHA, &info, GL_CLAMP, GL_NEAREST, GL_NEAREST);
	if(textureID == 0) 
	{
		printf(" Can't load file %s\n", filename);
		//exit(1);
	}

	printf(" Properties of '%s' : Size = %ix%i Depth = %i Alpha = %i\n", filename, info.Width, info.Height, info.Depth, info.Alpha);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(0, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void japeEmitter::colorParticles(float r, float g, float b)
{
	for(int x = 0; x < particleCount; x++)
	{	
		particles[x].colr = r;
		particles[x].colg = g;
		particles[x].colb = b;
		
		EmitterProperties.colr = r;
		EmitterProperties.colg = g;
		EmitterProperties.colb = b;
	}
}

void japeEmitter::updateParticles(bool gravity)
{
	globalGravity = gravity;


	for(int y = 0; y < particleCount; y++)
	{
		particles[y].posx += particles[y].velx;
		particles[y].posy += particles[y].vely;
		particles[y].posz += particles[y].velz;
		//
		particles[y].velx += particles[y].accx;
		particles[y].vely += particles[y].accy;
		particles[y].velz += particles[y].accz;
	
		particles[y].life -= particles[y].fade;
		
		if(enabled)
		{
			if(particles[y].life < 0)
			{
				particles[y].posx = pointx;
				particles[y].posy = pointy;
				particles[y].posz = pointz;
			
				particles[y].accx = 0;
				if(gravity)
				{
					particles[y].accy = particleGravity;
				}
				else if(!gravity)
				{
					particles[y].accy = 0;
				}
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
				particles[y].fade = float(rand() % 100) / fadeAmount + 0.003f;
			}
		}		
	}
}

void japeEmitter::drawParticles()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	if(EmitterProperties.texsize != 0)
	{
		glBegin(GL_QUADS);
		for(int i = 0; i < particleCount; i++)
		{		
			glColor4f(particles[i].colr, particles[i].colg, particles[i].colb, particles[i].life);
			
				glTexCoord2f(0.0f, 0.0f); glVertex3f(particles[i].posx - EmitterProperties.texsize, particles[i].posy - EmitterProperties.texsize,  particles[i].posz);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(particles[i].posx + EmitterProperties.texsize, particles[i].posy - EmitterProperties.texsize,  particles[i].posz);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(particles[i].posx + EmitterProperties.texsize, particles[i].posy + EmitterProperties.texsize,  particles[i].posz);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(particles[i].posx - EmitterProperties.texsize, particles[i].posy + EmitterProperties.texsize,  particles[i].posz);
			
		}
		glEnd();
	}
	else
	{
		for(int z = 0; z < particleCount; z++)
		{	
			glPointSize(5);
			glColor4f(particles[z].colr, particles[z].colg, particles[z].colb, particles[z].life);
			glBegin(GL_POINTS);
				glVertex3f(particles[z].posx, particles[z].posy, particles[z].posz);
			glEnd();
		}
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
