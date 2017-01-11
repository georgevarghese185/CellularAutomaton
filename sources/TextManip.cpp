/*
		Writes text onto the window using Win32 API
		Code written and provided by Suraj S., author of tech blog "Prominence"
				website: https://certigate.org
*/
#include"TextManip.h"

HFONT hf = NULL;
HWND OrigDC = NULL;

int setFont(LPWSTR fName, long size, BOOL italics, BOOL antiAlias)
{
	long lfHeight;
	HWND hwnd = GetActiveWindow();
	HDC hdc;
	if (OrigDC == NULL)
		OrigDC = hwnd;
	if (OrigDC == hwnd)
	{
		hdc = GetDC(hwnd);
		if (size == NULL)
			lfHeight = -MulDiv(12, GetDeviceCaps(hdc, LOGPIXELSY), 72);
		else
			lfHeight = size;
		if (antiAlias == TRUE)
			hf = CreateFont(lfHeight, 0, 0, 0, 0, italics, 0, 0, 0, 0, 0, ANTIALIASED_QUALITY, 0, fName);
		else
			hf = CreateFont(lfHeight, 0, 0, 0, 0, italics, 0, 0, 0, 0, 0, 0, 0, fName);
		ReleaseDC(hwnd, hdc);
	}
	return 0;
}

int throwText(LPWSTR lpText, int x, int y, COLORREF Bakcolor, COLORREF ForeColor)
{
	HWND hwnd;
	HDC hdc;
	hwnd = GetActiveWindow();
	if (OrigDC == NULL)
		OrigDC = hwnd;
	if (OrigDC == hwnd)
	{
		hdc = GetDC(hwnd);
		SetBkColor(hdc, Bakcolor);
		SetTextColor(hdc, ForeColor);
		SelectObject(hdc, hf);
		TextOut(hdc, x, y, lpText, lstrlen(lpText));
		ReleaseDC(hwnd, hdc);
	}
	return 0;
}