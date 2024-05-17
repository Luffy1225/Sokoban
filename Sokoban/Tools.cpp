#include "Tools.h"


COORD Tools::getCursorPosition(HANDLE hConsoleOutput) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &csbi)) {
        return csbi.dwCursorPosition;
    }
    else {
        COORD invalidCoord = { 0, 0 };
        return invalidCoord;
    }
}

void Tools::gotoxy(int xpos, int ypos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos; scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput, scrn);
}

COORD Tools::getpos() {
    return getCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
    //SetColor(red);
}

void Tools::SetColor(int color)
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void Tools::sleepMilsec(int milsec) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milsec));
}