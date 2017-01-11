#pragma once

#include<GL\glut.h>
#include<iostream>
#include"Textures.h"
#include"ViewAutomaton.h"
#include"WindowWorldGlobals.h"
using namespace std;
extern string ExecDir;

namespace ViewStart
{
	extern int startButton, startLeftBorder, startRightBorder, startTopBorder, startBottomBorder;
	extern GLfloat startButtonV[8][2];
	extern Textures *tex;

	void HandOver();
	void Initialize();
	void Display();
	int StartButtonPressed(double x, double y);
	void Reshape(int w, int h);
	void exitStart();

	namespace Draw
	{
		extern int startButtonDown;
		void StartButton();
	}

	namespace Mouse
	{
		void Mouse(int button, int state, int x, int y);
	}
}
