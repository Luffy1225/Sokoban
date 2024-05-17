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