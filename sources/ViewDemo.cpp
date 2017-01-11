#include"ViewDemo.h"

namespace ViewDemo
{
	double VRwidth, VRheight, px;
	double const WHRatio = 800.0 / 600.0;
	GLuint numOfLists, listsBase, grid, cell, buttonReleased, buttonPressed, backButtonPressed, backButtonReleased;
	int Draw::prevButtonDown, Draw::nextButtonDown, Draw::backButtonDown, Draw::Page, Draw::Page2FirstRun, Draw::Page4FirstRun, Draw::Page5FirstRun;
	Textures *tex;
	Cell cm;
	clock_t timerStart;

#define PREV_BUTTON 0
#define NEXT_BUTTON 1
#define BACK_BUTTON 2
#define TEX_D_PAGE1 0
#define TEX_D_PAGE2 1
#define TEX_D_PAGE3 2
#define TEX_D_PAGE4 3
#define TEX_D_PAGE5 4
#define TEX_B_PREV 5
#define TEX_B_NEXT 6
#define TEX_B_BACK 7

	void HandOver()
	{
		Initialize();
		glutReshapeFunc(Reshape);
		glutDisplayFunc(Display);
		glutMouseFunc(Mouse::Mouse);
		glutReshapeWindow(WindowWidth, WindowHeight);
		glutIdleFunc(NULL);
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

			glViewport(0, (h / 2) - ((GLsizei)(w / WHRatio) / 2), w, (GLsizei)(w / WHRatio));
		px = VRheight / (w / WHRatio);
		glutPostRedisplay();
	}

	void Initialize()
	{
		if (WindowWidth < 800 || WindowHeight < 600)
		{
			WindowWidth = 800; WindowHeight = 600;
		}
		VRwidth = 80;
		VRheight = 60;
		Reshape(WindowWidth, WindowHeight);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, VRwidth, 0, VRheight);
		glMatrixMode(GL_MODELVIEW);
		glClearColor(0.1725f, 0.1725f, 0.1725f, 1.0f);

		cm.Initialize(32);
		Draw::prevButtonDown = FALSE, Draw::nextButtonDown = FALSE, Draw::backButtonDown = FALSE;
		Draw::Page = 1;

		GLuint i;
		numOfLists = 6;
		listsBase = glGenLists(numOfLists);

		i = 0;

		glNewList(cell = listsBase + i++, GL_COMPILE);
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(1, 0);
		glVertex2f(1, 1);
		glVertex2f(0, 1);
		glEnd();
		glEndList();

		glNewList(buttonReleased = listsBase + i++, GL_COMPILE);
		//button inner
		glColor3ub(70, 70, 70);
		glRectf(2, 38, 13, 45);
		//left border
		glColor3ub(55, 55, 55);
		glBegin(GL_QUADS);
		glVertex2f(1, 46);
		glVertex2f(2, 45);
		glVertex2f(2, 38);
		glVertex2f(1, 37);
		//right border
		glColor3ub(126, 126, 126);
		glVertex2f(13, 45);
		glVertex2f(14, 46);
		glVertex2f(14, 37);
		glVertex2f(13, 38);
		//bottom border
		glColor3ub(35, 35, 35);
		glVertex2f(2, 38);
		glVertex2f(13, 38);
		glVertex2f(14, 37);
		glVertex2f(1, 37);
		//top border
		glColor3ub(156, 156, 156);
		glVertex2f(1, 46);
		glVertex2f(14, 46);
		glVertex2f(13, 45);
		glVertex2f(2, 45);
		glEnd();
		glEndList();

		glNewList(buttonPressed = listsBase + i++, GL_COMPILE);
		//button inner
		glColor3ub(61, 61, 61);
		glRectf(2, 38, 13, 45);
		//left border
		glColor3ub(126, 126, 126);
		glBegin(GL_QUADS);
		glVertex2f(1, 46);
		glVertex2f(2, 45);
		glVertex2f(2, 38);
		glVertex2f(1, 37);
		//right border
		glColor3ub(55, 55, 55);
		glVertex2f(13, 45);
		glVertex2f(14, 46);
		glVertex2f(14, 37);
		glVertex2f(13, 38);
		//bottom border
		glColor3ub(156, 156, 156);
		glVertex2f(2, 38);
		glVertex2f(13, 38);
		glVertex2f(14, 37);
		glVertex2f(1, 37);
		//top border
		glColor3ub(35, 35, 35);
		glVertex2f(1, 46);
		glVertex2f(14, 46);
		glVertex2f(13, 45);
		glVertex2f(2, 45);
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

		grid = listsBase + i++;

		tex = new Textures(8);

		tex->LoadTexture(ExecDir + "textures/TEX_D_PAGE1", 966, 364, TEX_D_PAGE1);
		tex->MakeDList(TEX_D_PAGE1, 6, 1, 75, 27);

		tex->LoadTexture(ExecDir + "textures/TEX_D_PAGE2", 966, 364, TEX_D_PAGE2);
		tex->MakeDList(TEX_D_PAGE2, 6, 1, 75, 27);

		tex->LoadTexture(ExecDir + "textures/TEX_D_PAGE3", 966, 364, TEX_D_PAGE3);
		tex->MakeDList(TEX_D_PAGE3, 6, 1, 75, 27);

		tex->LoadTexture(ExecDir + "textures/TEX_D_PAGE4", 966, 364, TEX_D_PAGE4);
		tex->MakeDList(TEX_D_PAGE4, 6, 1, 75, 27);

		tex->LoadTexture(ExecDir + "textures/TEX_D_PAGE5", 966, 364, TEX_D_PAGE5);
		tex->MakeDList(TEX_D_PAGE5, 6, 1, 75, 27);

		tex->LoadTexture(ExecDir + "textures/TEX_B_PREV", 220, 140, TEX_B_PREV);
		tex->MakeDList(TEX_B_PREV, 2, 38, 13, 45);

		tex->LoadTexture(ExecDir + "textures/TEX_B_NEXT", 220, 140, TEX_B_NEXT);
		tex->MakeDList(TEX_B_NEXT, 2, 38, 13, 45);

		tex->LoadTexture(ExecDir + "textures/TEX_B_BACK", 140, 80, TEX_B_BACK);
		tex->MakeDList(TEX_B_BACK, 0.5, 52.5, 7.5, 56.5);
	}

	void MakeGrid()
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
		glColor3ub(255, 255, 255);
		glBegin(GL_LINE_LOOP);
		glVertex2d(0, 0);
		glVertex2d(0, len);
		glVertex2d(len, len);
		glVertex2d(len, 0);
		glEnd();
		glEndList();
	}

	void Display()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glPushMatrix();
		glTranslated(24, 28-px, 0);
		Draw::FilledCells();
		glCallList(grid);
		glPopMatrix();
		Draw::TextBox();
		Draw::Text();
		Draw::Buttons();

		glutSwapBuffers();
	}

	void DummyDisplay(){}

	void exitDemo()
	{
		glutIdleFunc(NULL);
		glutDisplayFunc(DummyDisplay);
		glDeleteLists(listsBase, numOfLists);
		delete tex;
		cm.CleanUp();
		glutMouseFunc(NULL);
	}

	void Mouse::Mouse(int button, int state, int x, int y)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			int pressedButton = ButtonPressCheck(x, WindowHeight - y);
			if (pressedButton == PREV_BUTTON)
			{
				Draw::prevButtonDown = TRUE;
				glutPostRedisplay();
			}
			else if (pressedButton == NEXT_BUTTON)
			{
				Draw::nextButtonDown = TRUE;
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
			if (Draw::prevButtonDown)
			{
				Draw::prevButtonDown = FALSE;
				glutPostRedisplay();
				Draw::Page--;
				if (Draw::Page == 1)
				{
					glutIdleFunc(NULL);
					cm.Reset();
					glutPostRedisplay();
				}
				else if (Draw::Page == 3)
				{
					glutIdleFunc(NULL);
					cm.Reset();
					cm.ClearRules();
					glutPostRedisplay();
					Draw::Page2FirstRun = TRUE;
					timerStart = clock();
					glutIdleFunc(Draw::Page2);
				}
				else if (Draw::Page == 4)
				{
					glutIdleFunc(NULL);
					cm.Reset();
					cm.ClearRules();
					cm.Update(15, 15, POPULATED);
					cm.AddRule(UNPOPULATED, GREATER_THAN | EQUAL_TO, 1, POPULATED);
					Draw::Page4FirstRun = TRUE;
					glutPostRedisplay();
					timerStart = clock();
					glutIdleFunc(Draw::Page4);
				}
			}
			else if (Draw::nextButtonDown)
			{
				Draw::nextButtonDown = FALSE;
				glutPostRedisplay();
				Draw::Page++;
				if (Draw::Page == 2)
				{
					Draw::Page2FirstRun = TRUE;
					timerStart = clock();
					glutIdleFunc(Draw::Page2);
				}
				if (Draw::Page == 4)
				{
					glutIdleFunc(NULL);
					cm.Reset();
					cm.Update(15, 15, POPULATED);
					cm.AddRule(UNPOPULATED, GREATER_THAN | EQUAL_TO, 1, POPULATED);
					Draw::Page4FirstRun = TRUE;
					glutPostRedisplay();
					timerStart = clock();
					glutIdleFunc(Draw::Page4);
				}
				if (Draw::Page == 5)
				{
					glutIdleFunc(NULL);
					cm.Reset();
					cm.ClearRules();
					for (int i = 0; i < 32; i++)
					{
						for (int j = 0; j < 32; j++)
							cm.Update(i, j, (rand() % 6 == 0) ? POPULATED : UNPOPULATED);
					}
					cm.AddRule(POPULATED, LESS_THAN, 2, UNPOPULATED);
					cm.AddRule(POPULATED, GREATER_THAN, 3, UNPOPULATED);
					cm.AddRule(UNPOPULATED, EQUAL_TO, 3, POPULATED);
					Draw::Page5FirstRun = TRUE;
					glutPostRedisplay();
					timerStart = clock();
					glutIdleFunc(Draw::Page5);
				}
			}
			else if (Draw::backButtonDown)
			{
				Draw::backButtonDown = FALSE;
				glutPostRedisplay();
				exitDemo();
				glutIdleFunc(ViewMainMenu::HandOver);
			}
		}
	}
	
	int Mouse::ButtonPressCheck(int x, int y)
	{
		GLubyte pixelColor[3], prevColor = 10, nextColor = 20, backColor = 30;
		glClear(GL_COLOR_BUFFER_BIT);

		if (Draw::Page != 1)
		{
			glColor3ub(prevColor, 0, 0);
			glRectf(1, 14, 37, 46);
		}

		if (Draw::Page != 5)
		{
			glPushMatrix();
			glTranslatef(65, 0, 0);
			glColor3ub(nextColor, 0, 0);
			glRectf(1, 14, 37, 46);
			glPopMatrix();
		}

		glColor3ub(backColor, 0, 0);
		glRectf(0, 54, 8, 59);

		glFlush();

		glReadBuffer(GL_BACK);
		glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixelColor);

		if (pixelColor[0] == prevColor)
		{
			return PREV_BUTTON;
		}
		else if (pixelColor[0] == nextColor)
		{
			return NEXT_BUTTON;
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

	void Draw::Page2()
	{
		if (Page2FirstRun || (clock() - timerStart) / CLOCKS_PER_SEC >= 2)
		{
			Page2FirstRun = FALSE;
			timerStart = clock();
			cm.Invert(15, 15);
			glutPostRedisplay();
		}
	}

	void Draw::Page4()
	{
		if (Page4FirstRun==0 || (clock() - timerStart) / CLOCKS_PER_SEC >= 2)
		{
			glutPostRedisplay();
			if (Page4FirstRun != 2)
			{
				Page4FirstRun = 2;
				return;
			}
			Page4FirstRun = FALSE;
			timerStart = clock();
			cm.ApplyRules();
		}
	}

	void Draw::Page5()
	{
		if (Page5FirstRun || (clock() - timerStart) / CLOCKS_PER_SEC >= 1)
		{
			Page5FirstRun = FALSE;
			timerStart = clock();
			cm.ApplyRules();
			glutPostRedisplay();
		}
	}

	void Draw::FilledCells()
	{
		int i, j;
		glColor3ub(84, 200, 204);
		for (i = 0; i < cm.GridSize(); i++)
			for (j = 0; j < cm.GridSize(); j++)
				if (cm.operator()(i, j) == POPULATED)
				{
					glPushMatrix();
					glTranslatef((GLfloat)i, (GLfloat)j, 0);
					glCallList(cell);
					glPopMatrix();
				}
	}

	void Draw::TextBox()
	{
		glColor3ub(255, 255, 255);
		glBegin(GL_LINE_LOOP);
		glVertex2f(6,27);
		glVertex2f(75,27);
		glVertex2f(75,1);
		glVertex2f(6,1);
		glEnd();
	}

	void Draw::Text()
	{
		if (Page == 1)
			tex->DrawTexture(TEX_D_PAGE1);
		else if(Page==2)
			tex->DrawTexture(TEX_D_PAGE2);
		else if (Page == 3)
			tex->DrawTexture(TEX_D_PAGE3);
		else if (Page == 4)
			tex->DrawTexture(TEX_D_PAGE4);
		else if (Page == 5)
			tex->DrawTexture(TEX_D_PAGE5);
	}

	inline void Draw::ScaleAbout(GLfloat x, GLfloat y, GLfloat xScale, GLfloat yScale)
	{
		glTranslatef(x, y, 0);
		glScalef(xScale, yScale, 0);
		glTranslatef(-x, -y, 0);
	}

	void Draw::Buttons()
	{
		if (Page != 1)
		{
			if (Draw::prevButtonDown)
			{
				glPushMatrix();
				ScaleAbout(7.5f, 41.5f, 0.95f, 0.95f);
				glCallList(buttonPressed);
				tex->DrawTexture(TEX_B_PREV);
				glPopMatrix();
			}
			else
			{
				glCallList(buttonReleased);
				tex->DrawTexture(TEX_B_PREV);
			}
		}

		if (Page != 5)
		{
			glPushMatrix();
			glTranslatef(65, 0, 0);
			if (Draw::nextButtonDown)
			{
				glPushMatrix();
				ScaleAbout(7.5f, 41.5f, 0.95f, 0.95f);
				glCallList(buttonPressed);
				tex->DrawTexture(TEX_B_NEXT);
				glPopMatrix();
			}
			else
			{
				glCallList(buttonReleased);
				tex->DrawTexture(TEX_B_NEXT);
			}
			glPopMatrix();
		}
		
		glPushMatrix();
		glTranslatef(0, 2, 0);
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