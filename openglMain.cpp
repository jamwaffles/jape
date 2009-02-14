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

japeEmitter Emitter;					//first point
japeEmitter Emitter2;					//second point
openglTerminal Terminal;				//output
bool runSim = true;						//run simulation flag
bool rotate = false;					//rotate flag

void japeInit()
{
	Emitter.createParticles(1000, -2, 0, 0);
	Emitter.vectorParticles(50, 0, 50);
	Emitter.speedParticles(10000, 4000, 10000);
	Emitter.colorParticles(1, 0, 1);
	
	Emitter2.createParticles(1000, 2, 0, 0);
	Emitter2.vectorParticles(50, 50, 50);
	Emitter2.speedParticles(10000, 10000, 10000);
	Emitter2.colorParticles(1, 1, 0);
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
	if(runSim)
	{
		if(rotate)
		{
			angle += 20 * FrameTime();
		}
	
		Emitter.updateParticles();
		Emitter2.updateParticles();	 
	}

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
	
	glRotatef(angle, 0.0, 1.0, 0.0);

	/*glBegin(GL_TRIANGLES);
		glVertex3f(-0.5, -0.5, 0.0);
		glVertex3f(0.5, 0.0, 0.0);
		glVertex3f(0.0, 0.5, 0.0);
	glEnd();*/
	
	Emitter.drawParticles();
	Emitter2.drawParticles();	

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
		case 'q':
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
		
		case 'p':
			if(runSim)
			{
				runSim = false;
				Terminal.print("Simulation paused");
			}
			else if(!runSim)
			{
				runSim = true;
				Terminal.print("Simulation resumed");
			}
		break;
		
		case 's':
			if(rotate)
			{
				rotate = false;
				Terminal.print("Rotate: no");
			}
			else if(!rotate)
			{
				rotate = true;
				Terminal.print("Rotate: yes");
			}
		break;
		
		case 'r':
			rotate = false;
			runSim = true;
			angle = 0.0f;
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

	//AA/Blending
	GLfloat values[2];
    glGetFloatv(GL_LINE_WIDTH_GRANULARITY, values);
    glGetFloatv(GL_LINE_WIDTH_RANGE, values);
    glEnable(GL_POINT_SMOOTH);
    Terminal.print("Enabling blending...");
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    Terminal.print("Done");
    glHint(GL_POINT_SMOOTH_HINT, GL_DONT_CARE);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glClearDepth(10.0f);
	glDisable(GL_DEPTH_TEST);			
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);			
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	//adding here the setting of keyboard processing
	glutKeyboardFunc(openglNormalKeys);
	glutSpecialFunc(openglSpecialKeys);
	glutMainLoop();
}

int main(int argc, char **argv) 
{
	showTerminal = true;
	
	Terminal.print("JAPE-0.0.5");
	Terminal.print("Single point demo with 2000 particles in 2 points");
	
	Terminal.print("Initialising frame counter/timer...");
	InitFrameTimer();
	Terminal.print("Done");
	
	glutInit(&argc, argv);
	
	Terminal.print("Initialising JAPE...");
	japeInit();
	Terminal.print("Done");
	
	Terminal.print("Initialisng OpenGL window...");
	Terminal.print("Done");
	openglInit();
}

