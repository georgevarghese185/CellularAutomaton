/*
		Writes text onto the window using Win32 API
		Code written and provided by Suraj S., author of tech blog "Prominence"
				website: https://certigate.org
*/

#ifndef __TEXTMANIP_H_INCLUDED
#define __TEXTMANIP_H_INCLUDED

#include<Windows.h>

extern HFONT hf;
extern HWND OrigDC;

int setFont(LPWSTR fName, long size, BOOL italics, BOOL antiAlias);
int throwText(LPWSTR lpText, int x, int y, COLORREF Bakcolor, COLORREF ForeColor);

#endif