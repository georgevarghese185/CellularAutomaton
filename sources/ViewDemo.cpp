#include"ViewDemo.h"

namespace ViewDemo
{
	double VRwidth, VRheight, px;
	double const WHRatio = 800.0 / 600.0;
	GLuint numOfLists, listsBase, grid, cell;
	int Draw::Page, Draw::Page2FirstRun, Draw::Page4FirstRun, Draw::Page5FirstRun;
	Textures *tex;
	Buttons *buttons;
	Cell cm;
	clock_t timerStart;

#define BUTTON 0
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
		glutMouseFunc(Mouse);
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

		cm.Initialize(32); Draw::Page = 1;

		GLuint i=0;
		numOfLists = 2;
		listsBase = glGenLists(numOfLists);

		glNewList(cell = listsBase + i++, GL_COMPILE);
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(1, 0);
		glVertex2f(1, 1);
		glVertex2f(0, 1);
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
		tex->MakeDList(TEX_B_NEXT, 67, 38, 78, 45);

		tex->LoadTexture(ExecDir + "textures/TEX_B_BACK", 140, 80, TEX_B_BACK);
		tex->MakeDList(TEX_B_BACK, 1, 52.5, 8, 56.5);

		buttons = new Buttons(3);
		buttons->MakeButtonGraphic(BUTTON, 0, 0, 13, 9, 1, 1, 12, 8,
			Color(61, 61, 61), Color(35, 35, 35), Color(126, 126, 126), Color(156, 156, 156), Color(55, 55, 55),
			Color(70, 70, 70), Color(156, 156, 156), Color(35, 35, 35), Color(55, 55, 55), Color(126, 126, 126));
		buttons->MakeButtonGraphic(BACK_BUTTON, 0, 0, 8, 5, 0.5, 0.5, 7.5, 4.5,
			Color(61, 61, 61), Color(35, 35, 35), Color(126, 126, 126), Color(55, 55, 55), Color(156, 156, 156),
			Color(70, 70, 70), Color(156, 156, 156), Color(35, 35, 35), Color(55, 55, 55), Color(126, 126, 126));
		buttons->MakeButton(BACK_BUTTON, 0.5, 52, 8.5, 57, BACK_BUTTON);
		buttons->MakeButton(PREV_BUTTON, 1, 37, 14, 46, BUTTON);
		buttons->MakeButton(NEXT_BUTTON, 66, 37, 79, 46, BUTTON);
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
		if (Draw::Page != 5) buttons->DrawButton(NEXT_BUTTON, TEX_B_NEXT, tex);
		if (Draw::Page != 1) buttons->DrawButton(PREV_BUTTON, TEX_B_PREV, tex);
		buttons->DrawButton(BACK_BUTTON, TEX_B_BACK, tex);

		glutSwapBuffers();
	}

	void DummyDisplay(){}

	void exitDemo()
	{
		glutIdleFunc(NULL);
		glutDisplayFunc(DummyDisplay);
		glDeleteLists(listsBase, numOfLists);
		delete tex;
		delete buttons;
		cm.CleanUp();
		glutMouseFunc(NULL);
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
			if (pressedButton == PREV_BUTTON && Draw::Page != 1)
			{
				Draw::Page--;
				if (Draw::Page == 1)
				{
					glutIdleFunc(NULL);
					cm.Reset();
				}
				else if (Draw::Page == 3)
				{
					glutIdleFunc(NULL);
					cm.Reset();
					cm.ClearRules();
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
					timerStart = clock();
					glutIdleFunc(Draw::Page4);
				}
			}
			else if (pressedButton == NEXT_BUTTON && Draw::Page != 5)
			{
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
					timerStart = clock();
					glutIdleFunc(Draw::Page5);
				}
			}
			else if (pressedButton == BACK_BUTTON)
			{
				exitDemo();
				glutIdleFunc(ViewMainMenu::HandOver);
			}
			glutPostRedisplay();
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
}