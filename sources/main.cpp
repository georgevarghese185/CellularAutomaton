#include<GL\freeglut.h>
#include"ViewAutomaton.h"	//Holds Automaton View Mode
#include"ViewStart.h"

int MainWindow;
string ExecDir;

int main(int argc, char** argv)

{
	ExecDir = argv[0];
	while (1)
	{
		if (ExecDir.back() == '\\' || ExecDir.back() == '/')
			break;
		else
			ExecDir.pop_back();
	}

	glutInit(&argc, argv);							//
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);	//Initializing
	
	MainWindow=glutCreateWindow("Cellular Automaton 2.1");
	
	glutHideWindow();

	ViewStart::HandOver();				//Handover Control to Automaton View

	glutMainLoop();									//Loop event.

	return 0;
}