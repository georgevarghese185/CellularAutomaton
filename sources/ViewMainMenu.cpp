#include"ViewMainMenu.h"

namespace ViewMainMenu
{
	double VRwidth, VRheight;
	const double WHRatio = 800.0 / 600.0;
	GLuint listsBase, buttonPressed, buttonReleased, backButtonPressed, backButtonReleased;
	int Draw::CAPreButtonDown = FALSE, Draw::CACustButtonDown = FALSE, Draw::demoButtonDown = FALSE, Draw::backButtonDown = FALSE;
	GLsizei numOfLists;
	Textures *tex;

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
		glutMouseFunc(Mouse::Mouse);
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

		GLuint i = 0;
		numOfLists = 4;
		listsBase = glGenLists(numOfLists);

		glNewList(buttonReleased = listsBase + i++, GL_COMPILE);
		//button inner
		glColor3ub(70, 70, 70);
		glRectf(22, 32, 60, 39);
		//left border
		glColor3ub(55, 55, 55);
		glBegin(GL_QUADS);
		glVertex2f(21, 40);
		glVertex2f(22, 39);
		glVertex2f(22, 32);
		glVertex2f(21, 31);
		//right border
		glColor3ub(126, 126, 126);
		glVertex2f(60, 39);
		glVertex2f(61, 40);
		glVertex2f(61, 31);
		glVertex2f(60, 32);
		//bottom border
		glColor3ub(35, 35, 35);
		glVertex2f(22, 32);
		glVertex2f(60, 32);
		glVertex2f(61, 31);
		glVertex2f(21, 31);
		//top border
		glColor3ub(156, 156, 156);
		glVertex2f(21, 40);
		glVertex2f(61, 40);
		glVertex2f(60, 39);
		glVertex2f(22, 39);
		glEnd();
		glEndList();

		glNewList(buttonPressed = listsBase + i++, GL_COMPILE);
		//button inner
		glColor3ub(61, 61, 61);
		glRectf(22, 32, 60, 39);
		//left border
		glColor3ub(126, 126, 126);
		glBegin(GL_QUADS);
		glVertex2f(21, 40);
		glVertex2f(22, 39);
		glVertex2f(22, 32);
		glVertex2f(21, 31);
		//right border
		glColor3ub(55, 55, 55);
		glVertex2f(60, 39);
		glVertex2f(61, 40);
		glVertex2f(61, 31);
		glVertex2f(60, 32);
		//bottom border
		glColor3ub(156, 156, 156);
		glVertex2f(22, 32);
		glVertex2f(60, 32);
		glVertex2f(61, 31);
		glVertex2f(21, 31);
		//top border
		glColor3ub(35, 35, 35);
		glVertex2f(21, 40);
		glVertex2f(61, 40);
		glVertex2f(60, 39);
		glVertex2f(22, 39);
		glEnd();
		glEndList();

		glNewList(backButtonPressed = listsBase + i++, GL_COMPILE);
		//button inner
		glColor3ub(61, 61, 61);
		glRectf(0.5, 52.5, 7.5, 56.5);
		//left border
		glColor3ub(126, 126, 126);
		glBegin(GL_QUADS);
		glVertex2f(0, 57);
		glVertex2f(0.5, 56.5);
		glVertex2f(0.5, 52.5);
		glVertex2f(0, 52);
		//right border
		glColor3ub(55, 55, 55);
		glVertex2f(7.5, 56.5);
		glVertex2f(8, 57);
		glVertex2f(8, 52);
		glVertex2f(7.5, 52.5);
		glColor3ub(35, 35, 35);
		//bottom border
		glColor3ub(156, 156, 156);
		glVertex2f(0.5, 52.5);
		glVertex2f(7.5, 52.5);
		glVertex2f(8, 52);
		glVertex2f(0, 52);
		//top border
		glColor3ub(35, 35, 35);
		glVertex2f(0, 57);
		glVertex2f(8, 57);
		glVertex2f(7.5, 56.5);
		glVertex2f(0.5, 56.5);
		glEnd();
		glEndList();

		glNewList(backButtonReleased = listsBase + i++, GL_COMPILE);
		//button inner
		glColor3ub(70, 70, 70);
		glRectf(0.5, 52.5, 7.5, 56.5);
		//left border
		glColor3ub(55, 55, 55);
		glBegin(GL_QUADS);
		glVertex2f(0, 57);
		glVertex2f(0.5, 56.5);
		glVertex2f(0.5, 52.5);
		glVertex2f(0, 52);
		//right border
		glColor3ub(126, 126, 126);
		glVertex2f(7.5, 56.5);
		glVertex2f(8, 57);
		glVertex2f(8, 52);
		glVertex2f(7.5, 52.5);
		glColor3ub(35, 35, 35);
		//bottom border
		glColor3ub(35, 35, 35);
		glVertex2f(0.5, 52.5);
		glVertex2f(7.5, 52.5);
		glVertex2f(8, 52);
		glVertex2f(0, 52);
		//top border
		glColor3ub(156, 156, 156);
		glVertex2f(0, 57);
		glVertex2f(8, 57);
		glVertex2f(7.5, 56.5);
		glVertex2f(0.5, 56.5);
		glEnd();
		glEndList();

		tex = new Textures(4);

		tex->LoadTexture(ExecDir + "textures/TEX_MAIN_MENU", 648, 144, TEX_MAIN_MENU);
		tex->MakeDList(TEX_MAIN_MENU, 13, 46, 67, 58);

		tex->LoadTexture(ExecDir + "textures/TEX_B_CA_PRE", 684, 126, TEX_B_CA_PRE);
		tex->MakeDList(TEX_B_CA_PRE, 22, 32, 60, 39);

		tex->LoadTexture(ExecDir + "textures/TEX_B_CA_CUST", 684, 126, TEX_B_CA_CUST);
		tex->MakeDList(TEX_B_CA_CUST, 22, 32, 60, 39);

		tex->LoadTexture(ExecDir + "textures/TEX_B_DEMO", 684, 126, TEX_B_DEMO);
		tex->MakeDList(TEX_B_DEMO, 22, 32, 60, 39);

		tex->LoadTexture(ExecDir + "textures/TEX_B_BACK", 140, 80, TEX_B_BACK);
		tex->MakeDList(TEX_B_BACK, 0.5, 52.5, 7.5, 56.5);
	}

	void Display()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		tex->DrawTexture(TEX_MAIN_MENU);
		Draw::Buttons();

		glutSwapBuffers();
	}

	void DummyDisplay() {}

	void exitMainMenu()
	{
		glutDisplayFunc(DummyDisplay);
		glDeleteLists(listsBase, numOfLists);
		delete tex;
		glutMouseFunc(NULL);
		glutIdleFunc(NULL);
	}

	void Mouse::Mouse(int button, int state, int x, int y)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			int pressedButton = ButtonPressCheck(x, WindowHeight - y);
			if (pressedButton == CA_PRE_BUTTON)
			{
				Draw::CAPreButtonDown = TRUE;
				glutPostRedisplay();
			}
			else if (pressedButton == CA_CUST_BUTTON)
			{
				Draw::CACustButtonDown = TRUE;
				glutPostRedisplay();
			}
			else if (pressedButton == DEMO_BUTTON)
			{
				Draw::demoButtonDown = TRUE;
				glutPostRedisplay();
			}
			else if (pressedButton == BACK_BUTTON)
			{
				Draw::backButtonDown = TRUE;
				glutPostRedisplay();
			}
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			if (Draw::CAPreButtonDown)
			{
				Draw::CAPreButtonDown = FALSE;
				glutPostRedisplay();
				exitMainMenu();
				glutIdleFunc(ViewGOL::HandOver);
			}
			else if (Draw::CACustButtonDown)
			{
				Draw::CACustButtonDown = FALSE;
				glutPostRedisplay();
				exitMainMenu();
				glutIdleFunc(ViewCustom::HandOver);
			}
			else if (Draw::demoButtonDown)
			{
				Draw::demoButtonDown = FALSE;
				glutPostRedisplay();
				exitMainMenu();
				glutIdleFunc(ViewDemo::HandOver);
			}
			else if (Draw::backButtonDown)
			{
				Draw::backButtonDown = FALSE;
				glutPostRedisplay();
				exitMainMenu();
				glutIdleFunc(ViewStart::HandOver);
			}
		}
	}

	int Mouse::ButtonPressCheck(int x, int y)
	{
		GLubyte pixelColor[3], CAPreColor = 10, CACustColor = 20, demoColor = 30, backColor = 40;
		glClear(GL_COLOR_BUFFER_BIT);

		glColor3ub(CAPreColor, 0, 0);
		glRectf(21, 31, 61, 40);

		glPushMatrix();
		glTranslatef(0, -13, 0);
		glColor3ub(CACustColor, 0, 0);
		glRectf(21, 31, 61, 40);

		glTranslatef(0, 13 - 27, 0);
		glColor3ub(demoColor, 0, 0);
		glRectf(21, 31, 61, 40);
		glPopMatrix();

		glColor3ub(backColor, 0, 0);
		glRectf(0, 52, 8, 57);

		glFlush();

		glReadBuffer(GL_BACK);
		glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixelColor);

		if (pixelColor[0] == CAPreColor)
		{
			return CA_PRE_BUTTON;
		}
		else if (pixelColor[0] == CACustColor)
		{
			return CA_CUST_BUTTON;
		}
		else if (pixelColor[0] == demoColor)
		{
			return DEMO_BUTTON;
		}
		else if (pixelColor[0] == backColor)
		{
			return BACK_BUTTON;
		}
		else
		{
			return -1;
		}
	}

	inline void Draw::ScaleAbout(GLfloat x, GLfloat y, GLfloat xScale, GLfloat yScale)
	{
		glTranslatef(x, y, 0);
		glScalef(xScale, yScale, 0);
		glTranslatef(-x, -y, 0);
	}

	void Draw::Buttons()
	{
		if (Draw::CAPreButtonDown)
		{
			glPushMatrix();
			ScaleAbout(41.0f, 35.5f, 0.95f, 0.95f);
			glCallList(buttonPressed);
			tex->DrawTexture(TEX_B_CA_PRE);
			glPopMatrix();
		}
		else
		{
			glCallList(buttonReleased);
			tex->DrawTexture(TEX_B_CA_PRE);
		}

		glPushMatrix();
		glTranslatef(0, -13, 0);
		if (Draw::CACustButtonDown)
		{
			glPushMatrix();
			ScaleAbout(41.0f, 35.5f, 0.95f, 0.95f);
			glCallList(buttonPressed);
			tex->DrawTexture(TEX_B_CA_CUST);
			glPopMatrix();
		}
		else
		{
			glCallList(buttonReleased);
			tex->DrawTexture(TEX_B_CA_CUST);
		}
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, -27, 0);
		if (Draw::demoButtonDown)
		{
			glPushMatrix();
			ScaleAbout(41.0f, 35.5f, 0.95f, 0.95f);
			glCallList(buttonPressed);
			tex->DrawTexture(TEX_B_DEMO);
			glPopMatrix();
		}
		else
		{
			glCallList(buttonReleased);
			tex->DrawTexture(TEX_B_DEMO);
		}
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.5, 0, 0);
		if (Draw::backButtonDown)
		{
			glPushMatrix();
			ScaleAbout(4.0f, 54.5f, 0.95f, 0.95f);
			glCallList(backButtonPressed);
			tex->DrawTexture(TEX_B_BACK);
			glPopMatrix();
		}
		else
		{
			glCallList(backButtonReleased);
			tex->DrawTexture(TEX_B_BACK);
		}
		glPopMatrix();
	}
}