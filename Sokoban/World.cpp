#include "World.h"
#include <string>
#include <fstream> 
#include <iostream>
#include <iomanip>

using namespace std;

World::World() {
	level = 1; // start with level one
	times = 0; //步數
	col = 0, row = 0;

	cout << "World Initial" << endl;
}


void World::drawmap() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			map[i][j]->print();
		}
		cout << endl;
	}
}

void World::update(){
}

void World::intro(){
	std::cout << "遊戲名稱：倉庫番\n\n"
		<< "遊戲介紹：\n《倉庫番》是一款以推箱子為主題的益智遊戲。在遊戲中，玩家將扮演一名倉庫工人，需要將箱子推動到指定的位置，達到指定數量即可過關。然而，推箱子並不是一件容易的事情，玩家需要考慮每一步的移動，避免陷入困境。\n\n"
		<< "遊戲規則：\n1. 玩家可以以「推」的方式移動箱子，向左、右、上、下四個方向移動。\n2. 玩家無法穿過牆壁，也無法將箱子拉動（只能推動箱子）。\n3. 箱子與玩家均無法穿過牆壁。\n4. 在測試關卡中，保證存在一條路徑可以將箱子推動到終點。\n5. 玩家可以任意移動，不一定要站在箱子旁邊。\n6. 即使箱子已經到達終點，仍可以被推動。\n7. 程式能夠自行判斷無解的情況，例如，箱子被推入死角無法再被推動，但死角並不是終點，則會告知玩家結束遊戲。\n\n"
		<< "遊戲操作：\n玩家可以使用鍵盤或滑鼠進行操作，根據指示移動工人與箱子，推動箱子到指定位置即可通過關卡。\n\n"
		<< "希望這份遊戲介紹與規則能幫助你更好地了解《倉庫番》的遊戲玩法！\n";
	system("pause");
	system("cls");
}

void World::start() {
	intro();
	drawUI();
	showstate("遊戲開始");

	play();

}

void World::play() {
	loadmap();
	drawmap();

}


void World::end(){
}
void World::restart(){
}

bool World::loadmap() {
	string index;
	index = to_string(level);

	string filename = "mission" + index + ".txt";

	ifstream file(filename, ios::in);

	if (!file) {
		cout << "Can't open the file : \"" + filename + "\"" << endl;

		return false;
	}
	else {

		file >> row >> col;
		charmap.resize(row, vector<char>(col));
		map.resize(row, vector<Block*>(col));

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				char ch;
				file >> ch;
				charmap[i][j] = ch;
				
				if (ch == Icon::player) {
					player.playerSetXYPos(row, col);
					map[i][j] = new Player(row, col);
				}
				else if (ch == Icon::box) {
					map[i][j] = new Box(row, col);
					// 做一些處理箱子的操作
				}
				else if (ch == Icon::target) {
					map[i][j] = new Target(row, col);
					// 做一些處理目標的操作
				}
				else if (ch == Icon::obstacle) {
					map[i][j] = new Obstacle(row, col);
					// 做一些處理牆壁的操作
				}
				else if (ch == Icon::none) {
					map[i][j] = new Block(row, col);
					// 做一些處理空地的操作
				}
				else {
					map[i][j] = nullptr;
					showstate("Null pointer");
					// 對於其他情況的預設處理
				}

			}
		}
		return true;

	}
}

void World::moveBlockTo(int row, int col, Block) {

}

void World::mapReset() {
    for (int i = 0; i < map.size(); i++) {
        map[i].clear();
    }
    map.clear();
}


void World::printOriginmap(){
	for(int i = 0 ; i < row ; i++){
		for(int j = 0 ; j < col ; j++){
			cout << charmap[i][j] ;
		}
		cout << endl;
	}
}
void World::nextLevel() {
	level++;
	system("cls");
	loadmap();
	play();

}


void World::playerUp() {
	// 檢查前面有沒有箱子 
	// 沒有箱子 -> 是不是牆壁 ->
	int x = player.x();
	int y = player.y();

	int above = x - 1;

	if (above < 0 || charmap[x - 1][y] == Icon::obstacle) { // (above < 0)超過map邊界 , (charmap[x - 1][y] == '/')遇到牆壁
		cout << "無法移動" << endl;
		return;
	}
	

	if ( charmap[x-1][y] == Icon::none) { // 空地 可以往上
		char temp = charmap[x][y];
		charmap[x][y] = charmap[x - 1][y];
		charmap[x - 1][y] = temp;
	}
	else if (charmap[x - 1][y] == Icon::box && charmap[x - 2][y] == Icon::none) { // 如果上方是箱子 再檢查 箱子上方有沒有空間 
		// x-2    x-1
		// x-1     x
		// x      x-2
		char temp = charmap[x][y];
		charmap[x][y] = charmap[x - 2][y];
		charmap[x - 2][y] = charmap[x - 1][y];
		charmap[x - 1][y] = temp;
	}
	else
	{
		cout << "未知情況" << endl;
	}
}
void World::playerDown() {

}
void World::playerLeft() {

}
void World::playerRight() {

}

 
void World::drawUI() {
	// gotoxy ui列
	cout << " ======================================================= " << endl
		<< "| 倉庫番                           行走步數: " << std::setw(5) << right << times << " 步" << "   |" << endl
		<< "|                                                       |" << endl
		<< "| W : 上 , S : 下 , A : 左 , D : 右                     |" << endl
		<< " ======================================================= " << endl
		;
}

void World::showstate(string state) {
	//goto 狀態位置
	cout << "目前狀態: "  << state << endl;
}


