#include "Player.h"


Player::Player() {
}

void Player::playerSetXYPos(int x, int y) {
	pos_x = x;
	pos_y = y;
}
void Player::playerSet_Xpos(int x) {
	pos_x = x;

}
void Player::playerSet_Ypos(int y) {
	pos_y = y;

}

int Player::x() {
	return pos_x;
}
int Player::y() {
	return pos_y;
}