#pragma once
#include <windows.h>

enum Color {
	reset = 7,
	red = 12,
	blue = 9,
	gold = 14,
	white_black = 240,

};


class Tools
{
public:
	// ��m�]�w
	static COORD getCursorPosition(HANDLE hConsoleOutput);
	static void  gotoxy(int xpos, int ypos);
	static COORD getpos();

	// �C��
	static void SetColor(int color = 7);

};

