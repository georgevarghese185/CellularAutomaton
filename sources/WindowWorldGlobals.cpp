#include"WindowWorldGlobals.h"

GLint WindowWidth, WindowHeight;
double VRwidth, VRheight;
double WidthHeightRatio;

void WindowToWorldCoordinates(double &x, double &y)
{
	int Padding = abs((int)(WindowWidth - WindowHeight * WidthHeightRatio)) / 2;
	if (WindowHeight * WidthHeightRatio <= WindowWidth)
	{
		x = (x - Padding) / (float)(WindowHeight * WidthHeightRatio) * VRwidth;
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
	if (h * WidthHeightRatio <= w)

		glViewport((w / 2) - (h * WidthHeightRatio / 2), 0, h * WidthHeightRatio, h);
	else

		glViewport(0, (h / 2) - ((w / WidthHeightRatio) / 2), w, w / WidthHeightRatio);
	glutPostRedisplay();
}