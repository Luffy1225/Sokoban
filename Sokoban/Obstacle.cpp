#include "Obstacle.h"
#include "Tools.h"

Obstacle::Obstacle(int x, int y) {
	pos_x = x;
	pos_y = y;
}

void Obstacle::print() {
	Tools::SetColor(Col_gray);
	cout << Icon::obstacle;
	Tools::SetColor(Col_RESET);
}