#pragma once

#include<GL\glut.h>
#include<Windows.h>
#include<stdlib.h>
#include<iostream>
#include<ctime>
#include"CellMap.h"
#include"WindowWorldGlobals.h"
#include"Rule.h"

namespace ViewAutomaton		//Using a namespace to group together Automaton View functions for easier understadning.
{
	extern int paused, gridLineV, gridLineH, cell, startButton, playSymbol, pauseSymbol;
	extern float barX0, barY0, barX1, barY1, barWidth, barHeight, startBorder[4][2], startOffsetX, startOffsetY;
	extern clock_t timerStart;
	extern double delay;

	void HandOver();		//Recieves control of display
	
	void Initialize();		//Initializes global view variables, display lists and other elements.
	
	void Display();			//Displays elements
	
	void ButtonPressCheck(double x, double y);		//Check which sidebar button was pressed, IF pressed
	
	int StartButtonPressed(double x, double y);		//Check if start button was pressed
	
	void Run();				//Starts automaton and disables other interaction

	namespace Mouse			//For grouping Mouse click events
	{
		void Setup(int button, int state, int x, int y);		//For setting up cells or pressing sidebar buttons
		
		void Running(int button, int state, int x, int y);		//For specific buttons allowed during automaton running
	}

	namespace MouseMotion		//For grouping motion mouse events
	{
		void PopulateCells(int x, int y);		//To populate cells hovered over when left button pressed
		
		void UnpopulateCells(int x, int y);		//To unpoluate ..........................................
	}

	namespace Draw		//For grouping Drawing functions
	{
		void Grid();			//Draws cell grid
		
		void FilledCells();		//Draws filled (live) cell
		
		void StartButton();		//Draws play/pause button
	}
}
