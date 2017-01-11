#pragma once

#include<GL\glut.h>
#include<Windows.h>
#include<stdlib.h>
#include<iostream>
#include<ctime>
#include"CellMap.h"
#include"WindowWorldGlobals.h"
#include"Rule.h"
#include"ViewStart.h"
#include"Textures.h"

#define EXIT_BUTTON 1
#define PLAY_BUTTON 2
#define RESET_BUTTON 3

extern string ExecDir;

namespace ViewAutomaton		
{
	extern GLuint listsBase, gridLineV, gridLineH, cell, exitButtonInner, exitButtonTop, exitButtonBottom, exitButtonLeft, exitButtonRight, exitButtonX, playButtonPlay, playButtonPause;
	extern GLsizei numOfLists;
	extern int paused, exitButtonBorders[2][2];
	extern clock_t timerStart;
	extern double delay;
	extern Textures *tex;

	void HandOver();		

	void Initialize();

	void Display();

	void exitAutomaton();

	int ButtonPressCheck(int x, int y);	
	
	void Run();				

	namespace Mouse			
	{
		void Setup(int button, int state, int x, int y);		
		
		void Running(int button, int state, int x, int y);		
	}

	namespace MouseMotion		
	{
		void PopulateCells(int x, int y);		
		
		void UnpopulateCells(int x, int y);		
	}

	namespace Draw		
	{
		extern int exitButtonDown, playButtonDown, resetButtonDown;
		
		void Grid();			
		
		void FilledCells();		

		void Sidebar();
	}
}
