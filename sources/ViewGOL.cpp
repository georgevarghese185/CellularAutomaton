#include"ViewGOL.h"

namespace ViewGOL
{
	double VRwidth, VRheight;
	const double WHRatio = 800.0/600.0;
	GLuint inputBox;
	int showCursor;
	string input;
	clock_t startTimer;
	Textures *tex;
	Buttons *buttons;

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
		glutMouseFunc(Mouse);
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

		glNewList(inputBox = glGenLists(1), GL_COMPILE);
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
		tex->MakeDList(TEX_N_EQUALS, 26, 11.5, 33, 16.5);

		tex->LoadTexture(ExecDir + "textures/TEX_B_CONT", 684, 126, TEX_B_CONT);
		tex->MakeDList(TEX_B_CONT, 22, 2, 60, 9);

		tex->LoadTexture(ExecDir + "textures/TEX_B_BACK", 140, 80, TEX_B_BACK);
		tex->MakeDList(TEX_B_BACK, 1, 52.5, 8, 56.5);

		buttons = new Buttons(2);
		buttons->MakeButtonGraphic(CONT_BUTTON, 0, 0, 40, 9, 1, 1, 39, 8,
			Color(61, 61, 61), Color(35, 35, 35), Color(126, 126, 126), Color(156, 156, 156), Color(55, 55, 55),
			Color(70, 70, 70), Color(156, 156, 156), Color(35, 35, 35), Color(55, 55, 55), Color(126, 126, 126));
		buttons->MakeButton(CONT_BUTTON, 21, 1, 61, 10, CONT_BUTTON);
		buttons->MakeButtonGraphic(BACK_BUTTON, 0, 0, 8, 5, 0.5, 0.5, 7.5, 4.5,
			Color(61, 61, 61), Color(35, 35, 35), Color(126, 126, 126), Color(55, 55, 55), Color(156, 156, 156),
			Color(70, 70, 70), Color(156, 156, 156), Color(35, 35, 35), Color(55, 55, 55), Color(126, 126, 126));
		buttons->MakeButton(BACK_BUTTON, 0.5, 52, 8.5, 57, BACK_BUTTON);
	}

	void Display()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glPushMatrix(); glTranslatef(0, 1.5, 0);
		glCallList(inputBox);
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

		int tn[] = { TEX_GOL_RULES ,TEX_GRID_SIZE ,TEX_N_EQUALS };
		tex->DrawTextures(tn, 3);
		buttons->DrawButton(CONT_BUTTON, TEX_B_CONT, tex);
		buttons->DrawButton(BACK_BUTTON, TEX_B_BACK, tex);

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
		glDeleteLists(inputBox,1);
		delete tex;
		delete buttons;
		input.clear();
		glutDisplayFunc(DummyDisplay);
		glutMouseFunc(NULL);
		glutIdleFunc(NULL);
		glutKeyboardFunc(NULL);
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
			if (pressedButton == BACK_BUTTON)
			{
				exitGOL();
				glutIdleFunc(ViewMainMenu::HandOver);
			}
			else if (pressedButton == CONT_BUTTON)
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
	}
}