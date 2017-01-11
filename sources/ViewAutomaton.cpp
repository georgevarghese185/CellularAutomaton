#include"ViewAutomaton.h"

namespace ViewAutomaton
{
	Buttons2::Buttons2(int numOfButtons):Buttons(numOfButtons){}
	
	void Buttons2::DrawPlayButton(int buttonName,int paused)
	{
		if (_buttonDown[buttonName])
		{
			glPushMatrix();
			glTranslated(_buttonCenter[buttonName][0], _buttonCenter[buttonName][1], 0);
			glScaled(0.95, 0.95, 0);
			glTranslated(-_buttonCenter[buttonName][0], -_buttonCenter[buttonName][1], 0);
			glPushMatrix(); glTranslatef(_buttonBorders[buttonName][0], _buttonBorders[buttonName][1], 0);
			glCallList(_buttonGraphic[_button[buttonName]][1]); glPopMatrix();
			(paused) ? glCallList(playButtonPlay) : glCallList(playButtonPause);
			glPopMatrix();
		}
		else
		{
			glPushMatrix(); glTranslatef(_buttonBorders[buttonName][0], _buttonBorders[buttonName][1], 0);
			glCallList(_buttonGraphic[_button[buttonName]][0]); glPopMatrix();
			(paused) ? glCallList(playButtonPlay) : glCallList(playButtonPause);
		}
	}

	double VRwidth, VRheight, px;
	const double WHRatio = 680.0 / 576.0;
	GLint vp[4], automatonVP[4], sidebarVP[4];
	GLuint listsBase, grid, cell, exitButtonX, playButtonPlay, playButtonPause, plus, minus, delayBox;
	GLsizei numOfLists;
	clock_t timerStart;
	int delay;
	bool paused;
	Textures *tex;
	Buttons2 *buttons;
	Cell cm;

#define BUTTON 0
#define EXIT_BUTTON 0
#define PLAY_BUTTON 1
#define RESET_BUTTON 2
#define PLUS_BUTTON 3
#define MINUS_BUTTON 4
#define TEX_RESET 0
#define TEX_DELAY 1

	void HandOver()		//HandOver view.
	{
		paused = true;
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
		if (WindowWidth < 680 || WindowHeight < 576)	//Resize only if necessary
		{
			WindowWidth = 680, WindowHeight = 576;
		}
		glutReshapeWindow(WindowWidth, WindowHeight);

		VRwidth = (cm.GridSize() + (680 - 576) / ((double)576 / (double)cm.GridSize()));
		VRheight = cm.GridSize();

		delay = 100;

		glClearColor(0.1725f, 0.1725f, 0.1725f, 1.0f);
		GLuint i;
		numOfLists = 8;
		listsBase = glGenLists(numOfLists);
		
		i = 0;

		glNewList(cell = listsBase + i++, GL_COMPILE);
		glRectf(0, 0, 1, 1);
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
		glVertex2f(7,81);
		glVertex2f(7,77);
		glVertex2f(12,79);
		glEnd();
		glEndList();

		glNewList(playButtonPause = listsBase + i++, GL_COMPILE);
		glColor3ub(0, 0, 0);
		glRectf(7, 77, 9, 81);
		glRectf(10, 77, 12, 81);
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
		tex->MakeDList(TEX_RESET, 4, 3, 15, 9);

		tex->LoadTexture(ExecDir + "textures/TEX_DELAY", 120, 50, TEX_DELAY);
		tex->MakeDList(TEX_DELAY, 3, 65, 15, 70);

		buttons = new Buttons2(5);
		buttons->MakeButtonGraphic(BUTTON, 0, 0, 13, 8, 1, 1, 12, 7, 
			Color(222, 222, 222), Color(195, 195, 195), Color(245, 245, 245), Color(232, 232, 232), Color(212, 212, 212),
			Color(238, 238, 238), Color(240, 240, 240), Color(197, 197, 197), Color(209, 209, 209), Color(235, 235, 235));
		
		buttons->MakeButton(EXIT_BUTTON, 3, 89, 16, 97, BUTTON);
		buttons->MakeButton(PLAY_BUTTON, 3, 89 - 14, 16, 97 - 14,BUTTON);
		buttons->MakeButton(RESET_BUTTON, 3, 89 - 87, 16, 97 - 87, BUTTON);
		buttons->MakeButton(PLUS_BUTTON, 1, 50, 7, 56, NULL);
		buttons->MakeButton(MINUS_BUTTON, 11, 50, 17, 56, NULL);
		
	}

	void MakeGrid()		//Initialize DList for square grid
	{
		double len = cm.GridSize();
		glNewList(grid, GL_COMPILE);
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
		delete tex;
		delete buttons;
		cm.CleanUp();
		glutIdleFunc(ViewMainMenu::HandOver);
	}

	void Mouse::Setup(int button, int state, int x, int y)	//Manually populating when CA is paused
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (paused)
			{
				double xWorld = x, yWorld = y;
				WindowToWorldCoordinates(xWorld, yWorld);

				if (cm((int)xWorld, (int)yWorld) == UNPOPULATED)
				{
					cm.Invert((int)xWorld, (int)yWorld);
					glutMotionFunc(Mouse::Motion::PopulateCells);
					glutPostRedisplay(); return;
				}
				else if (cm((int)xWorld, (int)yWorld) == POPULATED)
				{
					cm.Invert((int)xWorld, (int)yWorld);
					glutMotionFunc(Mouse::Motion::UnpopulateCells);
					glutPostRedisplay(); return;
				}
			}
			Mouse::ButtonPressCheck(x, WindowHeight - y);
			glutPostRedisplay();
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			int pressedButton = Mouse::ButtonPressCheck(x, WindowHeight - y);
			buttons->ReleaseButtons();
			
			if (pressedButton == EXIT_BUTTON)
				exitAutomaton();
			else if (pressedButton == PLAY_BUTTON)
			{
				if (paused)
				{
					paused = false;
					timerStart = clock();
					glutIdleFunc(Run);
				}
				else
				{
					paused = true;
					glutIdleFunc(NULL);
				}
			}
			else if (pressedButton == RESET_BUTTON)
			{
				cm.Reset();
				paused = true;
				glutIdleFunc(NULL);
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
			glutPostRedisplay();
		}
	}

	void Mouse::WindowToWorldCoordinates(double &x, double &y)		//Converts Window coordinates to world coordinates
	{
		x = (x - vp[0]) / vp[2] * VRwidth;
		y = (WindowHeight - y - vp[1]) / vp[3] * VRheight;
	}

	int Mouse::ButtonPressCheck(int x, int y)		//Check if any buttons were clicked(Uses color picking)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glPushAttrib(GL_VIEWPORT_BIT);

		glViewport(sidebarVP[0],sidebarVP[1],sidebarVP[2],sidebarVP[3]);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, 18, 0, 100);
		glMatrixMode(GL_MODELVIEW);
		int pressedButton = buttons->PressButton(x, y);

		glPopAttrib();
		return pressedButton;
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
					glPushMatrix();
					glTranslatef((GLfloat)i, (GLfloat)j, 0);
					glCallList(cell);
					glPopMatrix();
				}
	}

	void Draw::Sidebar()	//Draw the sidebar
	{
		buttons->DrawButton(EXIT_BUTTON, exitButtonX, NULL);
		buttons->DrawPlayButton(PLAY_BUTTON, paused);
		buttons->DrawButton(RESET_BUTTON, TEX_RESET, tex);

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