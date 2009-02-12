#include <stdio.h>
#include <stdlib.h>

#include "openglTerminal.h"
#include "openglFrameTimer.h"
#include "openglFps.h"
#include "japeEngine.h"

unsigned int g_persp = 0, g_ortho = 0;
float angle = 0.0;
int windowWidth = 800, windowHeight = 600;
bool showTerminal;

japeEmitter Emitter;
openglTerminal Terminal;

void japeInit()
{
	Emitter.createParticles(100);
	Emitter.colorParticles(1, 1, 1);
}

void openglIdle()
{
	// update the frame time
	SortFrameTimer();

	//	if our prog runs at 50fps, each frame should take 0.02 secs.
	// 	If we want a value to increase by 10 units in one second,
	//	then each frame we need to increment the value by 0.2 units
	//
	//		Increment Size =  10 units / 50 fps
	//
	// 	Since 1 sec / 50 fps  == FrameTime, we can say
	//
	//		Increment Size = 10 * 1/50 fps
	// 		Increment Size = 10 * FrameTime
	//
	//	In this case, we increment the rotation value by 90
	// 	units per second
	//
	//g_Rotation += 90.0f * FrameTime(); 						variables here
	angle += 90 * FrameTime();

	Emitter.updateParticles();

	// redraw the screen
	glutPostRedisplay();
}

void openglReshape(int w, int h) 
{
	windowWidth = w;
	windowHeight = h;
	if(h == 0) 
	{
		h = 1;
	}

	// delete the last display lists
	glDeleteLists(g_persp, 1);
	glDeleteLists(g_ortho, 1);

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// generate new display list ID's
	g_persp = glGenLists(1);
	g_ortho = glGenLists(1);

	// generate perspective display list
	glNewList(g_persp, GL_COMPILE);

		// set up the projection matrix 
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// just use a perspective projection
		gluPerspective(45, (float)w / h, 0.1, 100);

		// go back to modelview matrix so we can move the objects about
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

	glEndList();


	// generate orthographic display list
	glNewList(g_ortho, GL_COMPILE);

		// set up the projection matrix 
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// just use a orthographic projection
		glOrtho(0, w, h, 0, -100, 100);

		// go back to modelview matrix so we can move the objects about
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

	glEndList();
}


void openglDraw(void) 
{	
	// clear the screen & depth buffer
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	// set the perspective projection
	glCallList(g_persp);

	// set the camera position
	gluLookAt(	1, 1, 10,	//	eye pos
				0, 0, 0,	//	aim point
				0, 1, 0);	//	up direction

	//3D stuff	*****************************************
	
	//glRotatef(angle, 0.0, 1.0, 0.0);

	/*glBegin(GL_TRIANGLES);
		glVertex3f(-0.5, -0.5, 0.0);
		glVertex3f(0.5, 0.0, 0.0);
		glVertex3f(0.0, 0.5, 0.0);
	glEnd();*/
	
	Emitter.drawParticles();

	// set the orthographic projection
	glCallList(g_ortho);

	//2D/text	*****************************************
	glColor4f(1.0, 1.0, 1.0, 1.0);

	if(showTerminal == true)
	{
		Terminal.showLines();
	}
	
	fontSet(GLUT_BITMAP_HELVETICA_10);
	fontDraw(printFps(), (windowWidth - 60), 11);
	
	// currently we've been drawing to the back buffer, we need
	// to swap the back buffer with the front one to make the image visible
	glutSwapBuffers();
}

void openglNormalKeys(unsigned char key, int x, int y) 
{
	switch (key) 
	{
		case 27:
			Terminal.print("Exiting JAPE");
			exit(0);
		break;
		
		case 't':
			if(showTerminal == true)
			{
				showTerminal = false;
			}
			else if(showTerminal == false)
			{
				showTerminal = true;
			}
		break;
	}
}

void openglSpecialKeys(int key, int x, int y) 
{
	switch (key) 
	{
		
	}
}

int openglInit()
{
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("JAPE Particle Engine Demo");
	glutDisplayFunc(openglDraw);
	glutIdleFunc(openglIdle);
	glutReshapeFunc(openglReshape);

	//adding here the setting of keyboard processing
	glutKeyboardFunc(openglNormalKeys);
	glutSpecialFunc(openglSpecialKeys);
	glutMainLoop();
}

int main(int argc, char **argv) 
{
	showTerminal = true;
	
	Terminal.print("JAPE-0.0.3");
	Terminal.print("Single point demo with 100 particles");
	
	Terminal.print("Initialising frame counter/timer...");
	InitFrameTimer();
	Terminal.print("Done");
	
	glutInit(&argc, argv);
	
	Terminal.print("Initialising JAPE...");
	japeInit();
	Terminal.print("Done");
	
	Terminal.print("Initialisng OpenGL window...");
	openglInit();
	Terminal.print("Done");
}

