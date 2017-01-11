/*
		Raw image texture loading code in Texures::LoadTexture() was taken
		from the OpenGL Texture Tutorial on wikibooks.org
		Link: https://en.wikibooks.org/wiki/OpenGL_Programming/Intermediate/Textures
*/
#ifndef __TEXTURES_H_INCLUDED
#define __TEXTURES_H_INCLUDED

#include<iostream>
#include<GL\freeglut.h>

using namespace std;
extern string ExecDir;		//current directory of .exe, for opening image files in /textures folder. Obtained from main.cpp

class Textures
{
	GLuint *_textures, *_dLists;						//_textures holds a number for each texture, _dLists holds the display list number corresponding to each texture.
	GLsizei _numOfTextures;								//needed for calling glDeleteTextures()
	
public:
	Textures(int numOfTextures);						//constructor. allocates "numOfTextures" elements in both arrays.
	void LoadTexture(string filePath, int width, int height, int texName);			//Load raw image file
	void MakeDList(int texName, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);	//Make a display list for the texture _textures[texName]
	void DrawTexture(int texName);						//calls display list for texture
	void DrawTextures(int *texNames, int n);			//for calling multiple textures. the texture numbers are passed through array.
	Textures::~Textures();								//Deletes display lists, textures and arrays.
};

#endif