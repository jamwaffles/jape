#include <GL/glut.h>
#include <iostream>
using namespace::std;

typedef struct
{
	float posx, posy, posz;
	float velx, vely, velz;
	float accx, accy, accz;
	float colr, colg, colb;
	
	float life;
	float fade;
}
japeParticle;

typedef struct
{
	float xdir, ydir, zdir;
	float xspeed, yspeed, zspeed;
	float colr, colg, colb;
}
japeEmitterProperties;

class japeEmitter
{	
	japeParticle *particles;				//i obviously need this to do something with or i get errors
	japeEmitterProperties EmitterProperties;
	int particleCount;						//global variable to store number of particles from japeEmitter::createParticles()
	float pointx, pointy, pointz;
	
	public:
		int createParticles(int numParticles, float x, float y, float z);
		void colorParticles(float r, float g, float b);
		void updateParticles(void);
		void drawParticles(void);
		void randSet(int vel, int acc);
		void movePoint(float x, float y, float z);
		void vectorParticles(float x, float y, float z);
		void speedParticles(float x, float y, float z);
};
