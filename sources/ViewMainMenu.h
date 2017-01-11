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
	extern Textures *tex;
	extern Buttons *buttons;

	void HandOver();
	void Reshape(int w, int h);
	void Initialize();
	void Display();
	void DummyDisplay();
	void exitMainMenu();
	
	void Mouse(int button, int state, int x, int y);
}

#endif