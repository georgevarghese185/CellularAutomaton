#include"Textures.h"

Textures::Textures(int numOfTextures)
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

int Textures::LoadTexture(string filePath, int width, int height, int texName)
{	/*	Most of this code including comments was taken from: https://en.wikibooks.org/wiki/OpenGL_Programming/Intermediate/Textures
		Special thanks to the various contributers of OpenGL Programming Tutorials on wikibooks.org
	*/

	if (texName >= _numOfTextures && texName<0)
	{
		cout << "LoadTexture: invalid texName" << endl;
		exit(1);
	}
	unsigned char *data;
	FILE *file;

	// open texture data
	file = fopen(filePath.c_str(), "rb");
	if (file == NULL)
	{
		cout << "LoadTexture: file==NULL" << endl;
		exit(1);
	}

	// allocate buffer
	data = new unsigned char[width * height * 4];//(unsigned char*)malloc(width * height * 4);

	// read texture data
	fread(data, width * height * 4, 1, file);
	fclose(file);

	// select our current texture
	glBindTexture(GL_TEXTURE_2D, _textures[texName]);

	// select modulate to mix texture with color for shading
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);*/

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	//// when texture area is small, bilinear filter the closest mipmap
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	//// when texture area is large, bilinear filter the first mipmap
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// texture should tile

	// build our texture mipmaps
	/*gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);*/

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	// free buffer
	delete[] data;//free(data);

	return TRUE;
}

GLuint Textures::GetDList(int name)
{
	return _dLists[name];
}

void Textures::DrawTexture(int texName)
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, _textures[texName]);
	glCallList(_dLists[texName]);

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void Textures::DrawTextures(int texNames[], int n)
{
	if (n <= 0 || n > _numOfTextures)
	{
		cout << "Textures::DrawTextures: invalid n value" << endl;
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

Textures::~Textures()
{
	glDeleteTextures(_numOfTextures, _textures);
	delete[] _textures;
	glDeleteLists(_dLists[0], _numOfTextures);
	delete[] _dLists;
}