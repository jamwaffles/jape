#include <stdio.h>
#include <GL/glut.h>
#include "openglTerminal.h"
#include "openglFont.h"
#include <cstring>
#include <iostream>
using namespace::std;



char line1[100];
char line2[100];
char line3[100];
char line4[100];
char line5[100];
char line6[100];
char line7[100];
char line8[100];
char line9[100];
char line10[100];

void openglTerminal::print(char *text, int type)
{
	char pi = 0, c;
	
	if(type == COUT || type == BOTH)
	{
		cout << " " << text; 
	}
	if(type == OPENGL || type == BOTH)
	{
    while(1)
    {
		c = text[pi++];
		if(!c)
		{
			showLines();
			break;
		}
		if(c == '\n')
		{
			strcpy(line1, line2);
			strcpy(line2, line3);
			strcpy(line3, line4);
			strcpy(line4, line5);
			strcpy(line5, line6);
			strcpy(line6, line7);
			strcpy(line7, line8);
			strcpy(line8, line9);
			strcpy(line9, line10);
			strcpy(line10, text);
		}
	}
	}
}

void openglTerminal::input(char text[100])
{
	//not implemented yet
}

void openglTerminal::showLines(void)
{
	fontSet(GLUT_BITMAP_HELVETICA_12);
	fontDraw(line1, 2, 14);
	fontDraw(line2, 2, 26);
	fontDraw(line3, 2, 38);
	fontDraw(line4, 2, 50);
	fontDraw(line5, 2, 62);
	fontDraw(line6, 2, 74);
	fontDraw(line7, 2, 86);
	fontDraw(line8, 2, 98);
	fontDraw(line9, 2, 110);
	fontDraw(line10, 2, 122);
}
