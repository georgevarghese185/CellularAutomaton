#ifndef __VIEWSTART_H_INCLUDED
#define __VIEWSTART_H_INCLUDED

#include<GL\freeglut.h>
#include"ViewMainMenu.h"
#include"Textures.h"
#include"TextManip.h"

using namespace std;
extern string ExecDir;
extern GLsizei WindowWidth, WindowHeight;

namespace ViewStart
{
	
	extern double VRwidth, VRheight;
	extern const double WHRatio;
	extern GLint vp[4];
	extern GLuint listsBase, startButtonReleased, startButtonPressed;
	extern GLsizei numOfLists;
	extern Textures *tex;

	void HandOver();
	void Reshape(int w, int h);
	void Initialize();
	void Display();
	void DummyDisplay();
	void exitStart();

	namespace Mouse
	{
		void Mouse(int button, int state, int x, int y);
		int ButtonPressCheck(int x, int y);
	}

	namespace Draw
	{
		extern int startButtonDown;

		inline void ScaleAbout(GLfloat x, GLfloat y, GLfloat xScale, GLfloat yScale);
		void text();
		void StartButton();
	}
}

#endif
