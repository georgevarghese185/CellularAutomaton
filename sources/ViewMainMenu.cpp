#include"ViewMainMenu.h"

namespace ViewMainMenu
{
	double VRwidth, VRheight;
	const double WHRatio = 800.0 / 600.0;
	Textures *tex;
	Buttons *buttons;

#define BUTTON 0
#define CA_CUST_BUTTON 0
#define CA_PRE_BUTTON 1
#define DEMO_BUTTON 2
#define BACK_BUTTON 3
#define TEX_MAIN_MENU 0
#define TEX_B_CA_PRE 1
#define TEX_B_CA_CUST 2
#define TEX_B_DEMO 3
#define TEX_B_BACK 4

	void HandOver()
	{
		Initialize();
		glutDisplayFunc(Display);
		glutReshapeFunc(Reshape);
		glutMouseFunc(Mouse);
		glutPostRedisplay();
		glutIdleFunc(NULL);
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
		glutPostRedisplay();
	}

	void Initialize()
	{
		if (WindowWidth < 800 || WindowHeight < 600)
		{
			WindowWidth = 800; WindowHeight = 600;
			glutReshapeWindow(WindowWidth, WindowHeight);
		}
		VRwidth = 80; VRheight = 60;
		glViewport(0, 0, 800, 600);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, VRwidth, 0, VRheight);
		glViewport(0, 0, WindowWidth, WindowHeight);
		glMatrixMode(GL_MODELVIEW);
		glClearColor(0.1725f, 0.1725f, 0.1725f, 1.0f);

		tex = new Textures(4);

		tex->LoadTexture(ExecDir + "textures/TEX_MAIN_MENU", 648, 144, TEX_MAIN_MENU);
		tex->MakeDList(TEX_MAIN_MENU, 13, 46, 67, 58);

		tex->LoadTexture(ExecDir + "textures/TEX_B_CA_PRE", 684, 126, TEX_B_CA_PRE);
		tex->MakeDList(TEX_B_CA_PRE, 22, 32, 60, 39);

		tex->LoadTexture(ExecDir + "textures/TEX_B_CA_CUST", 684, 126, TEX_B_CA_CUST);
		tex->MakeDList(TEX_B_CA_CUST, 22, 19, 60, 26);

		tex->LoadTexture(ExecDir + "textures/TEX_B_DEMO", 684, 126, TEX_B_DEMO);
		tex->MakeDList(TEX_B_DEMO, 22, 5, 60, 12);

		tex->LoadTexture(ExecDir + "textures/TEX_B_BACK", 140, 80, TEX_B_BACK);
		tex->MakeDList(TEX_B_BACK, 1, 52.5, 8, 56.5);

		buttons = new Buttons(4);
		buttons->MakeButtonGraphic(BACK_BUTTON, 0, 0, 8, 5, 0.5, 0.5, 7.5, 4.5,
			Color(61, 61, 61), Color(35, 35, 35), Color(126, 126, 126), Color(55, 55, 55), Color(156, 156, 156),
			Color(70, 70, 70), Color(156, 156, 156), Color(35, 35, 35), Color(55, 55, 55), Color(126, 126, 126));
		buttons->MakeButtonGraphic(BUTTON, 0, 0, 40, 9, 1, 1, 39, 8,
			Color(61, 61, 61), Color(35, 35, 35), Color(126, 126, 126), Color(156, 156, 156), Color(55, 55, 55),
			Color(70, 70, 70), Color(156, 156, 156), Color(35, 35, 35), Color(55, 55, 55), Color(126, 126, 126));
		buttons->MakeButton(CA_PRE_BUTTON, 21, 31, 61, 40, BUTTON);
		buttons->MakeButton(CA_CUST_BUTTON, 21, 18, 61, 27, BUTTON);
		buttons->MakeButton(DEMO_BUTTON, 21, 4, 61, 13, BUTTON);
		buttons->MakeButton(BACK_BUTTON, 0.5, 52, 8.5, 57, BACK_BUTTON);
	}

	void Display()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		tex->DrawTexture(TEX_MAIN_MENU);
		buttons->DrawButton(BACK_BUTTON,TEX_B_BACK,tex);
		buttons->DrawButton(CA_PRE_BUTTON, TEX_B_CA_PRE, tex);
		buttons->DrawButton(CA_CUST_BUTTON, TEX_B_CA_CUST, tex);
		buttons->DrawButton(DEMO_BUTTON, TEX_B_DEMO, tex);

		glutSwapBuffers();
	}

	void DummyDisplay() {}

	void exitMainMenu()
	{
		glutDisplayFunc(DummyDisplay);
		delete tex;
		delete buttons;
		glutMouseFunc(NULL);
		glutIdleFunc(NULL);
	}

	void Mouse(int button, int state, int x, int y)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			buttons->PressButton(x, WindowHeight - y);
			glutPostRedisplay();
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			int pressedButton = buttons->PressButton(x, WindowHeight - y);
			buttons->ReleaseButtons();
			if (pressedButton == CA_PRE_BUTTON)
			{
				exitMainMenu();
				glutIdleFunc(ViewGOL::HandOver);
			}
			else if (pressedButton == CA_CUST_BUTTON)
			{
				exitMainMenu();
				glutIdleFunc(ViewCustom::HandOver);
			}
			else if (pressedButton == DEMO_BUTTON)
			{
				exitMainMenu();
				glutIdleFunc(ViewDemo::HandOver);
			}
			else if(pressedButton == BACK_BUTTON)
			{
				exitMainMenu();
				glutIdleFunc(ViewStart::HandOver);
			}
			glutPostRedisplay();
		}
	}
}