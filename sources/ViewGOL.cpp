#include"ViewGOL.h"

namespace ViewGOL
{
	double VRwidth, VRheight;
	const double WHRatio = 800.0/600.0;
	GLuint listsBase, continueButtonPressed, continueButtonReleased, backButtonPressed, backButtonReleased, inputBox;
	GLsizei numOfLists;
	int showCursor, Draw::backButtonDown, Draw::continueButtonDown;
	string input;
	clock_t startTimer;
	Textures *tex;

#define BACK_BUTTON 0
#define CONT_BUTTON 1
#define TEX_GOL_RULES 0
#define TEX_GRID_SIZE 1
#define TEX_N_EQUALS 2
#define TEX_B_CONT 3
#define TEX_B_BACK 4

	void HandOver()
	{
		Initialize();
		glutDisplayFunc(Display);
		glutReshapeFunc(Reshape);
		glutMouseFunc(Mouse::Mouse);
		glutKeyboardFunc(Key);
		startTimer = clock();
		glutIdleFunc(CursorBlink);
		glutReshapeWindow(WindowWidth, WindowHeight);
	}

	void Reshape(int w, int h)
	{
		WindowWidth = w;
		WindowHeight = h;
		if (h * WHRatio <= w)

			glViewport((w / 2) - (GLsizei)(h * WHRatio / 2), 0, (GLsizei)(h * WHRatio), h);
		else

			glViewport(0, (h / 2) - ((GLsizei)(w / WHRatio) / 2), w, (GLsizei)(w / WHRatio));
		glutPostRedisplay();
	}

	void Initialize()
	{
		if (WindowWidth < 800 || WindowHeight < 600)
		{
			WindowWidth = 800; WindowHeight = 600;
			glutReshapeWindow(WindowWidth, WindowHeight);
		}
		VRwidth = 80; VRheight = 60;
		glViewport(0, 0, 800, 600);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, VRwidth, 0, VRheight);
		glViewport(0, 0, WindowWidth, WindowHeight);
		glMatrixMode(GL_MODELVIEW);
		glClearColor(0.1725f, 0.1725f, 0.1725f, 1.0f);

		showCursor = FALSE;
		Draw::backButtonDown = FALSE; Draw::continueButtonDown = FALSE;

		GLuint i = 0;
		numOfLists = 5;
		listsBase = glGenLists(numOfLists);

		glNewList(continueButtonReleased = listsBase + i++, GL_COMPILE);
		//button inner
		glColor3ub(70, 70, 70);
		glRectf(22, 32, 60, 39);
		//left border
		glColor3ub(55, 55, 55);
		glBegin(GL_QUADS);
		glVertex2f(21, 40);
		glVertex2f(22, 39);
		glVertex2f(22, 32);
		glVertex2f(21, 31);
		//right border
		glColor3ub(126, 126, 126);
		glVertex2f(60, 39);
		glVertex2f(61, 40);
		glVertex2f(61, 31);
		glVertex2f(60, 32);
		//bottom border
		glColor3ub(35, 35, 35);
		glVertex2f(22, 32);
		glVertex2f(60, 32);
		glVertex2f(61, 31);
		glVertex2f(21, 31);
		//top border
		glColor3ub(156, 156, 156);
		glVertex2f(21, 40);
		glVertex2f(61, 40);
		glVertex2f(60, 39);
		glVertex2f(22, 39);
		glEnd();
		glEndList();

		glNewList(continueButtonPressed = listsBase + i++, GL_COMPILE);
		//button inner
		glColor3ub(61, 61, 61);
		glRectf(22, 32, 60, 39);
		//left border
		glColor3ub(126, 126, 126);
		glBegin(GL_QUADS);
		glVertex2f(21, 40);
		glVertex2f(22, 39);
		glVertex2f(22, 32);
		glVertex2f(21, 31);
		//right border
		glColor3ub(55, 55, 55);
		glVertex2f(60, 39);
		glVertex2f(61, 40);
		glVertex2f(61, 31);
		glVertex2f(60, 32);
		//bottom border
		glColor3ub(156, 156, 156);
		glVertex2f(22, 32);
		glVertex2f(60, 32);
		glVertex2f(61, 31);
		glVertex2f(21, 31);
		//top border
		glColor3ub(35, 35, 35);
		glVertex2f(21, 40);
		glVertex2f(61, 40);
		glVertex2f(60, 39);
		glVertex2f(22, 39);
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

		glNewList(inputBox = listsBase + i++, GL_COMPILE);
		glColor3ub(255, 255, 255);
		glRectf(35,10,45,16);
		glColor3ub(0, 0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(35,10);
		glVertex2f(35,16);
		glVertex2f(45,16);
		glVertex2f(45,10);
		glEnd();
		glEndList();

		tex = new Textures(5);
		tex->LoadTexture(ExecDir + "textures/TEX_GOL_RULES", 812, 420, TEX_GOL_RULES);
		tex->MakeDList(TEX_GOL_RULES, 11, 28, 69, 58);

		tex->LoadTexture(ExecDir + "textures/TEX_GRID_SIZE", 360, 50, TEX_GRID_SIZE);
		tex->MakeDList(TEX_GRID_SIZE, 22, 18, 58, 23);

		tex->LoadTexture(ExecDir + "textures/TEX_N_EQUALS", 140, 100, TEX_N_EQUALS);
		tex->MakeDList(TEX_N_EQUALS, 26, 10, 33, 15);

		tex->LoadTexture(ExecDir + "textures/TEX_B_CONT", 684, 126, TEX_B_CONT);
		tex->MakeDList(TEX_B_CONT, 22, 32, 60, 39);

		tex->LoadTexture(ExecDir + "textures/TEX_B_BACK", 140, 80, TEX_B_BACK);
		tex->MakeDList(TEX_B_BACK, 0.5, 52.5, 7.5, 56.5);
	}

	void Display()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glCallList(inputBox);

		glPushMatrix();
		glLoadIdentity();
		glTranslatef(35.4f, 11.5f, 0.0f);
		glColor3ub(0, 0, 0);
		glScalef(0.03f,0.03f, 0.0f);
		if (!input.empty())
		{
			for (unsigned int i = 0; i < input.size();i++)
				glutStrokeCharacter(GLUT_STROKE_ROMAN, input[i]);
		}
		if(showCursor)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, '|');
		glPopMatrix();

		Draw::Text();
		Draw::Buttons();

		glutSwapBuffers();
	}

	void DummyDisplay() {}

	void CursorBlink()
	{
		if ((double)(clock() - startTimer) / (double)CLOCKS_PER_SEC >= 0.5)
		{
			startTimer = clock();
			showCursor = !showCursor;
			glutPostRedisplay();
		}
	}

	void Key(unsigned char key, int x, int y)
	{
		if (input.size() < 3 && isdigit(key))
		{
			input = input + (char)key;
		}
		else if (key == '\b' && !input.empty())
		{
			input.pop_back();
		}
		else if (key == 13)
		{
			if (input.empty() || atoi(input.c_str()) == 0) return;
			ViewAutomaton::cm.Initialize(atoi(input.c_str()));
			ViewAutomaton::cm.AddRule(POPULATED, LESS_THAN, 2, UNPOPULATED);
			ViewAutomaton::cm.AddRule(POPULATED, GREATER_THAN, 3, UNPOPULATED);
			ViewAutomaton::cm.AddRule(UNPOPULATED, EQUAL_TO, 3, POPULATED);
			exitGOL();
			glutIdleFunc(ViewAutomaton::HandOver);
		}
		glutPostRedisplay();

	}

	void exitGOL()
	{
		glDeleteLists(listsBase, numOfLists);
		delete tex;
		input.clear();
		glutDisplayFunc(DummyDisplay);
		glutMouseFunc(NULL);
		glutIdleFunc(NULL);
		glutKeyboardFunc(NULL);
	}

	void Mouse::Mouse(int button, int state, int x, int y)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			int pressedButton = ButtonPressCheck(x, WindowHeight - y);
			if (pressedButton == BACK_BUTTON)
			{
				Draw::backButtonDown = TRUE;
				glutPostRedisplay();
			}
			else if (pressedButton == CONT_BUTTON)
			{
				Draw::continueButtonDown = TRUE;
				glutPostRedisplay();
			}
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			if (Draw::backButtonDown)
			{
				Draw::backButtonDown = FALSE;
				glutPostRedisplay();
				exitGOL();
				glutIdleFunc(ViewMainMenu::HandOver);
			}
			else if (Draw::continueButtonDown)
			{
				Draw::continueButtonDown = FALSE;
				glutPostRedisplay();
				if (input.empty() || atoi(input.c_str()) == 0) return;
				ViewAutomaton::cm.Initialize(atoi(input.c_str()));
				ViewAutomaton::cm.AddRule(POPULATED, LESS_THAN, 2, UNPOPULATED);
				ViewAutomaton::cm.AddRule(POPULATED, GREATER_THAN, 3, UNPOPULATED);
				ViewAutomaton::cm.AddRule(UNPOPULATED, EQUAL_TO, 3, POPULATED);
				exitGOL();
				glutIdleFunc(ViewAutomaton::HandOver);
			}
		}
	}

	int Mouse::ButtonPressCheck(int x, int y)
	{
		GLubyte pixelColor[3], ContColor = 10, backColor = 20;
		glClear(GL_COLOR_BUFFER_BIT);

		glPushMatrix();
		glTranslatef(0, -31, 0);
		Draw::ScaleAbout(41.0f, 35.5f, 0.60f, 0.60f);
		glColor3ub(ContColor, 0, 0);
		glRectf(21, 31, 61, 40);
		glPopMatrix();

		glColor3ub(backColor, 0, 0);
		glRectf(0.5, 52, 8.5, 57);

		glFlush();
		glReadBuffer(GL_BACK);
		glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixelColor);

		if (pixelColor[0] == ContColor)
		{
			return CONT_BUTTON;
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

	void Draw::Text()
	{
		int tn[] = { TEX_GOL_RULES ,TEX_GRID_SIZE ,TEX_N_EQUALS };
		tex->DrawTextures(tn, 3);
	}

	inline void Draw::ScaleAbout(GLfloat x, GLfloat y, GLfloat xScale, GLfloat yScale)
	{
		glTranslatef(x, y, 0);
		glScalef(xScale, yScale, 0);
		glTranslatef(-x, -y, 0);
	}

	void Draw::Buttons()
	{
		glPushMatrix();
		glTranslatef(0, -31, 0);
		ScaleAbout(41.0f, 35.5f, 0.6f, 0.6f);
		if (Draw::continueButtonDown)
		{
			glPushMatrix();
			ScaleAbout(41.0f, 35.5f, 0.95f, 0.95f);
			glCallList(continueButtonPressed);
			tex->DrawTexture(TEX_B_CONT);
			glPopMatrix();
		}
		else
		{
			glCallList(continueButtonReleased);
			tex->DrawTexture(TEX_B_CONT);
		}
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.5, 0, 0);
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