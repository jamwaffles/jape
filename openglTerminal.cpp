#include <stdio.h>
#include <GL/glut.h>
#include "openglTerminal.h"
#include "openglFont.h"
#include <iostream>
using namespace::std;

char line1[50];
char line2[50];
char line3[50];
char line4[50];
char line5[50];
char line6[50];
char line7[50];
char line8[50];
char line9[50];
char line10[50];

void openglTerminal::print(char text[50])
{
	sprintf(line1, "%s", line2);
	sprintf(line2, "%s", line3);
	sprintf(line3, "%s", line4);
	sprintf(line4, "%s", line5);
	sprintf(line5, "%s", line6);
	sprintf(line6, "%s", line7);
	sprintf(line7, "%s", line8);
	sprintf(line8, "%s", line9);
	sprintf(line9, "%s", line10);
	sprintf(line10, "%s", text);
	
	cout << " " << text << "\n";
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
