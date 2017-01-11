#include"ViewStart.h"

namespace ViewStart
{
	double VRwidth, VRheight;
	const double WHRatio = 1;
	GLint vp[4];
	Textures *tex;
	Buttons *buttons;

#define START_BUTTON 0
#define TEX_START 0
#define TEX_BY 2

	void HandOver()
	{
		Initialize();
		glutDisplayFunc(Display);
		glutReshapeFunc(Reshape);
		glutMouseFunc(Mouse);
		glutPostRedisplay();
		glutIdleFunc(PutText);
		glutReshapeWindow(WindowWidth, WindowHeight);
	}

	void Reshape(int w, int h)
	{
		WindowWidth = w;
		WindowHeight = h;
		if (h * WHRatio <= w)

			glViewport((w / 2) - (GLsizei)(h * WHRatio / 2), 0, (GLsizei)(h * WHRatio), h);
		else
			glViewport(0, (h / 2) - ((GLsizei)(w / WHRatio) / 2), w, (GLsizei)(w / WHRatio));
		glGetIntegerv(GL_VIEWPORT, vp);
		setFont(L"Arial Black", (long)(vp[3] / VRheight * 7), FALSE, TRUE);

		glutPostRedisplay();
	}

	void Initialize()
	{
		if (WindowWidth < 500 || WindowHeight < 500)
		{
			WindowWidth = 500, WindowHeight = 500;
			glutReshapeWindow(WindowWidth, WindowHeight);
		}
		VRwidth = 50;
		VRheight = 50;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, VRwidth, 0, VRheight);
		glViewport(0, 0, WindowWidth, WindowHeight);
		glMatrixMode(GL_MODELVIEW);
		glClearColor(0.1725f, 0.1725f, 0.1725f, 1.0f);

		setFont(L"Arial Black", (long)(vp[3] / VRheight * 7.69), FALSE, TRUE);

		tex = new Textures(2);

		tex->LoadTexture(ExecDir + "textures/TEX_START", 480, 200, TEX_START);
		tex->MakeDList(TEX_START, 13, 11, 37, 21);

		tex->LoadTexture(ExecDir + "textures/TEX_BY", 364, 84, TEX_BY);
		tex->MakeDList(TEX_BY, 24, 2, 50, 8);

		buttons = new Buttons(1);
		buttons->MakeButtonGraphic(START_BUTTON, 0, 0, 26, 12, 1, 1, 25, 11,
			Color(70, 70, 70), Color(35, 35, 35), Color(156, 156, 156), Color(126, 126, 126), Color(55, 55, 55),
			Color(70, 70, 70), Color(156, 156, 156), Color(35, 35, 35), Color(55, 55, 55), Color(126, 126, 126));
		buttons->MakeButton(START_BUTTON, 12, 10, 38, 22, START_BUTTON);
	}

	void Display()
	{
		glFinish();
		glClear(GL_COLOR_BUFFER_BIT);

		buttons->DrawButton(START_BUTTON, TEX_START, tex);

		tex->DrawTexture(TEX_BY);

		glutSwapBuffers();
		glutIdleFunc(PutText);
	}

	void DummyDisplay() {}

	void exitStart()
	{
		glutDisplayFunc(DummyDisplay);
		delete tex;
		delete buttons;
		glutMouseFunc(NULL);
		glutReshapeFunc(NULL);
		glutIdleFunc(ViewMainMenu::HandOver);
	}

	void Mouse(int button, int state, int x, int y)
	{
		if (button == GLUT_LEFT && state == GLUT_DOWN)
		{
			buttons->PressButton(x, WindowHeight - y);
			glutPostRedisplay();
		}
		else if (button == GLUT_LEFT && state == GLUT_UP)
		{
			int pressed=buttons->PressButton(x, WindowHeight - y);
			buttons->ReleaseButtons();
			if (pressed == START_BUTTON)
				exitStart();
			glutPostRedisplay();
		}
	}

	void PutText()
	{
		throwText(L"Cellular", vp[0] + 167, vp[1] + 9, RGB(44, 44, 44), RGB(255, 255, 255));
		throwText(L"Automaton 3.0", vp[0] + 42, vp[1] + 104, RGB(44, 44, 44), RGB(255, 255, 255));
		glutIdleFunc(NULL);
	}
}