#include"WindowWorldGlobals.h"

GLsizei WindowWidth, WindowHeight;
double VRwidth, VRheight;
double WHRatio;

void WindowToWorldCoordinates(double &x, double &y)
{
	int Padding = abs((int)(WindowWidth - WindowHeight * WHRatio)) / 2;
	if (WindowHeight * WHRatio <= WindowWidth)
	{
		x = (x - Padding) / (float)(WindowHeight * WHRatio) * VRwidth;
		y = VRheight - y / (float)WindowHeight * VRheight;
	}
	else
	{
		x = x / (float)WindowWidth * VRwidth;
		y = VRheight - (y - Padding) / (float)WindowWidth * VRheight;
	}
}

void Reshape(int w, int h)
{
	WindowWidth = w;
	WindowHeight = h;
	if (h * WHRatio <= w)

		glViewport((w / 2) - (h * WHRatio / 2), 0, h * WHRatio, h);
	else

		glViewport(0, (h / 2) - ((w / WHRatio) / 2), w, w / WHRatio);
	glutPostRedisplay();
}