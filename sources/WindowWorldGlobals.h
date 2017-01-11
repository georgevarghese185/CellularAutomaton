#pragma once
#include<GL\glut.h>
#include<math.h>

extern GLsizei WindowWidth, WindowHeight;
extern double VRwidth, VRheight;
extern double WHRatio;

void WindowToWorldCoordinates(double &x, double &y);

void Reshape(int w, int h);
