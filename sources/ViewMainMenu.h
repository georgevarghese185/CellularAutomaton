#ifndef __VIEWMAINMENU_H_INCLUDED
#define __VIEWMAINMENU_H_INCLUDED

#include<GL\freeglut.h>
#include"ViewStart.h"
#include"ViewDemo.h"
#include"ViewGOL.h"
#include"ViewCustom.h"
#include"Textures.h"

extern string ExecDir;
extern GLsizei WindowWidth, WindowHeight;

namespace ViewMainMenu
{
	extern double VRwidth, VRheight;
	extern const double WHRatio;
	extern GLuint listsBase, buttonPressed, buttonReleased, backButtonPressed, backButtonReleased;
	extern GLsizei numOfLists;
	extern Textures *tex;

	void HandOver();
	void Reshape(int w, int h);
	void Initialize();
	void Display();
	void DummyDisplay();
	void exitMainMenu();
	
	namespace Mouse
	{
		void Mouse(int button, int state, int x, int y);
		int ButtonPressCheck(int x, int y);
	}

	namespace Draw
	{
		extern int CAPreButtonDown, CACustButtonDown, demoButtonDown, backButtonDown;

		inline void ScaleAbout(GLfloat x, GLfloat y, GLfloat xScale, GLfloat yScale);
		void Buttons();
	}
}

#endif