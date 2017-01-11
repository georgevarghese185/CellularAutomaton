#ifndef __VIEWCUSTOM_H_INCLUDED
#define __VIEWCUSTOM_H_INCLUDED

#include<GL\freeglut.h>
#include<string>
#include<iostream>
#include"Cells.h"
#include"ViewMainMenu.h"
#include"Textures.h"

using namespace std;

extern string ExecDir;
extern GLsizei WindowWidth, WindowHeight;

namespace ViewCustom
{
	extern double VRwidth, VRheight;
	extern const double WHRatio;
	extern GLuint listsBase, inputBox;
	extern GLsizei numOfLists;
	extern int gotRules, showCursor;
	extern Textures *tex;
	extern Buttons *buttons;
	extern string input;
	extern clock_t startTimer;

	void HandOver();
	void Reshape(int w, int h);
	void Initialize();
	void Display();
	void DisplayGetSize();
	void DummyDisplay();
	void Key(unsigned char key, int x, int y);	//For entering grid size
	void CursorBlink();		//Blinking curson in textbox
	void exitCustom();

	void Mouse(int button, int state, int x, int y);

	namespace GetRules	//getting rules from console window
	{
		extern vector<int> populationState, condition, neighbour, result;

		void Menu();
		void AddRule();
		void ViewRules();
		void ClearRules();
		void clearLast();
		void Begin();
	}
}
#endif
