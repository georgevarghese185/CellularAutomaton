#ifndef __VIEWAUTOMATON_H_INCLUDED
#define __VIEWAUTOMATON_H_INCLUDED

#include<GL\glut.h>
#include<Windows.h>
#include<ctime>
#include"ViewMainMenu.h"
#include"Cells.h"
#include"Textures.h"
#include"Buttons.h"

extern string ExecDir;						//current directory of .exe
extern GLsizei WindowWidth, WindowHeight;

namespace ViewAutomaton		
{
	extern double VRwidth, VRheight, px;	
	extern const double WHRatio;			//Ratio Width/Height
	extern GLint automatonVP[4], sidebarVP[4];
	extern GLuint listsBase, grid, cell, exitButtonX, playButtonPlay, playButtonPause, plus, minus, delayBox;
	extern GLsizei numOfLists;
	extern clock_t timerStart;
	extern int delay;
	extern bool paused;
	extern Textures *tex;
	extern Cell cm;

	class Buttons2 :public Buttons
	{
	public:
		Buttons2(int numOfButtons);
		void DrawPlayButton(int buttonName, int paused);
	};
	extern Buttons2 *buttons;

	void HandOver();				//HandOver view.
	void Reshape(int w, int h);
	void calcVPs();					//Calculate Viewports used by some functions
	void Initialize();				//Initialize variables and DLists
	void MakeGrid();				//Initialize DList for square grid
	void Display();
	void DummyDisplay();			//Empty Display function. Used to fix redisplay errors during deallocation of textures
	void Run();						//Idle function for unpaused automaton
	void exitAutomaton();			//Clean up

	namespace Mouse			
	{
		void Setup(int button, int state, int x, int y);		//Manually populating when CA is paused
		void WindowToWorldCoordinates(double &x, double &y);	//Converts Window coordinates to world coordinates
		int ButtonPressCheck(int x, int y);						//Check if any buttons were clicked

		namespace Motion			//Mouse Motion functions for when left button is held down.
		{
			void PopulateCells(int x, int y);
			void UnpopulateCells(int x, int y);
		}
	}

	namespace Draw		
	{
		void FilledCells();			//Color in the populated cells
		void Sidebar();		//Draw the sidebar
	}
}

#endif
