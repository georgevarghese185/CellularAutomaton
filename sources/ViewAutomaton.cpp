#include"ViewAutomaton.h"

namespace ViewAutomaton
{
	double VRwidth, VRheight, px;
	const double WHRatio = 680.0 / 576.0;
	GLint vp[4], automatonVP[4], sidebarVP[4];
	GLuint listsBase, grid, cell, ReleasedButton, PressedButton, exitButtonX, playButtonPlay, playButtonPause, plus, minus, delayBox;
	GLsizei numOfLists;
	int paused,Draw::exitButtonDown = FALSE, Draw::playButtonDown = FALSE, Draw::resetButtonDown = FALSE;
	clock_t timerStart;
	int delay;
	Textures *tex;
	Cell cm;

#define EXIT_BUTTON 1
#define PLAY_BUTTON 2
#define RESET_BUTTON 3
#define PLUS_BUTTON 4
#define MINUS_BUTTON 5
#define TEX_RESET 0
#define TEX_DELAY 1

	void HandOver()		//HandOver view.
	{
		paused = TRUE;
		Initialize();
		calcVPs();
		glutReshapeFunc(Reshape);
		glutDisplayFunc(Display);
		glutMouseFunc(Mouse::Setup);
		glutIdleFunc(NULL);
		glutReshapeWindow(WindowWidth, WindowHeight);
		MakeGrid();
		glutPostRedisplay();
	}

	void Reshape(int w, int h)
	{
		WindowWidth = w;
		WindowHeight = h;
		if (h * WHRatio <= w)

			glViewport((w / 2) - (GLsizei)(h * WHRatio / 2), 0, (GLsizei)(h * WHRatio), h);
		else

			glViewport(0, (h / 2) - (GLsizei)((w / WHRatio) / 2), w, (GLsizei)(w / WHRatio));

		calcVPs();

		glutPostRedisplay();
	}

	void calcVPs()		//Calculate Viewports used by some functions
	{
		glGetIntegerv(GL_VIEWPORT, vp);
		automatonVP[0] = vp[0]; automatonVP[1] = vp[1]; automatonVP[2] = (GLint)(vp[2] * (1 - 0.1526)), automatonVP[3] = vp[3];
		sidebarVP[0] = vp[0] + (GLint)(vp[2] * (1 - 0.1526)); sidebarVP[1] = vp[1]; sidebarVP[2] = (GLint)(vp[2] * 0.1526); sidebarVP[3] = vp[3];
		px = VRheight / vp[3];
	}

	void Initialize()		//Initialize variables and DLists
	{
		//srand(time(NULL));
		if (WindowWidth < 680 || WindowHeight < 576)	//Resize only if necessary
		{
			WindowWidth = 680, WindowHeight = 576;
		}
		glutReshapeWindow(WindowWidth, WindowHeight);

		VRwidth = (cm.GridSize() + (680 - 576) / ((double)576 / (double)cm.GridSize()));
		VRheight = cm.GridSize();

		delay = 100;

		glClearColor(0.1725f, 0.1725f, 0.1725f, 1.0f);
		//glClearColor(1, 1, 1, 1);
		GLuint i;
		numOfLists = 10;
		listsBase = glGenLists(numOfLists);
		
		i = 0;

		glNewList(cell = listsBase + i++, GL_COMPILE);
		glRectf(0, 0, 1, 1);
		glEndList();

		glNewList(ReleasedButton = listsBase + i++, GL_COMPILE);
		glColor3ub(238, 238, 238);
		glRectf(4, 90, 15, 96);
		glBegin(GL_QUADS);
		//top
		glColor3ub(240, 240, 240);
		glVertex2f(3, 97);
		glVertex2f(16, 97);
		glVertex2f(15, 96);
		glVertex2f(4, 96);
		//right
		glColor3ub(235, 235, 235);
		glVertex2f(15, 96);
		glVertex2f(16, 97);
		glVertex2f(16, 89);
		glVertex2f(14, 90);
		//bottom
		glColor3ub(197, 197, 197);
		glVertex2f(4, 90);
		glVertex2f(15, 90);
		glVertex2f(16, 89);
		glVertex2f(3, 89);
		//left
		glColor3ub(209, 209, 209);
		glVertex2f(3, 97);
		glVertex2f(4, 96);
		glVertex2f(4, 90);
		glVertex2f(3, 89);
		glEnd();
		glEndList();

		glNewList(PressedButton = listsBase + i++, GL_COMPILE);
		glColor3ub(222, 222, 222);
		glRectf(4, 90, 15, 96);
		glBegin(GL_QUADS);
		//top
		glColor3ub(195, 195, 195);
		glVertex2f(3, 97);
		glVertex2f(16, 97);
		glVertex2f(15, 96);
		glVertex2f(4, 96);
		//right
		glColor3ub(212, 212, 212);
		glVertex2f(15, 96);
		glVertex2f(16, 97);
		glVertex2f(16, 89);
		glVertex2f(14, 90);
		//bottom
		glColor3ub(245, 245, 245);
		glVertex2f(4, 90);
		glVertex2f(15, 90);
		glVertex2f(16, 89);
		glVertex2f(3, 89);
		//left
		glColor3ub(232, 232, 232);
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
		glColor3ub(0, 0, 0);
		glBegin(GL_TRIANGLES);
		glVertex2f(7,95);
		glVertex2f(7,91);
		glVertex2f(12,93);
		glEnd();
		glEndList();

		glNewList(playButtonPause = listsBase + i++, GL_COMPILE);
		glColor3ub(0, 0, 0);
		glRectf(7, 91, 9, 95);
		glRectf(10, 91, 12, 95);
		glEndList();

		glNewList(plus = listsBase + i++, GL_COMPILE);
		glColor3ub(200, 0, 0);
		glRectf(1, 52, 7, 54);
		glRectf(3, 50, 5, 56);
		glEndList();

		glNewList(minus = listsBase + i++, GL_COMPILE);
		glColor3ub(200, 0, 0);
		glRectf(11, 52, 17, 54);
		glEndList();

		glNewList(delayBox = listsBase + i++, GL_COMPILE);
		glColor3ub(255, 255, 255);
		glRectf(1, 57, 17, 64);
		glColor3ub(0, 0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(1, 64);
		glVertex2f(17, 64);
		glVertex2f(17, 57);
		glVertex2f(1, 57);
		glEnd();
		glEndList();

		grid = listsBase + i++;

		tex = new Textures(2);

		tex->LoadTexture(ExecDir + "textures/TEX_RESET", 220, 120, TEX_RESET);
		tex->MakeDList(TEX_RESET, 4, 90, 15, 96);

		tex->LoadTexture(ExecDir + "textures/TEX_DELAY", 120, 50, TEX_DELAY);
		tex->MakeDList(TEX_DELAY, 3, 65, 15, 70);
	}

	void MakeGrid()		//Initialize DList for square grid
	{
		double len = cm.GridSize();
		glNewList(grid, GL_COMPILE);
		//glColor3f(0.3,0.3, 0.3);
		glColor3ub(115, 115, 115);
		glBegin(GL_LINES);
		for (int i = 0; i < len; i++)
		{
			glVertex2d(i, 0);
			glVertex2d(i, len);
			glVertex2d(0, i);
			glVertex2d(len, i);
		}
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex2d(px, 0);
		glVertex2d(px, len - px);
		glVertex2d(len, len - px);
		glVertex2d(len, 0);
		glEnd();
		glEndList();
	}

	void Display()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glPushAttrib(GL_VIEWPORT_BIT);

		glViewport(automatonVP[0], automatonVP[1], automatonVP[2], automatonVP[3]);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, VRheight, 0, VRheight);
		glMatrixMode(GL_MODELVIEW);

		Draw::FilledCells();
		glCallList(grid);
		
		glFlush();

		glViewport(sidebarVP[0], sidebarVP[1], sidebarVP[2], sidebarVP[3]);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, 18, 0, 100);
		glMatrixMode(GL_MODELVIEW);

		Draw::Sidebar();
		
		glutSwapBuffers();
		glPopAttrib();
	}

	void DummyDisplay() {}		//Empty Display function. Used to fix redisplay errors during deallocation of textures

	void Run()		//Idle function for unpaused automaton
	{
		if ((double)(clock() - timerStart) / CLOCKS_PER_SEC >= (delay / 1000.0))
		{
			timerStart = clock();
			glutPostRedisplay();
			cm.ApplyRules();
		}
	}

	void exitAutomaton()	//Clean up
	{
		glutDisplayFunc(DummyDisplay);
		glDeleteLists(listsBase, numOfLists);
		glutIdleFunc(NULL);
		glutMouseFunc(NULL);
		glutMotionFunc(NULL);
		glutReshapeFunc(NULL);
		tex->~Textures();
		cm.CleanUp();
		glutIdleFunc(ViewMainMenu::HandOver);
	}

	void Mouse::Setup(int button, int state, int x, int y)	//Manually populating when CA is paused
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			double xWorld = x, yWorld = y;

			WindowToWorldCoordinates(xWorld, yWorld);

			if (cm((int)xWorld, (int)yWorld) == UNPOPULATED)
			{
				cm.Invert((int)xWorld, (int)yWorld);
				glutMotionFunc(Mouse::Motion::PopulateCells);
				glutPostRedisplay();
			}
			else if (cm((int)xWorld, (int)yWorld) == POPULATED)
			{
				cm.Invert((int)xWorld, (int)yWorld);
				glutMotionFunc(Mouse::Motion::UnpopulateCells);
				glutPostRedisplay();
			}
			else
			{
				int pressedButton = Mouse::ButtonPressCheck(x, WindowHeight - y);
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
				else if (pressedButton == RESET_BUTTON)
				{
					Draw::resetButtonDown = TRUE;
					glutPostRedisplay();
				}
				else if (pressedButton == PLUS_BUTTON)
				{
					if (delay < 10)
						delay += 5;
					else if (delay < 50)
						delay += 10;
					else
						delay += 50;
				}
				else if (pressedButton == MINUS_BUTTON)
				{
					if (delay > 50)
						delay -= 50;
					else if (delay > 10)
						delay -= 10;
					else if (delay > 5)
						delay -= 5;
				}
			}
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			if (Draw::playButtonDown)
			{
				Draw::playButtonDown = FALSE;
				glutPostRedisplay();
				paused = FALSE;
				timerStart = clock();
				glutIdleFunc(Run);
				glutMouseFunc(Mouse::Running);
			}
			else if (Draw::exitButtonDown)
			{
				Draw::exitButtonDown = FALSE;
				glutPostRedisplay();
				exitAutomaton();
			}
			else if (Draw::resetButtonDown)
			{
				Draw::resetButtonDown = FALSE;
				cm.Reset();
				glutPostRedisplay();
			}
			else
			{
				glutMotionFunc(NULL);
			}
		}
	}

	void Mouse::Running(int button, int state, int x, int y)	//Mouse callback for unpaused CA
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			int pressedButton = Mouse::ButtonPressCheck(x, WindowHeight - y);
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
			else if (pressedButton == RESET_BUTTON)
			{
				Draw::resetButtonDown = TRUE;
				glutPostRedisplay();
			}
			else if (pressedButton == PLUS_BUTTON)
			{
				if (delay < 10)
					delay += 5;
				else if (delay < 50)
					delay += 10;
				else
					delay += 50;
			}
			else if (pressedButton == MINUS_BUTTON)
			{
				if (delay > 50)
					delay -= 50;
				else if (delay > 10)
					delay -= 10;
				else if (delay > 5)
					delay -= 5;
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
				glutPostRedisplay();
			}
			else if (Draw::exitButtonDown)
			{
				Draw::exitButtonDown = FALSE;
				glutPostOverlayRedisplay();
				exitAutomaton();
			}
			else if (Draw::resetButtonDown)
			{
				Draw::resetButtonDown = FALSE;
				paused = TRUE;
				glutIdleFunc(NULL);
				glutMouseFunc(Setup);
				cm.Reset();
				glutPostRedisplay();
			}
		}
	}

	void Mouse::WindowToWorldCoordinates(double &x, double &y)		//Converts Window coordinates to world coordinates
	{
		x = (x - vp[0]) / vp[2] * VRwidth;
		y = (WindowHeight - y - vp[1]) / vp[3] * VRheight;
	}

	int Mouse::ButtonPressCheck(int x, int y)		//Check if any buttons were clicked(Uses color picking)
	{
		GLubyte pixelColor[3], exitColor = 10, playColor = 20, resetColor = 30, plusColor = 40, minusColor = 50;

		glClear(GL_COLOR_BUFFER_BIT);
		glPushAttrib(GL_VIEWPORT_BIT);

		glViewport(vp[0] + (GLsizei)(vp[2] * (1 - 0.1526)), vp[1], (GLsizei)(vp[2] * 0.1526), vp[3]);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, 18, 0, 100);
		glMatrixMode(GL_MODELVIEW);

		glColor3ub(exitColor, 0, 0);
		glRectf(3, 97, 16, 89);

		glPushMatrix();
		glTranslatef(0, -14, 0);
		glColor3ub(playColor, 0, 0);
		glRectf(3, 97, 16, 89);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, -87, 0);
		glColor3ub(resetColor, 0, 0);
		glRectf(3, 97, 16, 89);
		glPopMatrix();

		glColor3ub(plusColor, 0, 0);
		glRectf(1, 52, 7, 54);
		glRectf(3, 50, 5, 56);
		glEndList();

		glColor3ub(minusColor, 0, 0);
		glRectf(11, 52, 17, 54);

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
		else if (pixelColor[0] == resetColor)
		{
			return RESET_BUTTON;
		}
		else if (pixelColor[0] == plusColor)
		{
			return PLUS_BUTTON;
		}
		else if (pixelColor[0] == minusColor)
		{
			return MINUS_BUTTON;
		}
		else
		{
			return -1;
		}

	}

	void Mouse::Motion::PopulateCells(int x, int y)
	{
		double xWorld = x, yWorld = y;
		Mouse::WindowToWorldCoordinates(xWorld, yWorld);
		if (cm.operator()((int)xWorld, (int)yWorld) == UNPOPULATED)
		{
			cm.Update((int)xWorld, (int)yWorld, POPULATED);
			glutPostRedisplay();
		}
	}

	void Mouse::Motion::UnpopulateCells(int x, int y)
	{
		double xWorld = x, yWorld = y;
		Mouse::WindowToWorldCoordinates(xWorld, yWorld);
		if (cm.operator()((int)xWorld, (int)yWorld) == POPULATED)
		{
			cm.Update((int)xWorld, (int)yWorld, UNPOPULATED);
			glutPostRedisplay();
		}
	}

	void Draw::FilledCells()		//Color in the populated cells
	{
		glColor3ub(84, 200, 204);
		for (int i = 0; i < cm.GridSize(); i++)
			for (int j = 0; j < cm.GridSize(); j++)
				if (cm.operator()(i, j) == POPULATED)
				{
					//glColor3f((rand() % 95 + 5) / 100.0, (rand() % 95 + 5) / 100.0, (rand() % 95 + 5) / 100.0);
					glPushMatrix();
					glTranslatef((GLfloat)i, (GLfloat)j, 0);
					glCallList(cell);
					glPopMatrix();
				}
	}

	inline void Draw::ScaleAbout(double x, double y, double xScale, double yScale)	//Used for scaling about a point x,y
	{
		glTranslated(x, y, 0);
		glScaled(xScale, yScale, 0);
		glTranslated(-x, -y, 0);
	}

	void Draw::Sidebar()	//Draw the sidebar
	{
		if (exitButtonDown)
		{
			glPushMatrix();
			ScaleAbout(9.5, 93, 0.95, 0.95);
			glCallList(PressedButton);
			glCallList(exitButtonX);
			glPopMatrix();
		}
		else
		{
			glCallList(ReleasedButton);
			glCallList(exitButtonX);
		}

		if (playButtonDown)
		{
			glPushMatrix();
			glTranslatef(0, -14, 0);
			ScaleAbout(9.5, 93, 0.95, 0.95);
			glCallList(PressedButton);
			(paused) ? glCallList(playButtonPlay) : glCallList(playButtonPause);
			glPopMatrix();
		}
		else
		{
			glPushMatrix();
			glTranslatef(0, -14, 0);
			glCallList(ReleasedButton);
			(paused) ? glCallList(playButtonPlay) : glCallList(playButtonPause);
			glPopMatrix();
		}

		if (resetButtonDown)
		{
			glPushMatrix();
			glTranslatef(0, -87, 0);
			ScaleAbout(9.5, 93, 0.95, 0.95);
			glCallList(PressedButton);
			tex->DrawTexture(TEX_RESET);
			glPopMatrix();
		}
		else
		{
			glPushMatrix();
			glTranslatef(0, -87, 0);
			glCallList(ReleasedButton);
			tex->DrawTexture(TEX_RESET);
			glPopMatrix();
		}

		glCallList(plus);
		glCallList(minus);
		glCallList(delayBox);
		tex->DrawTexture(TEX_DELAY);
		
		glPushMatrix();
		glTranslatef(2, 58.5, 0);
		string d = to_string((int)(delay));
		d.append("ms");
		glColor3ub(0, 0, 0);
		glScalef(0.033f, 0.033f, 0);
		for (unsigned int i = 0; i < d.size();i++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN,d[i]);
		glPopMatrix();
	}
}