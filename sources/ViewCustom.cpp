#include"ViewCustom.h"

namespace ViewCustom
{
	double VRwidth, VRheight;
	const double WHRatio = 800.0/600.0;
	GLuint listsBase, inputBox;
	GLsizei numOfLists;
	int gotRules, showCursor;
	vector<int> GetRules::populationState, GetRules::condition, GetRules::neighbour, GetRules::result;
	Textures *tex;
	Buttons *buttons;
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
		glutMouseFunc(Mouse);
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

		gotRules = 0;
		GLuint i = 0;
		numOfLists = 1;
		listsBase = glGenLists(numOfLists);
		
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
		tex->MakeDList(TEX_B_CONT, 22, 2, 60, 9);

		tex->LoadTexture(ExecDir + "textures/TEX_B_BACK", 140, 80, TEX_B_BACK);
		tex->MakeDList(TEX_B_BACK, 1, 52.5, 8, 56.5);

		tex->LoadTexture(ExecDir + "textures/TEX_CUST", 810, 375, TEX_CUST);
		tex->MakeDList(TEX_CUST, 13, 21, 67, 45);

		tex->LoadTexture(ExecDir + "textures/TEX_GRID_SIZE", 360, 50, TEX_GRID_SIZE);
		tex->MakeDList(TEX_GRID_SIZE, 22, 18, 58, 23);

		tex->LoadTexture(ExecDir + "textures/TEX_N_EQUALS", 140, 100, TEX_N_EQUALS);
		tex->MakeDList(TEX_N_EQUALS, 26, 10, 33, 15);

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

		buttons->DrawButton(CONT_BUTTON, TEX_B_CONT, tex);
		buttons->DrawButton(BACK_BUTTON, TEX_B_BACK, tex);
		tex->DrawTexture(TEX_CUST);

		glutSwapBuffers();
	}

	void DisplayGetSize()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		buttons->DrawButton(CONT_BUTTON, TEX_B_CONT, tex);
		buttons->DrawButton(BACK_BUTTON, TEX_B_BACK, tex);
		
		glPushMatrix(); glTranslatef(0, 1.5, 0);
		int tn[] = { TEX_GRID_SIZE,TEX_N_EQUALS };
		tex->DrawTextures(tn, 2);
		glCallList(inputBox);
		glLoadIdentity();
		glTranslatef(35.4f, 13.0f, 0.0f);
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
		delete buttons;
		input.clear();
		GetRules::populationState.clear();
		GetRules::condition.clear();
		GetRules::neighbour.clear();
		GetRules::result.clear();
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
				exitCustom();
				ViewAutomaton::cm.ClearRules();
				glutIdleFunc(ViewMainMenu::HandOver);
			}
			if (pressedButton == CONT_BUTTON)
			{
				if (!gotRules)
					GetRules::Menu();
				else if(!input.empty() && atoi(input.c_str())>0)
				{
					ViewAutomaton::cm.Initialize(atoi(input.c_str()));
					exitCustom();
					glutIdleFunc(ViewAutomaton::HandOver);
				}
			}
			glutPostRedisplay();
		}
	}

	void GetRules::Menu()
	{
		int input,loop=1;
		glutHideWindow();

		while (loop==1)
		{
			std::system("cls");
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
					std::system("pause");
				}
				else
					ViewRules();
				break;
			case 3:
				if (populationState.size() < 1)
				{
					cout << "No rules entered!\n";
					std::system("pause");
				}
				else
					ClearRules();
				break;
			case 4:
				if (populationState.size() < 1)
				{
					cout<<"No rules entered!\n";
					std::system("pause");
				}
				else
					loop = 0;
				break;
			case 5:
				std::system("cls");
				loop = -1;
				glutShowWindow();
				exitCustom();
				glutIdleFunc(ViewMainMenu::HandOver);
				break;
			default:
				std::system("cls");
				cout << "Incorrect choice\n";
				std::system("pause");
				break;
			}
		}
		if (loop == 0)Begin();
	}

	void GetRules::AddRule()
	{
		string input;
		int temp, eflag = 0;
		while (1)
		{
			std::system("cls");
			cout << " Format:" << endl << "\n" << "before_state: [live|dead]"
				<< "\ncondition: [less_than|equal|greater_than],"
				<< "\nno_of_neighbours: [0-8]"
				<< "\nresult_state: [live|dead]"
				<< "\n\nExamples:\n\t" << "(i) dead, less_than, 4, live"
				<< "\nMeans-> All DEAD cells with LESS THAN 4 neighbours will become LIVE"
				<< "\n\n\t" << "(ii) live, greater_than|equal, 2, dead"
				<< "\nMeans-> All LIVE cells with 2 or GREATER THAN 2 neighbours will become DEAD"
				<< "\n\nEnter Rule (type 'back' to go back)..."
				<< "\nbefore_state: ";
			if (result.size() < populationState.size()){
				cout << (populationState.back()? "live":"dead") << endl; 
				goto get_condition;
			}
			cin >> input;
			if (!_stricmp(input.c_str(), "back"))
				break;
			if (!_stricmp(input.c_str(), "dead"))
				populationState.push_back(UNPOPULATED);
			else if (!_stricmp(input.c_str(), "live"))
				populationState.push_back(POPULATED);
			else
			{
				cout << "incorrect value\n";
				std::system("pause");
				continue;
			}
			
		get_condition:
			cout << "condition: ";
			if (result.size() < condition.size()){
				input.clear();
				if (condition.back()&LESS_THAN)input = "less_than|";
				if (condition.back()&EQUAL_TO)input = input + "equal|";
				if (condition.back()&GREATER_THAN)input = input + "greater_than|";
				cout << input.substr(0,input.size()-1) << endl;; goto get_neighbour;
			}
			cin >> input;
			temp = 0; eflag = 0;
			if (!_stricmp(input.substr(0, 4).c_str(), "back"))
			{
				clearLast();
				break;
			}
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
				std::system("pause");
				continue;
			}
			else
				condition.push_back(temp);
			
		get_neighbour:
			cout << "no_of_neigbours: ";
			if (result.size() < neighbour.size()) {
				cout << neighbour.back() << endl; goto get_result;
			}

			cin >> input;
			if (!_stricmp(input.substr(0, 4).c_str(), "back"))
			{
				clearLast();
				break;
			}
			temp = atoi(input.c_str());
			eflag = 0;
			while (!input.empty()) {
				if (isdigit(input.back())) input.pop_back();
				else { eflag = 1; break; }
			}
			if (!eflag && temp >= 0 && temp <= 8)
				neighbour.push_back(temp);
			else
			{
				cout << "incorrect value (should be b/w 0 and 8, inclusive)\n";
				std::system("pause");
				continue;
			}

		get_result:
			cout << "result_state: ";

			cin >> input;
			if (!_stricmp(input.substr(0, 4).c_str(), "back"))
			{
				clearLast();
				break;
			}
			if (!_stricmp(input.c_str(), "dead"))
			{
				result.push_back(UNPOPULATED);
				break;
			}
			else if (!_stricmp(input.c_str(), "live"))
			{
				result.push_back(POPULATED);
				break;
			}
			else
			{
				cout << "incorrect value\n";
				std::system("pause");
			}
		}
	}

	void GetRules::ViewRules()
	{
		std::system("cls");
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
		std::system("pause");
	}

	void GetRules::ClearRules()
	{
		std::system("cls");
		populationState.clear();
		condition.clear();
		neighbour.clear();
		result.clear();
		cout << "Rules Cleared\n";
		std::system("pause");
	}

	void GetRules::clearLast()
	{
		if (populationState.size() > result.size()) populationState.pop_back();
		else return;
		if (condition.size() > result.size()) condition.pop_back();
		else return;
		if (neighbour.size() > result.size()) neighbour.pop_back();
	}

	void GetRules::Begin()
	{
		std::system("cls");
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
}