#include"Buttons.h"

GLubyte * Color(GLubyte R, GLubyte  G, GLubyte B)
{
	GLubyte *color = new GLubyte[3];
	color[0] = R; color[1] = G; color[2] = B;
	return color;
}

Buttons::Buttons(int numOfButtons)
{
	_numOfButtons = numOfButtons;
	_buttonDown = new bool[numOfButtons];
	
	_buttonBorders = new GLfloat*[numOfButtons];
	for (int i = 0; i < numOfButtons; i++) _buttonBorders[i] = new GLfloat[4];
	
	_buttonCenter = new GLfloat*[numOfButtons];
	for (int i = 0; i < numOfButtons; i++)_buttonCenter[i] = new GLfloat[2];
	
	_button = new GLuint[numOfButtons];
	_buttonGraphic = new GLuint*[numOfButtons]();
}
void Buttons::MakeButton(int buttonName, GLfloat X0, GLfloat Y0, GLfloat X1, GLfloat Y1, GLuint graphicName)
{
	_buttonBorders[buttonName][0] = X0;
	_buttonBorders[buttonName][1] = Y0;
	_buttonBorders[buttonName][2] = X1;
	_buttonBorders[buttonName][3] = Y1;

	_buttonCenter[buttonName][0] = (X0 + X1) / 2;
	_buttonCenter[buttonName][1] = (Y0 + Y1) / 2;

	_button[buttonName] = graphicName;
	_buttonDown[buttonName] = false;
}

void Buttons::MakeButtonGraphic(int graphicName,
	GLfloat outerX0, GLfloat outerY0, GLfloat outerX1, GLfloat outerY1,
	GLfloat innerX0, GLfloat innerY0, GLfloat innerX1, GLfloat innerY1,
	GLubyte *innerPressed, GLubyte *topPressed, GLubyte *bottomPressed, GLubyte *leftPressed, GLubyte *rightPressed,
	GLubyte *innerReleased, GLubyte *topReleased, GLubyte *bottomReleased, GLubyte *leftReleased, GLubyte *rightReleased)
{
	_buttonGraphic[graphicName] = new GLuint[2];
	_buttonGraphic[graphicName][0] = glGenLists(2);
	_buttonGraphic[graphicName][1] = _buttonGraphic[graphicName][0] + 1;

	glNewList(_buttonGraphic[graphicName][0], GL_COMPILE);
	glColor3ubv(innerReleased);
	glRectf(innerX0, innerY0, innerX1, innerY1);
	glBegin(GL_QUADS);
	glColor3ubv(topReleased);
	glVertex2f(outerX0, outerY1);
	glVertex2f(outerX1, outerY1);
	glVertex2f(innerX1, innerY1);
	glVertex2f(innerX0, innerY1);
	glColor3ubv(rightReleased);
	glVertex2f(innerX1, innerY1);
	glVertex2f(outerX1, outerY1);
	glVertex2f(outerX1, outerY0);
	glVertex2f(innerX1, innerY0);
	glColor3ubv(bottomReleased);
	glVertex2f(innerX0, innerY0);
	glVertex2f(innerX1, innerY0);
	glVertex2f(outerX1, outerY0);
	glVertex2f(outerX0, outerY0);
	glColor3ubv(leftReleased);
	glVertex2f(outerX0, outerY1);
	glVertex2f(innerX0, innerY1);
	glVertex2f(innerX0, innerY0);
	glVertex2f(outerX0, outerY0);
	glEnd();
	glEndList();

	glNewList(_buttonGraphic[graphicName][1], GL_COMPILE);
	glColor3ubv(innerPressed);
	glRectf(innerX0, innerY0, innerX1, innerY1);
	glBegin(GL_QUADS);
	glColor3ubv(topPressed);
	glVertex2f(outerX0, outerY1);
	glVertex2f(outerX1, outerY1);
	glVertex2f(innerX1, innerY1);
	glVertex2f(innerX0, innerY1);
	glColor3ubv(rightPressed);
	glVertex2f(innerX1, innerY1);
	glVertex2f(outerX1, outerY1);
	glVertex2f(outerX1, outerY0);
	glVertex2f(innerX1, innerY0);
	glColor3ubv(bottomPressed);
	glVertex2f(innerX0, innerY0);
	glVertex2f(innerX1, innerY0);
	glVertex2f(outerX1, outerY0);
	glVertex2f(outerX0, outerY0);
	glColor3ubv(leftPressed);
	glVertex2f(outerX0, outerY1);
	glVertex2f(innerX0, innerY1);
	glVertex2f(innerX0, innerY0);
	glVertex2f(outerX0, outerY0);
	glEnd();
	glEndList();

	delete[] innerPressed; delete[] topPressed; delete[] bottomPressed; delete[] leftPressed; delete[] rightPressed;
	delete[] innerReleased; delete[] topReleased; delete[] bottomReleased; delete[] leftReleased; delete[] rightReleased;
}

int Buttons::PressButton(int x, int y)
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < _numOfButtons; i++)
	{
		glColor3ub(i, i, i);
		glRectf(_buttonBorders[i][0], _buttonBorders[i][1], _buttonBorders[i][2], _buttonBorders[i][3]);
	}
	glFlush();
	glReadBuffer(GL_BACK);
	GLubyte pixelColor[3];
	glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixelColor);

	for (int i = 0; i < _numOfButtons; i++)
	{
		if (pixelColor[0] == i)
		{
			_buttonDown[i] = (_buttonDown[i]) ? false : true;
			return i;
		}
	}
	return -1;
}

void Buttons::ReleaseButtons()
{
	for (int i = 0; i < _numOfButtons; i++)_buttonDown[i] = false;
}

void Buttons::DrawButton(int buttonName, int label, Textures *t)
{

	if (_buttonDown[buttonName])
	{
		glPushMatrix();
		glTranslated(_buttonCenter[buttonName][0], _buttonCenter[buttonName][1], 0);
		glScaled(0.95, 0.95, 0);
		glTranslated(-_buttonCenter[buttonName][0], -_buttonCenter[buttonName][1], 0);
		glPushMatrix(); glTranslatef(_buttonBorders[buttonName][0], _buttonBorders[buttonName][1],0);
		glCallList(_buttonGraphic[_button[buttonName]][1]); glPopMatrix();
		(!t) ? glCallList(label) : t->DrawTexture(label);
		glPopMatrix();
	}
	else
	{
		glPushMatrix(); glTranslatef(_buttonBorders[buttonName][0], _buttonBorders[buttonName][1], 0);
		glCallList(_buttonGraphic[_button[buttonName]][0]); glPopMatrix();
		(!t) ? glCallList(label) : t->DrawTexture(label);
	}
}

Buttons::~Buttons()
{
	delete[] _buttonDown;
	for (int i = 0; i < _numOfButtons; i++)
	{
		delete[] _buttonBorders[i];
		delete[] _buttonCenter[i];
		delete[] _buttonGraphic[i];
	}
	delete[] _buttonBorders; delete[] _buttonCenter;
	delete[] _buttonGraphic;
	delete[] _button;
}