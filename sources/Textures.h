/*
		Most of the code for loading of .raw files as textures in Texures::LoadTexture() was taken
		from the OpenGL Texture Tutorial on wikibooks.org
		Link: https://en.wikibooks.org/wiki/OpenGL_Programming/Intermediate/Textures
*/
#pragma once
#include<iostream>
#include<GL\freeglut.h>
using namespace std;

class Textures
{
	GLuint *_textures, *_dLists;
	GLsizei _numOfTextures;
public:
	Textures(int numOfTextures);
	int LoadTexture(string filePath, int width, int height, int texName);
	GLuint GetDList(int name);
	void DrawTexture(int texName);
	void DrawTextures(int texNames[], int n);
	Textures::~Textures();
};
