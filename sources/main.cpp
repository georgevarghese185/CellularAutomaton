#include<GL\glut.h>
#include"ViewAutomaton.h"	//Holds Automaton View Mode
#include"ViewStart.h"

int main(int argc, char** argv)

{
	glutInit(&argc, argv);							//
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//Initializing
	
	glutCreateWindow("Cellular Automaton 1.3");
	glutHideWindow();

	ViewStart::HandOver();				//Handover Control to Automaton View

	glutMainLoop();									//Loop event.

	return 0;
}