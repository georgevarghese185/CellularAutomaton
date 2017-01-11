#include"ViewAutomaton.h"

namespace ViewAutomaton
{
	int paused, gridLineV, gridLineH, cell, startButton, playSymbol, pauseSymbol;
	float barX0, barY0, barX1, barY1, barWidth, barHeight, startBorder[4][2], startOffsetX, startOffsetY;


	void Initialize()
	{
		int i;

		WindowWidth = 590, WindowHeight = 500;								//From "WindowWorldGlobals.h" Set default width and height. (500x500 for cell grid, 90 extra pixels wide for sidebar)
		WidthHeightRatio = (double)WindowWidth / (double)WindowHeight;		//From "WindowWorldGlobals.h" used for reshaping and coordinate calculations

		VRwidth = (GRID_MAX + (WindowWidth - WindowHeight) / ((double)WindowHeight / (double)GRID_MAX));		//From "WindowWorldGlobals.h" for reshaping and coordinate calculations
		VRheight = GRID_MAX;		//same
		CM.Initialize(GRID_MAX);	//Initialzing cellmap (CellMap.h) for holding cell live/dead state.

		glMatrixMode(GL_PROJECTION);					//Set viewing area
		glLoadIdentity();
		gluOrtho2D(0, VRwidth, 0, VRheight);
		glMatrixMode(GL_MODELVIEW);
		glClearColor(1, 1, 1, 1);
		glutReshapeWindow(WindowWidth, WindowHeight);	//Resize window

		barX0 = GRID_MAX;		//initializing sidebar boundaries
		barX1 = VRwidth;
		barY0 = 0;
		barY1 = VRheight;
		barWidth = barX1 - barX0;		//Sidebar width and height (for button placement calculations)
		barHeight = barY1 - barY0;

		startBorder[0][0] = barX0 + 0.05 *barWidth; startBorder[0][1] = barY0 + 0.9 *barHeight;			//4 vertices of play/pause button. Vertices taken in forms of %'s to be independant from variable grid size
		startBorder[1][0] = barX0 + 0.95 *barWidth; startBorder[1][1] = barY0 + 0.9 *barHeight;	
		startBorder[2][0] = barX0 + 0.95 *barWidth; startBorder[2][1] = barY0 + 0.8 *barHeight;
		startBorder[3][0] = barX0 + 0.05 *barWidth; startBorder[3][1] = barY0 + 0.8 *barHeight;
		int startLength = startBorder[1][0] - startBorder[0][0], startHeight = startBorder[1][1] - startBorder[2][1];

		startOffsetX = startLength * 0.1 / 2;			//Offset of smaller inner box of start button. Offset used in accordance with scaling and transformation
		startOffsetY = startHeight * 0.1 / 2;
		startOffsetX = startBorder[3][0] - 0.9*startBorder[3][0] + startOffsetX;
		startOffsetY = startBorder[3][1] - 0.9*startBorder[3][1] + startOffsetY;

		glNewList(gridLineV = glGenLists(1), GL_COMPILE);	//Display list for vertical line for grid
		glBegin(GL_LINES);
		glVertex2f(0, 0);
		glVertex2f(0, GRID_MAX);
		glEnd();
		glEndList();

		glNewList(gridLineH = glGenLists(1), GL_COMPILE);	//DL for horizontal grid line
		glBegin(GL_LINES);
		glVertex2f(0, 0);
		glVertex2f(GRID_MAX, 0);
		glEnd();
		glEndList();

		glNewList(cell = glGenLists(1), GL_COMPILE);		//DL for single live cell
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(1, 0);
		glVertex2f(1, 1);
		glVertex2f(0, 1);
		glEnd();
		glEndList();

		glNewList(startButton = glGenLists(1), GL_COMPILE);	//DL for start button(outer or inner rectangle)
		glBegin(GL_QUADS);
		for (i = 0; i < 4; i++) glVertex2fv(startBorder[i]);
		glEnd();
		glEndList();

		glNewList(playSymbol = glGenLists(1), GL_COMPILE);	//DL for play symbol
		glBegin(GL_TRIANGLES);
		glVertex2f(startBorder[0][0] + 0.2*startLength, startBorder[0][1] - 0.05*startHeight);
		glVertex2f(startBorder[3][0] + 0.2*startLength, startBorder[3][1] + 0.05*startHeight);
		glVertex2f(startBorder[1][0] - 0.2*startLength, startBorder[3][1] + 0.5*startHeight);
		glEnd();
		glEndList();

		glNewList(pauseSymbol = glGenLists(1), GL_COMPILE);	//DL for pause symbol
		glBegin(GL_QUADS);
		glVertex2f(startBorder[0][0] + startLength * 0.3, startBorder[0][1] - startHeight * 0.1);
		glVertex2f(startBorder[0][0] + startLength * 0.45, startBorder[0][1] - startHeight * 0.1);
		glVertex2f(startBorder[0][0] + startLength * 0.45, startBorder[2][1] + startHeight * 0.1);
		glVertex2f(startBorder[0][0] + startLength * 0.3, startBorder[2][1] + startHeight * 0.1);

		glVertex2f(startBorder[0][0] + startLength * 0.6, startBorder[0][1] - startHeight * 0.1);
		glVertex2f(startBorder[0][0] + startLength * 0.75, startBorder[0][1] - startHeight * 0.1);
		glVertex2f(startBorder[0][0] + startLength * 0.75, startBorder[2][1] + startHeight * 0.1);
		glVertex2f(startBorder[0][0] + startLength * 0.6, startBorder[2][1] + startHeight * 0.1);
		glEnd();
		glEndList();
	}

	void HandOver()
	{
		cout << "Enter Sqaure Grid Size: ";		//Get grid size from user
		cin >> GRID_MAX;

		paused = TRUE;	//initially, Automaton not running
		glutCreateWindow("Cellular Automaton 1.2");
		Initialize();
		glutReshapeFunc(Reshape);
		glutDisplayFunc(Display);
		glutMouseFunc(Mouse::Setup);
	}

	void Display()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		Draw::FilledCells();

		Draw::Grid();

		Draw::StartButton();

		glFlush();
	}

	void ButtonPressCheck(double x, double y)
	{
		if (StartButtonPressed(x, y))
		{
			paused = FALSE;
			glutIdleFunc(Run);	//Starts processing automaton's state changes during idle time.
			glutMouseFunc(Mouse::Running);
		}
	}

	int StartButtonPressed(double x, double y)
	{
		if (x >= startBorder[0][0] && x <= startBorder[1][0] && y >= startBorder[2][1] && y <= startBorder[1][1])	//check if x and y within start buttons boundaries.
			return TRUE;
		else
			return FALSE;
	}

	void Run()
	{
		Rule gameOfLife1(POPULATED, LESS_THAN, 2, UNPOPULATED);
		Rule gameOfLife2(POPULATED, GREATER_THAN, 3, UNPOPULATED);
		Rule gameOfLife3(UNPOPULATED, EQUAL_TO, 3, POPULATED);
		int i, j;
		Sleep(100);
		CM.Update();
		glutPostRedisplay();
		for (i = 0; i < GRID_MAX; i++)
		{
			for (j = 0; j < GRID_MAX; j++)
			{
				gameOfLife1.AppyRule(i, j);
				gameOfLife2.AppyRule(i, j);
				gameOfLife3.AppyRule(i, j);
			}
		}
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
				ButtonPressCheck(xWorld, yWorld);
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			glutMotionFunc(NULL);
		}
	}

	void Mouse::Running(int button, int state, int x, int y)
	{
		if (button == GLUT_LEFT && state == GLUT_DOWN)
		{
			double xWorld = x, yWorld = y;
			WindowToWorldCoordinates(xWorld, yWorld);
			if (StartButtonPressed(xWorld, yWorld))
			{
				paused = TRUE;
				glutIdleFunc(NULL);
				glutMouseFunc(Setup);
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
		glColor3f(0.8, 0.8, 0.8);
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
		glColor3f(1, 1, 0);
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

	void Draw::StartButton()
	{
		glColor3f(0, 0, 0);
		glCallList(startButton);

		glPushMatrix();
		glTranslatef(startOffsetX, startOffsetY, 0);
		glScalef(0.9, 0.9, 0);
		glColor3f(0.5, 0.5, 0.5);
		glCallList(startButton);
		glColor3f(0, 0, 0);
		if (paused)
			glCallList(playSymbol);
		else
			glCallList(pauseSymbol);
		glPopMatrix();

	}
}