#pragma once
#include<GL\glut.h>
#include<math.h>

extern GLint WindowWidth, WindowHeight;
extern double VRwidth, VRheight;
extern double WidthHeightRatio;

void WindowToWorldCoordinates(double &x, double &y);

void Reshape(int w, int h);
