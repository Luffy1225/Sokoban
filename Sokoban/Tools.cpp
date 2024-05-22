#include "Tools.h"


COORD Tools::getCursorPosition(HANDLE hConsoleOutput) { //gotoxy 輔助函數
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &csbi)) {
        return csbi.dwCursorPosition;
    }
    else {
        COORD invalidCoord = { 0, 0 };
        return invalidCoord;
    }
}

void Tools::gotoXY(int xpos, int ypos) //游標指往 xpos , ypos
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos; scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput, scrn);
}

void Tools::gotoX(int xpos) {  //游標指往 第 xpos 行

    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos; scrn.Y = 0;
    SetConsoleCursorPosition(hOuput, scrn);
}
void Tools::gotoY(int ypos) {  //游標指往 第 xpos 列

    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = 0; scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput, scrn);
}






COORD Tools::getpos() { //取得目前位置 以 COORD 物件返回
    return getCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
    //SetColor(red);
}

void Tools::SetColor(int color) // 設定顏色 int color
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void Tools::sleepMilsec(int milsec) { //暫停 ...秒
    std::this_thread::sleep_for(std::chrono::milliseconds(milsec));
}



void Tools::hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void Tools::showCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void Tools::clearX(int xpos) {
    gotoX(xpos);

}
