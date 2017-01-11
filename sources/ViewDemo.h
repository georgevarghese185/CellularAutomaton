#ifndef __VIEWDEMO_H_INCLUDED
#define __VIEWDEMO_H_INCLUDED

#include<GL\freeglut.h>
#include<ctime>
#include<Windows.h>
#include"ViewMainMenu.h"
#include"Cells.h"
#include"Textures.h"

extern string ExecDir;
extern GLsizei WindowWidth, WindowHeight;

namespace ViewDemo
{
	extern double VRwidth, VRheight;
	extern double const WHRatio;
	extern GLuint numOfLists, listsBase, cell, buttonReleased, buttonPressed, backButtonPressed, backButtonReleased;
	extern Textures *tex;
	extern Cell cm;
	extern clock_t timerStart;

	void HandOver();
	void Reshape(int w, int h);
	void Initialize();
	void MakeGrid();
	void Display();
	void DummyDisplay();
	void exitDemo();

	namespace Mouse
	{
		void Mouse(int button, int state, int x, int y);
		int ButtonPressCheck(int x, int y);
	}

	namespace Draw
	{
		extern int prevButtonDown, nextButtonDown, backButtonDown, Page, Page2FirstRun, Page4FirstRun, Page5FirstRun;

		void Page2();
		void Page4();
		void Page5();
		void FilledCells();
		void TextBox();
		void Text();
		inline void ScaleAbout(GLfloat x, GLfloat y, GLfloat xScale, GLfloat yScale);
		void Buttons();
	}
}

#endif