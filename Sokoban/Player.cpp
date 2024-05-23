#include "Player.h"
#include "Tools.h"


Player::Player() {

}

Player::Player(int x, int y) {
	//playerSetXYPos( x,  y);
	SetXYPos(x, y);
}


//void Player::playerSetXYPos(int x, int y) {
//	pos_x = x;
//	pos_y = y;
//}
//void Player::playerSet_Xpos(int x) {
//	pos_x = x;
//
//}
//void Player::playerSet_Ypos(int y) {
//	pos_y = y;
//
//}

//int Player::x() {
//	return pos_x;
//}
//int Player::y() {
//	return pos_y;
//}
//void Player::playerAddX(int Xvalue) {
//	pos_x += Xvalue;
//}
//void Player::playerAddY(int Yvalue) {
//	pos_y += Yvalue;
//}

void Player::print() {
	Tools::SetColor(Col_blue);
	cout << Icon::player;
	Tools::SetColor(Col_RESET);

}
