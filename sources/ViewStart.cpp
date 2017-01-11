#include"ViewStart.h"

namespace ViewStart
{
	int startButton, startLeftBorder, startRightBorder, startTopBorder, startBottomBorder, startButtonDown;
	GLfloat startButtonV[8][2];
	
	void HandOver()
	{
		Initialize();
		glutDisplayFunc(Display);
		glutReshapeFunc(Reshape);
		glutMouseFunc(Mouse::Mouse);
		glutReshapeWindow(500, 500);

		glutShowWindow();
		glutIdleFunc(NULL);
	}
	
	void Initialize()
	{
		WindowWidth = WindowHeight = 500;
		WidthHeightRatio = (double)WindowWidth / (double)WindowHeight;
		VRwidth = 50;
		VRheight = 50;
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, VRwidth, 0, VRheight);
		glMatrixMode(GL_MODELVIEW);
		glutReshapeWindow(WindowWidth, WindowHeight);
		glClearColor(1, 0.73, 0.39, 1);

		startButton = glGenLists(5);
		startLeftBorder = startButton + 1; startRightBorder = startButton + 2;
		startTopBorder = startButton + 3; startBottomBorder = startButton + 4;

		startButtonDown = FALSE;
		startButtonV[0][0] = 12; startButtonV[0][1] = 22;
		startButtonV[1][0] = 38; startButtonV[1][1] = 22;
		startButtonV[2][0] = 38; startButtonV[2][1] = 10;
		startButtonV[3][0] = 12; startButtonV[3][1] = 10;
		startButtonV[4][0] = 13; startButtonV[4][1] = 21;
		startButtonV[5][0] = 37; startButtonV[5][1] = 21;
		startButtonV[6][0] = 37; startButtonV[6][1] = 11;
		startButtonV[7][0] = 13; startButtonV[7][1] = 11;

		glNewList(startButton, GL_COMPILE);
		glBegin(GL_QUADS);
		glVertex2fv(startButtonV[4]);
		glVertex2fv(startButtonV[5]);
		glVertex2fv(startButtonV[6]);
		glVertex2fv(startButtonV[7]);
		glEnd();
		glEndList();

		glNewList(startLeftBorder, GL_COMPILE);
		glBegin(GL_QUADS);
		glVertex2fv(startButtonV[0]);
		glVertex2fv(startButtonV[4]);
		glVertex2fv(startButtonV[7]);
		glVertex2fv(startButtonV[3]);
		glEnd();
		glEndList();

		glNewList(startRightBorder, GL_COMPILE);
		glBegin(GL_QUADS);
		glVertex2fv(startButtonV[5]);
		glVertex2fv(startButtonV[1]);
		glVertex2fv(startButtonV[2]);
		glVertex2fv(startButtonV[6]);
		glEnd();
		glEndList();

		glNewList(startTopBorder, GL_COMPILE);
		glBegin(GL_QUADS);
		glVertex2fv(startButtonV[0]);
		glVertex2fv(startButtonV[1]);
		glVertex2fv(startButtonV[5]);
		glVertex2fv(startButtonV[4]);
		glEnd();
		glEndList();

		glNewList(startBottomBorder, GL_COMPILE);
		glBegin(GL_QUADS);
		glVertex2fv(startButtonV[7]);
		glVertex2fv(startButtonV[6]);
		glVertex2fv(startButtonV[2]);
		glVertex2fv(startButtonV[3]);
		glEnd();
		glEndList();

	}

	void DrawGrid()
		//temporary
	{
		glColor3f(0, 0, 0);
		glBegin(GL_LINES);
		for (int i = 0; i < 50; i++)
		{
			glVertex2f(0, i);
			glVertex2f(50, i);
			glVertex2f(i, 0);
			glVertex2f(i, 50);
		}
		glEnd();
	}

	void Display()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		Draw::StartButton();

		//DrawGrid();

		glFlush();
	}

	void Mouse::Mouse(int button, int state, int x, int y)
	{
		if (button == GLUT_LEFT && state == GLUT_DOWN)
		{
			double xWorld = x, yWorld = y;
			WindowToWorldCoordinates(xWorld, yWorld);
			cout << xWorld << " " << yWorld << endl;
			if(StartButtonPressed(xWorld,yWorld))
				startButtonDown = TRUE;
			glutPostRedisplay();
		}
		else if (button == GLUT_LEFT && state == GLUT_UP && startButtonDown)
		{
			startButtonDown = FALSE;
			glDeleteLists(startButton, 5);
			glutMouseFunc(NULL);
			glutReshapeFunc(NULL);
			glutHideWindow();
			glutIdleFunc(ViewAutomaton::HandOver);
		}
	}

	int StartButtonPressed(double x, double y)
	{
		if (x >= startButtonV[0][0] && x <= startButtonV[1][0] && y >= startButtonV[2][1] && y <= startButtonV[1][1])	//check if x and y within start buttons boundaries.
			return TRUE;
		else
			return FALSE;
	}

	void Draw::StartButton()
	{
		if (startButtonDown)
		{
			glColor3f(0.145, 0.145, 0.145);
			glCallList(startButton);
			glColor3f(0.459, 0.459, 0.459);
			glCallList(startLeftBorder);
			glColor3f(0.553, 0.553, 0.553);
			glCallList(startBottomBorder);
			glColor3f(0.267, 0.267, 0.267);
			glCallList(startRightBorder);
			glColor3f(0.204, 0.204, 0.204);
			glCallList(startTopBorder);
		}
		else
		{
			glColor3f(0.196, 0.196, 0.196);
			glCallList(startButton);
			glColor3f(0.29, 0.29, 0.29);
			glCallList(startLeftBorder);
			glColor3f(0.25, 0.25, 0.25);
			glCallList(startBottomBorder);
			glColor3f(0.549, 0.549, 0.549);
			glCallList(startRightBorder);
			glColor3f(0.6118, 0.6118, 0.6118);
			glCallList(startTopBorder);
		}
	}
}