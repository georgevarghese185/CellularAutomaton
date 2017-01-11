#include<GL\freeglut.h>
#include<string>
#include"ViewStart.h"

using namespace std;

GLsizei WindowWidth, WindowHeight;		//global variables for width and height
string ExecDir;							//global variable. holds current directory of .exe

int main(int argc, char** argv)
{
	ExecDir = argv[0];					//initially, path to .exe stored in ExecDir
	while (1)
	{
		if (ExecDir.back() == '\\' || ExecDir.back() == '/')	//starting from the end of .exe's path, find the first '/'. that gives
			break;												//us the current directory's path
		else
			ExecDir.pop_back();
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Cellular Automaton 3.0");
	WindowWidth = 800; WindowHeight = 600;
	glutPositionWindow(10, 10);

	ViewStart::HandOver();										//Hand over control to ViewStart.

	glutMainLoop();
	return 0;
}