#ifndef __VIEWDEMO_H_INCLUDED
#define __VIEWDEMO_H_INCLUDED

#include<GL\freeglut.h>
#include<ctime>
#include<Windows.h>
#include"ViewMainMenu.h"
#include"Cells.h"
#include"Textures.h"
#include"Buttons.h"

extern string ExecDir;
extern GLsizei WindowWidth, WindowHeight;

namespace ViewDemo
{
	extern double VRwidth, VRheight;
	extern double const WHRatio;
	extern GLuint numOfLists, listsBase, cell;
	extern Textures *tex;
	extern Buttons *buttons;
	extern Cell cm;
	extern clock_t timerStart;

	void HandOver();
	void Reshape(int w, int h);
	void Initialize();
	void MakeGrid();
	void Display();
	void DummyDisplay();
	void exitDemo();

	void Mouse(int button, int state, int x, int y);

	namespace Draw
	{
		extern int Page, Page2FirstRun, Page4FirstRun, Page5FirstRun;

		void Page2();
		void Page4();
		void Page5();
		void FilledCells();
		void TextBox();
		void Text();
	}
}

#endif