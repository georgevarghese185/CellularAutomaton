#pragma once

#include<GL\glut.h>
#include<iostream>
#include"ViewAutomaton.h"
#include"WindowWorldGlobals.h"
using namespace std;

namespace ViewStart
{
	extern int startButton, startLeftBorder, startRightBorder, startTopBorder, startBottomBorder, startButtonDown;
	extern GLfloat startButtonV[8][2];
	
	void HandOver();
	void Initialize();
	void Display();
	int StartButtonPressed(double x, double y);

	namespace Draw
	{
		void StartButton();
	}

	namespace Mouse
	{
		void Mouse(int button, int state, int x, int y);
	}
}
