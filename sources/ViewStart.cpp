#include"ViewStart.h"

namespace ViewStart
{
	int startButton, startLeftBorder, startRightBorder, startTopBorder, startBottomBorder;
	int Draw::startButtonDown = FALSE;
	GLfloat startButtonV[8][2];
	Textures *tex;
	
	void HandOver()
	{
		Initialize();
		glutDisplayFunc(Display);
		glutReshapeFunc(Reshape);
		glutMouseFunc(Mouse::Mouse);
		glutReshapeWindow(WindowWidth, WindowHeight);
		glutPositionWindow(10, 10);

		glutShowWindow();
		glutIdleFunc(NULL);
	}

	void Initialize()
	{
		WindowWidth = WindowHeight = 650;
		WHRatio = (double)WindowWidth / (double)WindowHeight;
		VRwidth = 50;
		VRheight = 50;
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, VRwidth, 0, VRheight);
		glViewport(0, 0, WindowWidth, WindowHeight);
		glMatrixMode(GL_MODELVIEW);
		//glClearColor(0.3490, 0.3490, 0.3490, 0.3490);
		glClearColor(0.1725, 0.1725, 0.1725, 1);

		startButton = glGenLists(5);
		startLeftBorder = startButton + 1; startRightBorder = startButton + 2;
		startTopBorder = startButton + 3; startBottomBorder = startButton + 4;

		Draw::startButtonDown = FALSE;
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

		#define TEX_START 0
		#define TEX_CA_TITLE 1
		#define TEX_BY 2

		tex = new Textures(3);
		
		tex->LoadTexture(ExecDir + "textures/TEX_START.raw", 480, 200, TEX_START);
		glNewList(tex->GetDList(TEX_START),GL_COMPILE);
		glBegin(GL_QUADS);
		glTexCoord2d(1, 1); glVertex2fv(startButtonV[6]);
		glTexCoord2d(1, 0); glVertex2fv(startButtonV[5]);
		glTexCoord2d(0, 0); glVertex2fv(startButtonV[4]);
		glTexCoord2d(0, 1); glVertex2fv(startButtonV[7]);
		glEnd();
		glEndList();

		tex->LoadTexture(ExecDir + "textures/TEX_CA_TITLE.raw", 420, 140, TEX_CA_TITLE);
		glNewList(tex->GetDList(TEX_CA_TITLE), GL_COMPILE);
		glBegin(GL_QUADS);
		glTexCoord2d(1, 1); glVertex2f(46,33);
		glTexCoord2d(1, 0); glVertex2f(46,47);
		glTexCoord2d(0, 0); glVertex2f(4,47);
		glTexCoord2d(0, 1); glVertex2f(4,33);
		glEnd();
		glEndList();

		tex->LoadTexture(ExecDir + "textures/TEX_BY.raw", 364, 84, TEX_BY);
		glNewList(tex->GetDList(TEX_BY), GL_COMPILE);
		glBegin(GL_QUADS);
		glTexCoord2d(1, 1); glVertex2f(50, 2);
		glTexCoord2d(1, 0); glVertex2f(50, 8);
		glTexCoord2d(0, 0); glVertex2f(24, 8);
		glTexCoord2d(0, 1); glVertex2f(24, 2);
		glEnd();
		glEndList();
	}

	void Reshape(int w, int h)
	{
		::Reshape(w, h);
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
		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		glClear(GL_COLOR_BUFFER_BIT);

		Draw::StartButton();
		
		int tn[] = { TEX_CA_TITLE, TEX_BY };
		tex->DrawTextures(tn, 2);

		//DrawGrid();

		glFlush();
		glutSwapBuffers();
	}

	void Mouse::Mouse(int button, int state, int x, int y)
	{
		if (button == GLUT_LEFT && state == GLUT_DOWN)
		{
			double xWorld = x, yWorld = y;
			WindowToWorldCoordinates(xWorld, yWorld);
			cout << xWorld << " " << yWorld << endl;
			if(StartButtonPressed(xWorld,yWorld))
				Draw::startButtonDown = TRUE;
			glutPostRedisplay();
		}
		else if (button == GLUT_LEFT && state == GLUT_UP && Draw::startButtonDown)
		{
			Draw::startButtonDown = FALSE;
			glutPostRedisplay();
			exitStart();
		}
	}

	int StartButtonPressed(double x, double y)
	{
		if (x >= startButtonV[0][0] && x <= startButtonV[1][0] && y >= startButtonV[2][1] && y <= startButtonV[1][1])	//check if x and y within start buttons boundaries.
			return TRUE;
		else
			return FALSE;
	}

	void exitStart()
	{
		glDeleteLists(startButton, 5);
		delete tex;
		glutMouseFunc(NULL);
		glutReshapeFunc(NULL);
		glutHideWindow();
		glutIdleFunc(ViewAutomaton::HandOver);
	}

	void Draw::StartButton()
	{
		if (Draw::startButtonDown)
		{
			glPushMatrix();
			glTranslatef(25, 16, 0);
			glScalef(0.95, 0.95, 0);
			glTranslatef(-25, -16, 0);

			glColor3ub(61, 61, 61);
			glCallList(startButton);
			tex->DrawTexture(TEX_START);
			glColor3ub(126, 126, 126);
			glCallList(startLeftBorder);
			glColor3ub(156, 156, 156);
			glCallList(startBottomBorder);
			glColor3ub(55, 55, 55);
			glCallList(startRightBorder);
			glColor3ub(35, 35, 35);
			glCallList(startTopBorder);

			glPopMatrix();
		}
		else
		{
			glColor3ub(70, 70, 70);
			glCallList(startButton);
			tex->DrawTexture(TEX_START);
			glColor3ub(55, 55, 55);
			glCallList(startLeftBorder);
			glColor3ub(35, 35, 35);
			glCallList(startBottomBorder);
			glColor3ub(126, 126, 126);
			glCallList(startRightBorder);
			glColor3ub(156, 156, 156);
			glCallList(startTopBorder);
		}
	}
}