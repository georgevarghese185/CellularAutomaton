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

int GRID_MAX,CApaused=1;
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
		if (InBounds(x,y))
			return _cellMap[x][y];
		else
			return 0;		
	}

	void Set(int x, int y, int populationType)
	
	{
		_updateList.push_back(x);
		_updateList.push_back(y);
		_updateList.push_back(populationType);
	}

	void Update()
	{
		for (int i = 0; i < _updateList.size(); i+=3)
			_cellMap[_updateList[i]][_updateList[i + 1]] = _updateList[i + 2];
		_updateList.clear();
	}

	void Update(int x, int y, int populationState)
	{
			_cellMap[x][y] = populationState;
	}

	void invert(int x, int y)
	
	{
		_cellMap[x][y] = (_cellMap[x][y]==POPULATED) ? UNPOPULATED : POPULATED;
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
}cm;

class Rule
{
	int _populationState, _conditionType, _neighbourCount, _result;

public :
	Rule(int populationState, int conditionType, int neighbourCount, int result)
	
	{
		_populationState = populationState;
		_neighbourCount = neighbourCount;
		_conditionType = conditionType;
		_result = result;
	}
	
	void AppyRule(int x, int y)
	
	{
		if (cm(x,y) == _populationState)
		{
			int c=0;
			int count = cm(x - 1, y - 1) + cm(x - 1, y) + cm(x - 1, y + 1) 
				+ cm(x, y - 1) + cm(x, y + 1) + cm(x + 1, y - 1) + cm(x + 1, y) + cm(x + 1, y + 1);	
			
			if (count < _neighbourCount)
				c = c | LESS_THAN;
			if (count == _neighbourCount)
				c = c | EQUAL_TO;
			if (count > _neighbourCount)
				c = c | GREATER_THAN;

			if (c == _conditionType)
				cm.Set(x, y, _result);
		}
	}
};


void Initialize();
void DrawGrid();
void DisplayCellAutomataPaused();
void FillCells();
void DrawStartButton();
void MouseSetupClick(int,int,int,int);
void MousePopulateCells(int, int);
void MouseUnpopulateCells(int, int);
void AutomataButtonPress(double, double);
void StartAutomata();
void Reshape(int,int);
void WindowToCellCoordinates(double &x, double &y);


int main(int argc, char** argv)

{
	srand(time(NULL));
	cout << "Enter Sqaure Grid Size: ";
	cin >> GRID_MAX;
	VRwidth = (GRID_MAX + (WindowWidth-WindowHeight) / ((double)WindowHeight / (double)GRID_MAX));
	VRheight = GRID_MAX;
	cm.Initialize(GRID_MAX);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutCreateWindow("Cellular Automaton 1.0");
	
	Initialize();
	glutDisplayFunc(DisplayCellAutomataPaused);
	glutReshapeFunc(Reshape);
	glutMouseFunc(MouseSetupClick);
	
	glutMainLoop();

	return 0;
}


void Initialize()

{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, VRwidth, 0, VRheight);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1, 1, 1, 1);
}


void MouseSetupClick(int button, int state, int x, int y)

{
	int i, j;
	double xWorld=x, yWorld=y;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		WindowToCellCoordinates(xWorld, yWorld);
		if (cm.InBounds(xWorld, yWorld))
		{

			if (cm(xWorld, yWorld) == UNPOPULATED)
				glutMotionFunc(MousePopulateCells);
			else
				glutMotionFunc(MouseUnpopulateCells);
			cm.invert(xWorld, yWorld);
			glutPostRedisplay();
		}
		else
			AutomataButtonPress(xWorld, yWorld);
	}
}


void MousePopulateCells(int x, int y)
{
	double xWorld = x, yWorld = y;
	WindowToCellCoordinates(xWorld, yWorld);
	if (cm.InBounds(xWorld,yWorld) && cm(xWorld, yWorld) == UNPOPULATED)
	{
		cm.Update(xWorld, yWorld, POPULATED);
		glutPostRedisplay();
	}
}


void MouseUnpopulateCells(int x, int y)
{
	double xWorld = x, yWorld = y;
	WindowToCellCoordinates(xWorld, yWorld);
	if (cm.InBounds(xWorld,yWorld) && cm(xWorld, yWorld) == POPULATED)
	{
		cm.Update(xWorld, yWorld, UNPOPULATED);
		glutPostRedisplay();
	}
}

void MousePauseAutomata(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT && state == GLUT_DOWN)
	{
		double xWorld = x, yWorld = y;
		WindowToCellCoordinates(xWorld, yWorld);
		AutomataButtonPress(xWorld, yWorld);
	}
}


void AutomataButtonPress(double x, double y)
{
	if (CApaused == 0)
	{
		glutIdleFunc(NULL);
		glutMouseFunc(MouseSetupClick);
		CApaused = 1;
	}
	else if (x >= startButton[0] && x <= startButton[1] && y >= startButton[2] && y <= startButton[3])
	{
		CApaused = 0;
		glutMouseFunc(MousePauseAutomata);
		glutIdleFunc(StartAutomata);
	}
}


void Reshape(int w, int h)

{
	WindowWidth = w;
	WindowHeight = h;
	if (h * WidthHeightRatio <= w)
		
		glViewport((w / 2) - (h * WidthHeightRatio / 2), 0, h * WidthHeightRatio, h);
	else
		
		glViewport(0, (h / 2) - ((w / WidthHeightRatio) / 2), w, w/WidthHeightRatio);
	glutPostRedisplay();
	
}


void DisplayCellAutomataPaused()

{
	glClear(GL_COLOR_BUFFER_BIT);

	FillCells();

	DrawGrid();

	DrawStartButton();

	glFlush();
}

void StartAutomata()
{
	Rule gameOfLife1(POPULATED, LESS_THAN, 2, UNPOPULATED);
	Rule gameOfLife2(POPULATED, GREATER_THAN, 3, UNPOPULATED);
	Rule gameOfLife3(UNPOPULATED, EQUAL_TO, 3, POPULATED);
	int i, j;
	Sleep(100);
		cm.Update();
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


void DrawStartButton()
{
	int i;
	float barX0 = GRID_MAX, barX1 = VRwidth, barY0 = 0, barY1 = VRheight, 
		barWidth = barX1 - barX0, barHeight =  barY1 - barY0;
	
	float startBorder[][2] = { {barX0 + 0.05 * barWidth, barY0 + 0.9 * barHeight}, 
		{barX0 + 0.95 * barWidth, barY0 + 0.9 * barHeight}, {barX0 + 0.95 * barWidth,barY0 + 0.8 * barHeight},
		{barX0 + 0.05 * barWidth, barY0 + 0.8 * barHeight} };

	startButton[0] = startBorder[0][0];
	startButton[1] = startBorder[1][0];
	startButton[2] = startBorder[2][1];
	startButton[3] = startBorder[1][1];


	float startInner[][2] = { {barX0 + 0.1*barWidth,barY0 + 0.895*barHeight},
		{ barX0 + 0.895*barWidth,barY0 + 0.895*barHeight },{ barX0 + 0.895*barWidth,barY0 + 0.805*barHeight },
		{ barX0 + 0.1*barWidth,barY0 + 0.805*barHeight } };

	float playTriangle[][2] = { {} };
	
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	for (i = 0; i < 4; i++) glVertex2fv(startBorder[i]);
	glEnd();

	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_QUADS);
	for (i = 0; i < 4; i++) glVertex2fv(startInner[i]);
	glEnd();


}


void DrawGrid()

{
	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_LINES);
	for (int i = 0; i < GRID_MAX; i++)
	{
		glVertex2f(0, i);
		glVertex2f(GRID_MAX, i);
		glVertex2f(i, 0);
		glVertex2f(i, GRID_MAX);
	}
	glEnd();
}


void FillCells()

{
	int i, j;
	glColor3f(1, 1, 0);
	glBegin(GL_QUADS);
	for (i = 0; i < GRID_MAX; i++)
		for (j = 0; j < GRID_MAX;j++)
			if (cm(i,j)==POPULATED)
			{
				//cout << (rand() % 80 + 20) / 100.0 << endl;
				//glColor3f((rand() % 95 + 5) / 100.0, (rand() % 95 + 5) / 100.0, (rand() % 95 + 5) / 100.0);
				glVertex2f(i, j);
				glVertex2f(i + 1, j);
				glVertex2f(i + 1, j + 1);
				glVertex2f(i, j + 1);
			}
	glEnd();
}


void WindowToCellCoordinates(double &x, double &y)

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