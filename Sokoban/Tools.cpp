#include "Tools.h"


COORD Tools::getCursorPosition(HANDLE hConsoleOutput) { //gotoxy ���U���
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &csbi)) {
        return csbi.dwCursorPosition;
    }
    else {
        COORD invalidCoord = { 0, 0 };
        return invalidCoord;
    }
}

void Tools::gotoXY(int xpos, int ypos) //��Ы��� xpos , ypos
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos; scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput, scrn);
}

void Tools::gotoX(int xpos) {  //��Ы��� �� xpos ��

    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos; scrn.Y = 0;
    SetConsoleCursorPosition(hOuput, scrn);
}
void Tools::gotoY(int ypos) {  //��Ы��� �� xpos �C

    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = 0; scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput, scrn);
}






COORD Tools::getpos() { //���o�ثe��m �H COORD �����^
    return getCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
    //SetColor(red);
}

void Tools::SetColor(int color) // �]�w�C�� int color
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void Tools::sleepMilsec(int milsec) { //�Ȱ� ...��
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
