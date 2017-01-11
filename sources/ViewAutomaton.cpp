#include"ViewAutomaton.h"

namespace ViewAutomaton
{
	GLuint listsBase, gridLineV, gridLineH, cell, exitButtonInner, exitButtonTop, exitButtonBottom, exitButtonLeft, exitButtonRight, exitButtonX, playButtonPlay, playButtonPause;
	GLsizei numOfLists;
	int paused, exitButtonBorders[2][2] = { { 3,97 },{ 16,89 } };
	int Draw::exitButtonDown = FALSE, Draw::playButtonDown = FALSE;
	clock_t timerStart;
	double delay;

	void Initialize()
	{
		srand(time(NULL));

		WindowWidth = 590, WindowHeight = 500;
		WidthHeightRatio = (double)WindowWidth / (double)WindowHeight;
		glutReshapeWindow(WindowWidth, WindowHeight);

		VRwidth = (GRID_MAX + (WindowWidth - WindowHeight) / ((double)WindowHeight / (double)GRID_MAX));
		VRheight = GRID_MAX;
		CM.Initialize(GRID_MAX);

		glClearColor(0.1725, 0.1725, 0.1725, 1);

		GLuint i;
		numOfLists = 11;
		listsBase = glGenLists(numOfLists);
		
		i = 0;
		glNewList(gridLineV = listsBase + i++, GL_COMPILE);
		glBegin(GL_LINES);
		glVertex2f(0, 0);
		glVertex2f(0, GRID_MAX);
		glEnd();
		glEndList();

		glNewList(gridLineH = listsBase + i++, GL_COMPILE);
		glBegin(GL_LINES);
		glVertex2f(0, 0);
		glVertex2f(GRID_MAX, 0);
		glEnd();
		glEndList();

		glNewList(cell = listsBase + i++, GL_COMPILE);
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(1, 0);
		glVertex2f(1, 1);
		glVertex2f(0, 1);
		glEnd();
		glEndList();

		glNewList(exitButtonInner = listsBase + i++, GL_COMPILE);
		glBegin(GL_QUADS);
		glVertex2f(4, 96);
		glVertex2f(15, 96);
		glVertex2f(15, 90);
		glVertex2f(4, 90);
		glEnd();
		glEndList();

		glNewList(exitButtonTop = listsBase + i++, GL_COMPILE);
		glBegin(GL_QUADS);
		glVertex2f(3, 97);
		glVertex2f(16, 97);
		glVertex2f(15, 96);
		glVertex2f(4, 96);
		glEnd();
		glEndList();

		glNewList(exitButtonRight = listsBase + i++, GL_COMPILE);
		glBegin(GL_QUADS);
		glVertex2f(15, 96);
		glVertex2f(16, 97);
		glVertex2f(16, 89);
		glVertex2f(14, 90);
		glEnd();
		glEndList();

		glNewList(exitButtonBottom = listsBase + i++, GL_COMPILE);
		glBegin(GL_QUADS);
		glVertex2f(4, 90);
		glVertex2f(15, 90);
		glVertex2f(16, 89);
		glVertex2f(3, 89);
		glEnd();
		glEndList();

		glNewList(exitButtonLeft = listsBase + i++, GL_COMPILE);
		glBegin(GL_QUADS);
		glVertex2f(3, 97);
		glVertex2f(4, 96);
		glVertex2f(4, 90);
		glVertex2f(3, 89);
		glEnd();
		glEndList();

		glNewList(exitButtonX = listsBase + i++, GL_COMPILE);
		glBegin(GL_QUADS);
		glColor3f(1, 0, 0);
		glVertex2f(7, 95);
		glVertex2f(8, 95);
		glVertex2f(9.5, 94);
		glVertex2f(9, 93);
		glVertex2f(9.5, 94);
		glVertex2f(11, 95);
		glVertex2f(12, 95);
		glVertex2f(10, 93);
		glVertex2f(10, 93);
		glVertex2f(12, 91);
		glVertex2f(11, 91);
		glVertex2f(9.5, 92);
		glVertex2f(9.5, 92);
		glVertex2f(8, 91);
		glVertex2f(7, 91);
		glVertex2f(9, 93);
		glVertex2f(9, 93);
		glVertex2f(9.5, 94);
		glVertex2f(10, 93);
		glVertex2f(9.5, 92);
		glEnd();
		glEndList();

		glNewList(playButtonPlay = listsBase + i++, GL_COMPILE);
		glBegin(GL_TRIANGLES);
		glVertex2f(7,95);
		glVertex2f(7,91);
		glVertex2f(12,93);
		glEnd();
		glEndList();

		glNewList(playButtonPause = listsBase + i++, GL_COMPILE);
		glBegin(GL_QUADS);
		glVertex2f(7,95);
		glVertex2f(9,95);
		glVertex2f(9,91);
		glVertex2f(7,91);

		glVertex2f(10,95);
		glVertex2f(12,95);
		glVertex2f(12,91);
		glVertex2f(10,91);
		glEnd();
		glEndList();
		//last DL (11)
	}

	void HandOver()
	{
		system("cls");
		cout << "Enter Sqaure Grid Size: ";		
		cin >> GRID_MAX;
		cout << "Enter delay(in seconds): ";
		cin >> delay;

		paused = TRUE;	
		Initialize();
		glutReshapeFunc(Reshape);
		glutDisplayFunc(Display);
		glutMouseFunc(Mouse::Setup);
		glutIdleFunc(NULL);
		glutShowWindow();
	}

	void Display()
	{
		GLint viewport[4];
		glClear(GL_COLOR_BUFFER_BIT);
		glPushAttrib(GL_VIEWPORT_BIT);
		glGetIntegerv(GL_VIEWPORT, viewport);

		glViewport(viewport[0], viewport[1], viewport[2] * (1 - 0.1526), viewport[3]);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, VRheight, 0, VRheight);
		glMatrixMode(GL_MODELVIEW);

		Draw::FilledCells();
		Draw::Grid();
		glFlush();

		glViewport(viewport[0] + viewport[2] * (1 - 0.1526), viewport[1], viewport[2] * 0.1526, viewport[3]);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, 18, 0, 100);
		glMatrixMode(GL_MODELVIEW);

		Draw::Sidebar();
		glFlush();
		glutSwapBuffers();
		glPopAttrib();
	}

	void Draw::Sidebar()
	{
		if (exitButtonDown)
		{
			glPushMatrix();

			glColor3ub(222,222,222);
			glCallList(exitButtonInner);
			
			glColor3ub(184,0,0);
			glTranslatef(9.5, 93, 0);
			glScalef(0.95, 0.95, 0);
			glTranslatef(-9.5, -93, 0);
			glCallList(exitButtonX);

			
			glColor3ub(195,195,195);
			glCallList(exitButtonTop);
			
			glColor3ub(245,245,245);
			glCallList(exitButtonBottom);
			
			glColor3ub(232,232,232);
			glCallList(exitButtonLeft);
			
			glColor3ub(212,212,212);
			glCallList(exitButtonRight);

			glPopMatrix();
		}
		else
		{
			glColor3ub(238,238,238);
			glCallList(exitButtonInner);
			
			glColor3ub(215,2,2);
			glCallList(exitButtonX);
			
			glColor3ub(240,240,240);
			glCallList(exitButtonTop);
			
			glColor3ub(197,197,197);
			glCallList(exitButtonBottom);
			
			glColor3ub(209,209,209);
			glCallList(exitButtonLeft);
			
			glColor3ub(235,235,235);
			glCallList(exitButtonRight);
		}

		if (playButtonDown)
		{
			GLint stackSize[20];
			glPushMatrix();
			glTranslatef(0, -14, 0);

			glColor3ub(222, 222, 222);
			glCallList(exitButtonInner);

			glColor3ub(0, 0, 0);
			glTranslatef(9.5, 93, 0);
			glScalef(0.95, 0.95, 0);
			glTranslatef(-9.5, -93, 0);
			(paused) ? glCallList(playButtonPlay) : glCallList(playButtonPause);

			glColor3ub(195, 195, 195);
			glCallList(exitButtonTop);

			glColor3ub(245, 245, 245);
			glCallList(exitButtonBottom);

			glColor3ub(232, 232, 232);
			glCallList(exitButtonLeft);

			glColor3ub(212, 212, 212);
			glCallList(exitButtonRight);

			glPopMatrix();
		}
		else
		{
			glPushMatrix();
			glTranslatef(0, -14, 0);

			glColor3ub(238, 238, 238);
			glCallList(exitButtonInner);

			glColor3ub(0, 0, 0);
			(paused) ? glCallList(playButtonPlay) : glCallList(playButtonPause);

			glColor3ub(240, 240, 240);
			glCallList(exitButtonTop);

			glColor3ub(197, 197, 197);
			glCallList(exitButtonBottom);

			glColor3ub(209, 209, 209);
			glCallList(exitButtonLeft);

			glColor3ub(235, 235, 235);
			glCallList(exitButtonRight);

			glPopMatrix();
		}
	}

	int ButtonPressCheck(int x, int y)
	{
		GLint viewport[4];
		GLubyte pixelColor[3], exitColor = 10, playColor = 20;

		glClear(GL_COLOR_BUFFER_BIT);
		glPushAttrib(GL_VIEWPORT_BIT);
		glGetIntegerv(GL_VIEWPORT, viewport);

		glViewport(viewport[0] + viewport[2] * (1 - 0.1526), viewport[1], viewport[2] * 0.1526, viewport[3]);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, 18, 0, 100);
		glMatrixMode(GL_MODELVIEW);

		glColor3ub(exitColor, 0, 0);
		glRectf(exitButtonBorders[0][0], exitButtonBorders[0][1], exitButtonBorders[1][0], exitButtonBorders[1][1]);
		
		glPushMatrix();
		glTranslatef(0, -14, 0);
		glColor3ub(playColor, 0, 0);
		glRectf(exitButtonBorders[0][0], exitButtonBorders[0][1], exitButtonBorders[1][0], exitButtonBorders[1][1]);
		glPopMatrix();
		
		glFlush();

		glReadBuffer(GL_BACK);
		glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixelColor);
		glPopAttrib();

		if (pixelColor[0] == exitColor)
		{
			return EXIT_BUTTON;
		}
		else if (pixelColor[0] == playColor)
		{
			return PLAY_BUTTON;
		}
		else
		{
			return -1;
		}

	}

	void Run()
	{
		if ((double)(clock() - timerStart) / CLOCKS_PER_SEC >= delay)
		{
			timerStart = clock();
			glutPostRedisplay();
			Rule gameOfLife1(POPULATED, LESS_THAN, 2, UNPOPULATED);
			Rule gameOfLife2(POPULATED, GREATER_THAN, 3, UNPOPULATED);
			Rule gameOfLife3(UNPOPULATED, EQUAL_TO, 3, POPULATED);
			int i, j;
			for (i = 0; i < GRID_MAX; i++)
			{
				for (j = 0; j < GRID_MAX; j++)
				{
					gameOfLife1.AppyRule(i, j);
					gameOfLife2.AppyRule(i, j);
					gameOfLife3.AppyRule(i, j);
				}
			}
			CM.Update();
		}
	}

	void exitAutomaton()
	{
		glutPostRedisplay();
		glDeleteLists(listsBase, numOfLists);
		glutMouseFunc(NULL);
		glutMotionFunc(NULL);
		glutReshapeFunc(NULL);
		glutIdleFunc(ViewStart::HandOver);
	}

	void Mouse::Setup(int button, int state, int x, int y)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			int i, j;
			double xWorld = x, yWorld = y;

			WindowToWorldCoordinates(xWorld, yWorld);

			if (CM(xWorld, yWorld) == UNPOPULATED)
			{
				CM.invert(xWorld, yWorld);
				glutMotionFunc(MouseMotion::PopulateCells);
				glutPostRedisplay();
			}
			else if (CM(xWorld, yWorld) == POPULATED)
			{
				CM.invert(xWorld, yWorld);
				glutMotionFunc(MouseMotion::UnpopulateCells);
				glutPostRedisplay();
			}
			else
			{
				int pressedButton = ButtonPressCheck(x, WindowHeight - y);
				if (pressedButton == EXIT_BUTTON)
				{
					Draw::exitButtonDown = TRUE;
					glutPostRedisplay();
				}
				else if (pressedButton == PLAY_BUTTON)
				{
					Draw::playButtonDown = TRUE;
					glutPostRedisplay();
				}
			}
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			if (Draw::playButtonDown)
			{
				Draw::playButtonDown = FALSE;
				paused = FALSE;
				timerStart = clock();
				glutIdleFunc(Run);
				glutMouseFunc(Mouse::Running);
			}
			else if (Draw::exitButtonDown)
			{
				Draw::exitButtonDown = FALSE;
				exitAutomaton();
			}
			else
			{
				glutMotionFunc(NULL);
			}
		}
	}

	void Mouse::Running(int button, int state, int x, int y)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			Sleep(10);
			int pressedButton = ButtonPressCheck(x, WindowHeight - y);
			if (pressedButton == EXIT_BUTTON)
			{
				Draw::exitButtonDown = TRUE;
				glutPostRedisplay();
			}
			else if (pressedButton == PLAY_BUTTON)
			{
				Draw::playButtonDown = TRUE;
			}
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			if (Draw::playButtonDown)
			{
				Draw::playButtonDown = FALSE;
				paused = TRUE;
				glutIdleFunc(NULL);
				glutMouseFunc(Setup);
			}
			else if (Draw::exitButtonDown)
			{
				Draw::exitButtonDown = FALSE;
				exitAutomaton();
			}
		}
	}

	void MouseMotion::PopulateCells(int x, int y)
	{
		double xWorld = x, yWorld = y;
		WindowToWorldCoordinates(xWorld, yWorld);
		if (CM(xWorld, yWorld) == UNPOPULATED)
		{
			CM.Update(xWorld, yWorld, POPULATED);
			glutPostRedisplay();
		}
	}

	void MouseMotion::UnpopulateCells(int x, int y)
	{
		double xWorld = x, yWorld = y;
		WindowToWorldCoordinates(xWorld, yWorld);
		if (CM(xWorld, yWorld) == POPULATED)
		{
			CM.Update(xWorld, yWorld, UNPOPULATED);
			glutPostRedisplay();
		}
	}

	void Draw::Grid()
	{
		glColor3ub(115, 115, 115);
		glPushMatrix();
		for (int i = 0; i < GRID_MAX; i++)
		{
			glTranslatef(i, 0, 0);
			glCallList(gridLineV);
			glTranslatef(-i, i, 0);
			glCallList(gridLineH);
			glTranslatef(0, -i, 0);
		}
	}

	void Draw::FilledCells()
	{
		int i, j;
		glColor3ub(84, 200, 204);
		for (i = 0; i < GRID_MAX; i++)
			for (j = 0; j < GRID_MAX; j++)
				if (CM(i, j) == POPULATED)
				{
					glPushMatrix();
					glTranslatef(i, j, 0);
					glCallList(cell);
					glPopMatrix();
				}
	}
}