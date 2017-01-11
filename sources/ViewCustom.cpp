#include"ViewCustom.h"

namespace ViewCustom
{
	double VRwidth, VRheight;
	const double WHRatio = 800.0/600.0;
	GLuint listsBase, continueButtonReleased, continueButtonPressed, backButtonReleased, backButtonPressed, inputBox;
	GLsizei numOfLists;
	int gotRules, showCursor, Draw::backButtonDown, Draw::continueButtonDown;
	vector<int> GetRules::populationState, GetRules::condition, GetRules::neighbour, GetRules::result;
	Textures *tex;
	string input;
	clock_t startTimer;

#define CONT_BUTTON 0
#define BACK_BUTTON 1
#define TEX_B_CONT 0
#define TEX_B_BACK 1
#define TEX_CUST 2
#define TEX_GRID_SIZE 3
#define TEX_N_EQUALS 4

	void HandOver()
	{
		Initialize();
		glutDisplayFunc(Display);
		glutReshapeFunc(Reshape);
		glutMouseFunc(Mouse::Mouse);
		glutPostRedisplay();
		glutReshapeWindow(WindowWidth, WindowHeight);
		glutIdleFunc(NULL);
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

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, VRwidth, 0, VRheight);
		glMatrixMode(GL_MODELVIEW);
		glClearColor(0.1725f, 0.1725f, 0.1725f, 1.0f);

		gotRules = FALSE; showCursor = FALSE; Draw::backButtonDown = FALSE; Draw::continueButtonDown = FALSE;

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
		//white inner of textbox
		glColor3ub(255, 255, 255);
		glRectf(35, 10, 45, 16);
		//box outline
		glColor3ub(0, 0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(35, 10);
		glVertex2f(35, 16);
		glVertex2f(45, 16);
		glVertex2f(45, 10);
		glEnd();
		glEndList();

		tex = new Textures(5);
		tex->LoadTexture(ExecDir + "textures/TEX_B_CONT", 684, 126, TEX_B_CONT);
		tex->MakeDList(TEX_B_CONT, 22, 32, 60, 39);

		tex->LoadTexture(ExecDir + "textures/TEX_B_BACK", 140, 80, TEX_B_BACK);
		tex->MakeDList(TEX_B_BACK, 0.5, 52.5, 7.5, 56.5);

		tex->LoadTexture(ExecDir + "textures/TEX_CUST", 810, 375, TEX_CUST);
		tex->MakeDList(TEX_CUST, 13, 21, 67, 45);

		tex->LoadTexture(ExecDir + "textures/TEX_GRID_SIZE", 360, 50, TEX_GRID_SIZE);
		tex->MakeDList(TEX_GRID_SIZE, 22, 18, 58, 23);

		tex->LoadTexture(ExecDir + "textures/TEX_N_EQUALS", 140, 100, TEX_N_EQUALS);
		tex->MakeDList(TEX_N_EQUALS, 26, 10, 33, 15);
	}

	void Display()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		Draw::Buttons();
		tex->DrawTexture(TEX_CUST);

		glutSwapBuffers();
	}

	void DisplayGetSize()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		Draw::Buttons();
		int tn[] = { TEX_GRID_SIZE,TEX_N_EQUALS };
		tex->DrawTextures(tn, 2);
		glCallList(inputBox);

		glPushMatrix();
		glLoadIdentity();
		glTranslatef(35.4f, 11.5f, 0.0f);
		glScalef(0.03f, 0.03f, 0.0f);
		glColor3ub(0, 0, 0);
		if (!input.empty())
		{
			for (unsigned int i = 0; i < input.size(); i++)
				glutStrokeCharacter(GLUT_STROKE_ROMAN, input[i]);
		}
		if (showCursor)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, '|');
		glPopMatrix();

		glutSwapBuffers();
	}

	void DummyDisplay(){}

	void Key(unsigned char key, int x, int y)	//For entering grid size
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
			exitCustom();
			glutIdleFunc(ViewAutomaton::HandOver);
		}
		glutPostRedisplay();
	}

	void CursorBlink()		//Blinking curson in textbox
	{
		if ((double)(clock() - startTimer) / (double)CLOCKS_PER_SEC >= 0.5)
		{
			startTimer = clock();
			showCursor = !showCursor;
			glutPostRedisplay();
		}
	}

	void exitCustom()
	{
		glutDisplayFunc(DummyDisplay);
		glDeleteLists(listsBase, numOfLists);
		delete tex;
		input.clear();
		GetRules::populationState.clear();
		GetRules::condition.clear();
		GetRules::neighbour.clear();
		GetRules::result.clear();
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
			if (pressedButton == CONT_BUTTON)
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
				exitCustom();
				ViewAutomaton::cm.ClearRules();
				glutIdleFunc(ViewMainMenu::HandOver);
			}
			else if (Draw::continueButtonDown)
			{
				Draw::continueButtonDown = FALSE;
				glutPostRedisplay();
				if(!gotRules)
					GetRules::Menu();
				else
				{
					ViewAutomaton::cm.Initialize(atoi(input.c_str()));
					exitCustom();
					glutIdleFunc(ViewAutomaton::HandOver);
				}
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

	void GetRules::Menu()
	{
		int input,loop=1;
		glutHideWindow();

		while (loop==1)
		{
			system("cls");
			cout << "1. Add New Rule" << endl
				<< "2. See entered rules" << endl
				<< "3. Clear all rules" << endl
				<< "4. Begin" << endl
				<<"5. Back to main menu"<<endl<<endl
				<< "> ";
			cin >> input;

			switch (input)
			{
			case 1:
				AddRule();
				break;
			case 2:
				if (populationState.size() < 1)
				{
					cout << "No rules entered!\n";
					system("pause");
				}
				else
					ViewRules();
				break;
			case 3:
				if (populationState.size() < 1)
				{
					cout << "No rules entered!\n";
					system("pause");
				}
				else
					ClearRules();
				break;
			case 4:
				if (populationState.size() < 1)
				{
					cout<<"No rules entered!\n";
					system("pause");
				}
				else
					loop = 0;
				break;
			case 5:
				system("cls");
				loop = -1;
				glutShowWindow();
				exitCustom();
				glutIdleFunc(ViewMainMenu::HandOver);
				break;
			default:
				system("cls");
				cout << "Incorrect choice\n";
				system("pause");
				break;
			}
		}
		if (loop == 0)Begin();
	}

	void GetRules::AddRule()
	{
		string input;
		int temp, eflag=0;
		while (1)
		{
			system("cls");
			cout << " Format:" << endl << "\n" << "before_state : condition : no_of_neighbours : result_state";
			cout << "\n[populated|unpopulated] : [less_than|equal|greater_than] : [0-8] : [populated|unpopulated]";
			cout << "\nExamples:\n\t" << "unpopulated:less_than:4:populated"
				<< "\nMeans-> All DEAD cells with LESS THAN 4 neighbours will become LIVE";
			cout << "\n\n\t" << "populated:greater_than|equal:2:unpopulated";
			cout << "\nMeans-> All LIVE cells with 2 or GREATER THAN 2 neighbours will become DEAD";
			cout << "\n\n";
			cout << "before_state: ";
			cin >> input;
			if (!_stricmp(input.c_str(), "unpopulated"))
				populationState.push_back(UNPOPULATED);
			else if (!_stricmp(input.c_str(), "populated"))
				populationState.push_back(POPULATED);
			else
			{
				cout << "incorrect value\n";
				system("pause");
				continue;
			}

			cout << "condition: ";
			cin >> input;
			temp = 0; eflag = 0;
			for (unsigned int i = 0; i < input.size(); i++)
			{
				unsigned int j = i;
				while (input[j] != '|' && j<input.size())j++;
				string sub = input.substr(i, j - i);
				i = j;
				if (!_stricmp(sub.c_str(), "less_than"))
					temp = temp | LESS_THAN;
				else if (!_stricmp(sub.c_str(), "equal"))
					temp = temp | EQUAL_TO;
				else if (!_stricmp(sub.c_str(), "greater_than"))
					temp = temp | GREATER_THAN;
				else
				{
					eflag = 1;
					break;
				}
			}
			if (eflag)
			{
				cout << "incorrect value\n";
				system("pause");
				populationState.pop_back();
				continue;
			}
			else
				condition.push_back(temp);

			cout << "no_of_neigbours: ";
			cin >> temp;
			if (temp >= 0 && temp <= 8)
				neighbour.push_back(temp);
			else
			{
				cout << "incorrect value (should be b/w inclusive of 0 and 8, inclusive)\n";
				system("pause");
				populationState.pop_back();
				condition.pop_back();
				continue;
			}

			cout << "result_state: ";
			cin >> input;
			if (!_stricmp(input.c_str(), "unpopulated"))
			{
				result.push_back(UNPOPULATED);
				break;
			}
			else if (!_stricmp(input.c_str(), "populated"))
			{
				result.push_back(POPULATED);
				break;
			}
			else
			{
				cout << "incorrect value\n";
				system("pause");
				populationState.pop_back();
				condition.pop_back();
				neighbour.pop_back();
			}
		}
	}

	void GetRules::ViewRules()
	{
		system("cls");
		for (unsigned int i = 0; i < populationState.size(); i++)
		{
			cout << i + 1 << ". ";
			cout << "All ";
			if (populationState[i] == POPULATED)
				cout << "LIVE ";
			else if (populationState[i] == UNPOPULATED)
				cout << "DEAD ";
			cout << "cells with ";
			
			if (condition[i] == EQUAL_TO)
				cout << neighbour[i] << " ";
			else
			{
				if (condition[i] & EQUAL_TO)
					cout << neighbour[i] << " or ";
				if ((condition[i] & LESS_THAN) && (condition[i] & GREATER_THAN))
					cout << "LESS THAN or GREATER THAN " << neighbour[i] << " ";
				else if (condition[i] & LESS_THAN)
					cout << "LESS THAN " << neighbour[i] << " ";
				else if (condition[i] & GREATER_THAN)
					cout << "GREATER THAN " << neighbour[i] << " ";
			}
			cout << "neighbours will become ";
			if (result[i] == POPULATED)
				cout << "LIVE ";
			else if (result[i] == UNPOPULATED)
				cout << "DEAD ";
			cout << "\n\n";
		}
		system("pause");
	}

	void GetRules::ClearRules()
	{
		system("cls");
		populationState.clear();
		condition.clear();
		neighbour.clear();
		result.clear();
		cout << "Rules Cleared\n";
		system("pause");
	}

	void GetRules::Begin()
	{
		system("cls");
		for (unsigned int i = 0; i < populationState.size(); i++)
		{
			ViewAutomaton::cm.AddRule(populationState[i], condition[i], neighbour[i], result[i]);
		}
		glutShowWindow();
		glutKeyboardFunc(Key);
		glutIdleFunc(CursorBlink);
		glutDisplayFunc(DisplayGetSize);
		gotRules = TRUE;
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