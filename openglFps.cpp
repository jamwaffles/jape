#include "openglFps.h"
#include <stdio.h>
#include <GL/glut.h>

int frame, time, timebase = 0;
char s[30];

void printFps()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if(time - timebase > 100) 
	{
		sprintf(s, "FPS: %4.2f", frame * 1000.0 / (time - timebase));
		timebase = time;		
		frame = 0;
	}
	
	fontSet(GLUT_BITMAP_HELVETICA_10);
	fontDraw(s, 1, 11);
}
