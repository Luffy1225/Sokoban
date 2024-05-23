#include "Block.h"

const char Icon::player = '0';
const char Icon::obstacle = '/';
const char Icon::none = '-';
const char Icon::box = '1';
const char Icon::target = '2';



Block::Block() {
	pos_x = -1;
	pos_y = -1;
}


Block::Block(int x , int y) {
	pos_x = x;
	pos_y = y;
}

void Block::print() {
	cout << Icon::none;
}

int Block::x() {
	return pos_x;
}
int Block::y() {
	return pos_y;
}


void Block::SetXYPos(int x, int y) {
	pos_x = x;
	pos_y = y;
}
void Block::Set_Xpos(int x) {
	pos_x = x;

}
void Block::Set_Ypos(int y) {
	pos_y = y;

}

void Block::AddX(int Xvalue) {
	pos_x += Xvalue;
}
void Block::AddY(int Yvalue) {
	pos_y += Yvalue;
}