#include"Textures.h"

Textures::Textures(int numOfTextures)		//constructor. allocates "numOfTextures" elements in both arrays.
{
	if (numOfTextures <= 0)
	{
		cout << "numOfTextures <=0 not allowed" << endl;
		exit(1);
	}
	_numOfTextures = numOfTextures;
	_textures = new GLuint[numOfTextures];
	glGenTextures(numOfTextures, _textures);
	_dLists = new GLuint[numOfTextures];
	_dLists[0] = glGenLists(numOfTextures);
	for (int i = 1; i < numOfTextures; i++)
		_dLists[i] = _dLists[0] + i;
}

void Textures::LoadTexture(string filePath, int width, int height, int texName)		//Load raw image file
{	/*	Most of this code including comments were taken from: https://en.wikibooks.org/wiki/OpenGL_Programming/Intermediate/Textures
		Special thanks to the various contributers of OpenGL Programming Tutorials on wikibooks.org
	*/

	if (texName >= _numOfTextures && texName<0)		
	{
		cout << "invalid texture name" << endl;
		system("pause");
		exit(1);
	}
	unsigned char *data;
	FILE *file;

	// open texture data
	file = fopen(filePath.c_str(), "rb");
	if (file == NULL)
	{
		cout << "Error: Could not locate texture file \"" <<filePath.c_str() << "\"" << endl;
		cout << "\n\nMake sure the \"textures\" folder is present in the same directory as \"CA3.0.exe\"" << endl;
		system("pause");
		exit(1);
	}

	// allocate buffer
	data = new unsigned char[width * height * 4];

	// read texture data
	fread(data, width * height * 4, 1, file);
	fclose(file);

	// select our current texture
	glBindTexture(GL_TEXTURE_2D, _textures[texName]);

	// select modulate to mix texture with color for shading
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	// free buffer
	delete[] data;
}

void Textures::MakeDList(int texName, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)	//Make a display list for the texture _textures[texName]
{
	glNewList(_dLists[texName], GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2d(1, 1); glVertex2f(x2, y1);
	glTexCoord2d(1, 0); glVertex2f(x2, y2);
	glTexCoord2d(0, 0); glVertex2f(x1, y2);
	glTexCoord2d(0, 1); glVertex2f(x1, y1);
	glEnd();
	glEndList();
}

void Textures::DrawTexture(int texName)		//calls display list for texture
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, _textures[texName]);
	glCallList(_dLists[texName]);

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void Textures::DrawTextures(int *texNames, int n)	//for calling multiple textures. the texture numbers are passed through array.
{
	if (n <= 0 || n > _numOfTextures)
	{
		cout << "Textures::DrawTextures: invalid n value" << endl;
		system("pause");
		exit(1);
	}
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	for (int i = 0; i < n; i++)
	{
		glBindTexture(GL_TEXTURE_2D, _textures[texNames[i]]);
		glCallList(_dLists[texNames[i]]);
	}
	
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

Textures::~Textures()	//Deletes display lists, textures and arrays.
{
	glDeleteTextures(_numOfTextures, _textures);
	delete[] _textures;
	glDeleteLists(_dLists[0], _numOfTextures);
	delete[] _dLists;
}