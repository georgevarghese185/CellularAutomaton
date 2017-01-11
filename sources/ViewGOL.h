#ifndef __VIEWGOL_H_INCLUDED
#define __VIEWGOL_H_INCLUDED

#include<GL\freeglut.h>
#include<string>
#include<ctime>
#include<iostream>
#include"ViewMainMenu.h"
#include"ViewAutomaton.h"
#include"Textures.h"
using namespace std;

extern string ExecDir;
extern GLsizei WindowWidth, WindowHeight;

namespace ViewGOL
{
	
	extern double VRwidth, VRheight;
	extern const double WHRatio;
	extern GLuint listsBase, continueButtonPressed, continueButtonReleased, backButtonPressed, backButtonReleased, inputBox;
	extern GLsizei numOfLists;
	extern int showCursor;
	extern string input;
	extern clock_t startTimer;
	extern Textures *tex;

	void HandOver();
	void Reshape(int w, int h);
	void Initialize();
	void Display();
	void DummyDisplay();
	void CursorBlink();
	void Key(unsigned char key, int x, int y);		//For entering grid size
	void exitGOL();

	namespace Mouse
	{
		void Mouse(int button, int state, int x, int y);
		int ButtonPressCheck(int x, int y);
	}

	namespace Draw
	{
		extern int backButtonDown, continueButtonDown, backButtonDown;

		void Text();
		inline void ScaleAbout(GLfloat x, GLfloat y, GLfloat xScale, GLfloat yScale);
		void Buttons();
	}
}

#endif
