#include<GL\glut.h>
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<ctime>
#include<Windows.h>

#define POPULATED 1
#define UNPOPULATED 0
#define LESS_THAN 8
#define EQUAL_TO 4
#define NOT_EQUAL_TO 2
#define GREATER_THAN 1

using namespace std;

int GRID_MAX, CApaused = 1;
GLint WindowWidth = 590, WindowHeight = 500;
double WidthHeightRatio = (double)WindowWidth / (double)WindowHeight;
double VRwidth, VRheight;
float startButton[4];

class CellMap

{
	int **_cellMap;
	vector<int> _updateList;
public:

	void Initialize(int size)

	{
		_cellMap = new int*[size];
		for (int i = 0; i < GRID_MAX; i++)
			_cellMap[i] = new int[size]();
	}

	int operator() (int x, int y)

	{
		if (InBounds(x, y))
			return _cellMap[x][y];
		else
			return -1;
	}

	int Neighbourhood(int x, int y)
	{
		return(
			(InBounds(x - 1, y - 1) ? CM(x - 1, y - 1) : 0)
			+ (InBounds(x - 1, y) ? CM(x - 1, y) : 0)
			+ (InBounds(x - 1, y + 1) ? CM(x - 1, y + 1) : 0)
			+ (InBounds(x, y - 1) ? CM(x, y - 1) : 0)
			+ (InBounds(x, y + 1) ? CM(x, y + 1) : 0)
			+ (InBounds(x + 1, y - 1) ? CM(x + 1, y - 1) : 0)
			+ (InBounds(x + 1, y) ? CM(x + 1, y) : 0)
			+ (InBounds(x + 1, y + 1) ? CM(x + 1, y + 1) : 0)
			);
	}

	void Set(int x, int y, int populationType)

	{
		_updateList.push_back(x);
		_updateList.push_back(y);
		_updateList.push_back(populationType);
	}

	void Update()
	{
		for (int i = 0; i < _updateList.size(); i += 3)
			_cellMap[_updateList[i]][_updateList[i + 1]] = _updateList[i + 2];
		_updateList.clear();
	}

	void Update(int x, int y, int populationState)
	{
		if (InBounds(x, y))
			_cellMap[x][y] = populationState;
	}

	void invert(int x, int y)

	{
		_cellMap[x][y] = (_cellMap[x][y] == POPULATED) ? UNPOPULATED : POPULATED;
	}

	int InBounds(int x, int y)
	{
		if (x >= 0 && y >= 0 && x < GRID_MAX && y < GRID_MAX)
			return TRUE;
		else
			return FALSE;
	}

	~CellMap()

	{
		for (int i = 0; i < GRID_MAX; i++)
			delete[] _cellMap[i];
		delete _cellMap;
	}
}CM;

class Rule
{
	int _populationState, _conditionType, _neighbourCount, _result;

public:
	Rule(int populationState, int conditionType, int neighbourCount, int result)

	{
		_populationState = populationState;
		_neighbourCount = neighbourCount;
		_conditionType = conditionType;
		_result = result;
	}

	void AppyRule(int x, int y)

	{
		if (CM(x, y) == _populationState)
		{
			int c = 0;
			int count = CM.Neighbourhood(x, y);

			if (count < _neighbourCount)
				c = c | LESS_THAN;
			if (count == _neighbourCount)
				c = c | EQUAL_TO;
			if (count > _neighbourCount)
				c = c | GREATER_THAN;

			if (c == _conditionType)
				CM.Set(x, y, _result);
		}
	}
};

void Reshape(int, int);
void WindowToWorldCoordinates(double &x, double &y);

class ViewAutomaton
{
	static int _paused, _gridLineV, _gridLineH, _cell, _startButton, _playSymbol, _pauseSymbol;
	static float _barX0, _barY0, _barX1, _barY1, _barWidth, _barHeight, _startBorder[4][2], _startOffsetX, _startOffsetY;


	static void Initialize()
	{
		int i;

		VRwidth = (GRID_MAX + (WindowWidth - WindowHeight) / ((double)WindowHeight / (double)GRID_MAX));
		VRheight = GRID_MAX;
		CM.Initialize(GRID_MAX);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, VRwidth, 0, VRheight);
		glMatrixMode(GL_MODELVIEW);
		glClearColor(1, 1, 1, 1);

		_barX0 = GRID_MAX;
		_barX1 = VRwidth;
		_barY0 = 0;
		_barY1 = VRheight;
		_barWidth = _barX1 - _barX0;
		_barHeight = _barY1 - _barY0;

		_startBorder[0][0] = _barX0 + 0.05 *_barWidth;
		_startBorder[0][1] = _barY0 + 0.9 *_barHeight;
		_startBorder[1][0] = _barX0 + 0.95 *_barWidth;
		_startBorder[1][1] = _barY0 + 0.9 *_barHeight;
		_startBorder[2][0] = _barX0 + 0.95 *_barWidth;
		_startBorder[2][1] = _barY0 + 0.8 *_barHeight;
		_startBorder[3][0] = _barX0 + 0.05 *_barWidth;
		_startBorder[3][1] = _barY0 + 0.8 *_barHeight;
		int startLength = _startBorder[1][0] - _startBorder[0][0], startHeight = _startBorder[1][1] - _startBorder[2][1];

		int startBorderLength = _startBorder[1][0] - _startBorder[0][0];
		int startBorderHeight = _startBorder[1][1] - _startBorder[2][1];
		_startOffsetX = startBorderLength * 0.1 / 2;
		_startOffsetY = startBorderHeight * 0.1 / 2;
		_startOffsetX = _startBorder[3][0] - 0.9*_startBorder[3][0] + _startOffsetX;
		_startOffsetY = _startBorder[3][1] - 0.9*_startBorder[3][1] + _startOffsetY;

		glNewList(_gridLineV = glGenLists(1), GL_COMPILE);
		glBegin(GL_LINES);
		glVertex2f(0, 0);
		glVertex2f(0, GRID_MAX);
		glEnd();
		glEndList();

		glNewList(_gridLineH = glGenLists(1), GL_COMPILE);
		glBegin(GL_LINES);
		glVertex2f(0, 0);
		glVertex2f(GRID_MAX, 0);
		glEnd();
		glEndList();

		glNewList(_cell = glGenLists(1), GL_COMPILE);
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(1, 0);
		glVertex2f(1, 1);
		glVertex2f(0, 1);
		glEnd();
		glEndList();

		glNewList(_startButton = glGenLists(1), GL_COMPILE);
		glBegin(GL_QUADS);
		for (i = 0; i < 4; i++) glVertex2fv(_startBorder[i]);
		glEnd();
		glEndList();

		glNewList(_playSymbol = glGenLists(1), GL_COMPILE);
		glBegin(GL_TRIANGLES);
		glVertex2f(_startBorder[0][0] + 0.2*startLength, _startBorder[0][1] - 0.05*startHeight);
		glVertex2f(_startBorder[3][0] + 0.2*startLength, _startBorder[3][1] + 0.05*startHeight);
		glVertex2f(_startBorder[1][0] - 0.2*startLength, _startBorder[3][1] + 0.5*startHeight);
		glEnd();
		glEndList();

		glNewList(_pauseSymbol = glGenLists(1), GL_COMPILE);
		glBegin(GL_QUADS);
		glVertex2f(_startBorder[0][0] + startBorderLength * 0.3, _startBorder[0][1] - startBorderHeight * 0.1);
		glVertex2f(_startBorder[0][0] + startBorderLength * 0.45, _startBorder[0][1] - startBorderHeight * 0.1);
		glVertex2f(_startBorder[0][0] + startBorderLength * 0.45, _startBorder[2][1] + startBorderHeight * 0.1);
		glVertex2f(_startBorder[0][0] + startBorderLength * 0.3, _startBorder[2][1] + startBorderHeight * 0.1);

		glVertex2f(_startBorder[0][0] + startBorderLength * 0.6, _startBorder[0][1] - startBorderHeight * 0.1);
		glVertex2f(_startBorder[0][0] + startBorderLength * 0.75, _startBorder[0][1] - startBorderHeight * 0.1);
		glVertex2f(_startBorder[0][0] + startBorderLength * 0.75, _startBorder[2][1] + startBorderHeight * 0.1);
		glVertex2f(_startBorder[0][0] + startBorderLength * 0.6, _startBorder[2][1] + startBorderHeight * 0.1);
		glEnd();
		glEndList();
	}


public:

	static void HandOver()
	{
		_paused = TRUE;
		Initialize();
		glutDisplayFunc(Display);
		glutMouseFunc(MouseSetup);
	}


	static void Display()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		DrawFilledCells();

		DrawGrid();

		DrawStartButton();

		glFlush();
	}


	static void MouseSetup(int button, int state, int x, int y)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			int i, j;
			double xWorld = x, yWorld = y;

			WindowToWorldCoordinates(xWorld, yWorld);

			if (CM(xWorld, yWorld) == UNPOPULATED)
			{
				CM.invert(xWorld, yWorld);
				glutMotionFunc(MouseMotionPopulateCells);
				glutPostRedisplay();
			}
			else if (CM(xWorld, yWorld) == POPULATED)
			{
				CM.invert(xWorld, yWorld);
				glutMotionFunc(MouseMotionUnpopulateCells);
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


	static void MouseMotionPopulateCells(int x, int y)
	{
		double xWorld = x, yWorld = y;
		WindowToWorldCoordinates(xWorld, yWorld);
		if (CM(xWorld, yWorld) == UNPOPULATED)
		{
			CM.Update(xWorld, yWorld, POPULATED);
			glutPostRedisplay();
		}
	}


	static void MouseMotionUnpopulateCells(int x, int y)
	{
		double xWorld = x, yWorld = y;
		WindowToWorldCoordinates(xWorld, yWorld);
		if (CM(xWorld, yWorld) == POPULATED)
		{
			CM.Update(xWorld, yWorld, UNPOPULATED);
			glutPostRedisplay();
		}
	}


	static void ButtonPressCheck(double x, double y)
	{
		if (StartButtonPressed(x, y))
		{
			_paused = FALSE;
			glutIdleFunc(Run);
			glutMouseFunc(MouseRunning);
		}
	}


	static int StartButtonPressed(double x, double y)
	{
		if (x >= _startBorder[0][0] && x <= _startBorder[1][0] && y >= _startBorder[2][1] && y <= _startBorder[1][1])
			return TRUE;
		else
			return FALSE;
	}


	static void Run()
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


	static void MouseRunning(int button, int state, int x, int y)
	{
		if (button == GLUT_LEFT && state == GLUT_DOWN)
		{
			double xWorld = x, yWorld = y;
			WindowToWorldCoordinates(xWorld, yWorld);
			if (StartButtonPressed(xWorld, yWorld))
			{
				_paused = TRUE;
				glutIdleFunc(NULL);
				glutMouseFunc(MouseSetup);
			}
		}
	}


	static void DrawGrid()
	{
		glColor3f(0.8, 0.8, 0.8);
		for (int i = 0; i < GRID_MAX; i++)
		{
			glTranslatef(i, 0, 0);
			glCallList(_gridLineV);
			glTranslatef(-i, i, 0);
			glCallList(_gridLineH);
			glTranslatef(0, -i, 0);
		}
	}


	static void DrawFilledCells()
	{
		int i, j;
		glColor3f(1, 1, 0);
		for (i = 0; i < GRID_MAX; i++)
			for (j = 0; j < GRID_MAX; j++)
				if (CM(i, j) == POPULATED)
				{
					glPushMatrix();
					glTranslatef(i, j, 0);
					glCallList(_cell);
					glPopMatrix();
				}
	}


	static void DrawStartButton()
	{
		glColor3f(0, 0, 0);
		glCallList(_startButton);

		glPushMatrix();
		glTranslatef(_startOffsetX, _startOffsetY, 0);
		glScalef(0.9, 0.9, 0);
		glColor3f(0.5, 0.5, 0.5);
		glCallList(_startButton);
		glColor3f(0, 0, 0);
		if (_paused)
			glCallList(_playSymbol);
		else
			glCallList(_pauseSymbol);
		glPopMatrix();

	}

}ViewAutomaton;
float ViewAutomaton::_barX0, ViewAutomaton::_barY0, ViewAutomaton::_barX1, ViewAutomaton::_barY1, ViewAutomaton::_barWidth, ViewAutomaton::_barHeight, ViewAutomaton::_startBorder[4][2], ViewAutomaton::_startOffsetX, ViewAutomaton::_startOffsetY;
int ViewAutomaton::_paused, ViewAutomaton::_gridLineV, ViewAutomaton::_gridLineH, ViewAutomaton::_cell, ViewAutomaton::_startButton, ViewAutomaton::_playSymbol, ViewAutomaton::_pauseSymbol;


int main(int argc, char** argv)

{
	srand(time(NULL));
	cout << "Enter Sqaure Grid Size: ";
	cin >> GRID_MAX;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutCreateWindow("Cellular Automaton 1.1");

	ViewAutomaton.HandOver();
	glutReshapeFunc(Reshape);

	glutMainLoop();

	return 0;
}


void Reshape(int w, int h)

{
	WindowWidth = w;
	WindowHeight = h;
	if (h * WidthHeightRatio <= w)

		glViewport((w / 2) - (h * WidthHeightRatio / 2), 0, h * WidthHeightRatio, h);
	else

		glViewport(0, (h / 2) - ((w / WidthHeightRatio) / 2), w, w / WidthHeightRatio);
	glutPostRedisplay();

}


void WindowToWorldCoordinates(double &x, double &y)

{
	int Padding = abs(WindowWidth - WindowHeight * WidthHeightRatio) / 2;
	if (WindowHeight * WidthHeightRatio <= WindowWidth)
	{
		x = (x - Padding) / (float)(WindowHeight * WidthHeightRatio) * VRwidth;
		y = GRID_MAX - y / (float)WindowHeight * VRheight;
	}
	else
	{
		x = x / (float)WindowWidth * VRwidth;
		y = GRID_MAX - (y - Padding) / (float)WindowWidth * VRheight;
	}
}