#include<GL\glut.h>
#include"ViewAutomaton.h"	//Holds Automaton View Mode


int main(int argc, char** argv)

{
	glutInit(&argc, argv);							//
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//Initializing

	ViewAutomaton::HandOver();						//Handover Control to Automaton View

	glutMainLoop();									//Loop event.

	return 0;
}