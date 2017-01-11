#ifndef __BUTTONS_H_INCLUDED
#define __BUTTONS_H_INCLUDED

#include<GL\freeglut.h>
#include<iostream>
#include"Textures.h"
using namespace std;

GLubyte * Color(GLubyte R, GLubyte G, GLubyte B);

class Buttons
{
protected:
	int _numOfButtons;
	bool *_buttonDown;
	GLfloat **_buttonBorders,**_buttonCenter;
	GLuint **_buttonGraphic, *_button;

public:
	Buttons(int numOfButtons);
	void MakeButton(int buttonName, GLfloat X0, GLfloat Y0, GLfloat X1, GLfloat Y1, GLuint buttonGraphic);
	void MakeButtonGraphic(int buttonName,
		GLfloat outerX0, GLfloat outerY0, GLfloat outerX1, GLfloat outerY1,
		GLfloat innerX0, GLfloat innerY0, GLfloat innerX1, GLfloat innerY1,
		GLubyte *innerPressed, GLubyte *topPressed, GLubyte *bottomPressed, GLubyte *leftPressed, GLubyte *rightPressed,
		GLubyte *innerReleased, GLubyte *topReleased, GLubyte *bottomReleased, GLubyte *leftReleased, GLubyte *rightReleased);
	
	int PressButton(int x, int y);
	void ReleaseButtons();

	void DrawButton(int buttonName, int label, Textures *t);
	~Buttons();
};

#endif

