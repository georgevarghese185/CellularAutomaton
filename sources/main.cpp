#include<GL\freeglut.h>
#include"ViewAutomaton.h"	//Holds Automaton View Mode
#include"ViewStart.h"

int MainWindow;

int main(int argc, char** argv)

{
	glutInit(&argc, argv);							//
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);	//Initializing
	
	MainWindow=glutCreateWindow("Cellular Automaton 2.0");
	glutHideWindow();

	ViewStart::HandOver();				//Handover Control to Automaton View

	glutMainLoop();									//Loop event.

	return 0;
}