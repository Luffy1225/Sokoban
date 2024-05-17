#include "Box.h"
#include "Tools.h"



Box::Box(int x, int y) {
	pos_x = x;
	pos_y = y;
}

void Box::print() {
	Tools::SetColor(Col_shit);
	cout << Icon::box;
	Tools::SetColor(Col_RESET);
}