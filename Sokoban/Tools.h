#pragma once
#include <windows.h>
#include <chrono>
#include <iostream>
#include <thread>
#include <conio.h>



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
	// 位置設定
	static COORD getCursorPosition(HANDLE hConsoleOutput);
	static void  gotoxy(int xpos, int ypos);
	static COORD getpos();

	// 顏色
	static void SetColor(int color = 7);

	//延遲
	static void sleepMilsec(int milsec);


};

