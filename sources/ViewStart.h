#ifndef __VIEWSTART_H_INCLUDED
#define __VIEWSTART_H_INCLUDED

#include<GL\freeglut.h>
#include"ViewMainMenu.h"
#include"Textures.h"
#include"Buttons.h"
#include"TextManip.h"

using namespace std;
extern string ExecDir;
extern GLsizei WindowWidth, WindowHeight;

namespace ViewStart
{
	
	extern double VRwidth, VRheight;
	extern const double WHRatio;
	extern GLint vp[4];
	extern Textures *tex;
	extern Buttons *buttons;

	void HandOver();
	void Reshape(int w, int h);
	void Initialize();
	void Display();
	void DummyDisplay();
	void exitStart();

	void Mouse(int button, int state, int x, int y);

	void PutText();
}

#endif
