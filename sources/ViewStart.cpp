#include"ViewStart.h"

namespace ViewStart
{
	double VRwidth, VRheight;
	const double WHRatio = 1;
	GLint vp[4];
	GLuint listsBase, startButtonReleased, startButtonPressed;
	GLsizei numOfLists;
	int Draw::startButtonDown = FALSE;
	Textures *tex;

#define START_BUTTON 0
#define TEX_START 0
#define TEX_BY 2

	void HandOver()
	{
		Initialize();
		glutDisplayFunc(Display);
		glutReshapeFunc(Reshape);
		glutMouseFunc(Mouse::Mouse);
		glutPostRedisplay();
		glutIdleFunc(Draw::text);
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

		Draw::startButtonDown = FALSE;

		GLuint i = 0;
		numOfLists = 2;
		listsBase = glGenLists(numOfLists);

		glNewList(startButtonReleased = listsBase + i++, GL_COMPILE);
		//button inner
		glColor3ub(70, 70, 70);
		glRectf(13, 11, 37, 21);
		//left border
		glColor3ub(55, 55, 55);
		glBegin(GL_QUADS);
		glVertex2f(12, 22);
		glVertex2f(13, 21);
		glVertex2f(13, 11);
		glVertex2f(12, 10);
		//right border
		glColor3ub(126, 126, 126);
		glVertex2f(37, 21);
		glVertex2f(38, 22);
		glVertex2f(38, 10);
		glVertex2f(37, 11);
		//top border
		glColor3ub(156, 156, 156);
		glVertex2f(12, 22);
		glVertex2f(38, 22);
		glVertex2f(37, 21);
		glVertex2f(13, 21);
		//bottom border
		glColor3ub(35, 35, 35);
		glVertex2f(13, 11);
		glVertex2f(37, 11);
		glVertex2f(38, 10);
		glVertex2f(12, 10);
		glEnd();
		glEndList();

		glNewList(startButtonPressed = listsBase + i++, GL_COMPILE);
		glColor3ub(70, 70, 70);
		glRectf(13, 11, 37, 21);
		//left border
		glColor3ub(126, 126, 126);
		glBegin(GL_QUADS);
		glVertex2f(12, 22);
		glVertex2f(13, 21);
		glVertex2f(13, 11);
		glVertex2f(12, 10);
		//right border
		glColor3ub(55, 55, 55);
		glVertex2f(37, 21);
		glVertex2f(38, 22);
		glVertex2f(38, 10);
		glVertex2f(37, 11);
		//top border
		glColor3ub(35, 35, 35);
		glVertex2f(12, 22);
		glVertex2f(38, 22);
		glVertex2f(37, 21);
		glVertex2f(13, 21);
		//bottom border
		glColor3ub(156, 156, 156);
		glVertex2f(13, 11);
		glVertex2f(37, 11);
		glVertex2f(38, 10);
		glVertex2f(12, 10);
		glEnd();
		glEndList();

		setFont(L"Arial Black", (long)(vp[3] / VRheight * 7.69), FALSE, TRUE);

		tex = new Textures(2);

		tex->LoadTexture(ExecDir + "textures/TEX_START", 480, 200, TEX_START);
		tex->MakeDList(TEX_START, 13, 11, 37, 21);

		tex->LoadTexture(ExecDir + "textures/TEX_BY", 364, 84, TEX_BY);
		tex->MakeDList(TEX_BY, 24, 2, 50, 8);
	}

	void Display()
	{
		glFinish();
		glClear(GL_COLOR_BUFFER_BIT);

		Draw::StartButton();

		tex->DrawTexture(TEX_BY);

		glutSwapBuffers();
		glutIdleFunc(Draw::text);
	}

	void DummyDisplay() {}

	void exitStart()
	{
		glutDisplayFunc(DummyDisplay);
		glDeleteLists(listsBase, numOfLists);
		delete tex;
		glutMouseFunc(NULL);
		glutReshapeFunc(NULL);
		glutIdleFunc(ViewMainMenu::HandOver);
	}

	void Mouse::Mouse(int button, int state, int x, int y)
	{
		if (button == GLUT_LEFT && state == GLUT_DOWN)
		{
			int pressedButton = ButtonPressCheck(x, WindowHeight - y);
			if (pressedButton == START_BUTTON)
			{
				Draw::startButtonDown = TRUE;
				glutPostRedisplay();
			}
		}

		else if (button == GLUT_LEFT && state == GLUT_UP && Draw::startButtonDown)
		{
			Draw::startButtonDown = FALSE;
			Draw::StartButton();
			glutPostRedisplay();
			exitStart();
		}
	}

	int Mouse::ButtonPressCheck(int x, int y)
	{
		GLubyte pixelColor[3], startColor = 10;
		glClear(GL_COLOR_BUFFER_BIT);

		glColor3ub(startColor, 0, 0);
		glRectf(12, 10, 38, 22);

		glFlush();
		glReadBuffer(GL_BACK);
		glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixelColor);

		if (pixelColor[0] == startColor)
		{
			return START_BUTTON;
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

	void Draw::text()
	{
		throwText(L"Cellular", vp[0] + 167, vp[1] + 9, RGB(44, 44, 44), RGB(255, 255, 255));
		throwText(L"Automaton 3.0", vp[0] + 42, vp[1] + 104, RGB(44, 44, 44), RGB(255, 255, 255));
		glutIdleFunc(NULL);
	}

	void Draw::StartButton()
	{
		if (Draw::startButtonDown)
		{
			glPushMatrix();
			ScaleAbout(25.0f, 16.0f, 0.95f, 0.95f);
			glCallList(startButtonPressed);
			tex->DrawTexture(TEX_START);
			glPopMatrix();
		}
		else
		{
			glCallList(startButtonReleased);
			tex->DrawTexture(TEX_START);
		}
	}
}