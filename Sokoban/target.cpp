#include "target.h"
#include "Tools.h"



Target::Target(int x, int y) {
	pos_x = x;
	pos_y = y;
}

void Target::print() {
	Tools::SetColor(Col_red);
	cout << Icon::target;
	Tools::SetColor(Col_RESET);
}