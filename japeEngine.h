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

class japeEmitter
{	
	japeParticle *particles;				//i obviously need this to do something with or i get errors
	int particleCount;						//global variable to store number of particles from japeEmitter::createParticles()
	float pointx, pointy, pointz;
	
	public:
		int createParticles(int numParticles, float x, float y, float z);
		void colorParticles(float r, float g, float b);
		void updateParticles(void);
		void drawParticles(void);
		void randSet(int vel, int acc);
		void movePoint(float x, float y, float z);
};
