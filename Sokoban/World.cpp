#include "World.h"
#include <string>
#include <fstream> 
#include <iostream>

enum icon {
	player = '0',
	wall = '/',
	none = '-',
	box = '1',
	target = '2',
};



using namespace std;

World::World() {
	level = 1; // start with level one
	col, row = 0;

	cout << "World Initial" << endl;
}
void World::draw(){
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
	loadmap();


}


void World::end(){
}
void World::restart(){
}

bool World::loadmap(){


	string prefix = ""; // C:// 之類的

    string index;
    index = to_string(level);

    string filename = prefix + "mission" + index + ".txt";

	ifstream file(filename , ios::in);
	//std::ifstream file("mission1.txt");

	if(!file){
		cout << "Can't open the file : \"" + filename + "\"" << endl;
		return false;
		
	}
	else{
			 
		file >> row >> col ;
		//map.resize(row, vector<char>(col));
		charmap.resize(row, vector<char>(col));
		//map.resize(row, vector<Block>(col));
		map.resize(row, vector<Block*>(col));


		for(int i = 0 ; i< row ; i++){
			for (int j = 0; j < col; j++) {
				char ch;
				file >> ch;
				charmap[i][j] = ch; 



				switch (ch)
				{
				case '0':
					player.playerSetXYPos(row, col);
					break;

				case '1':
					break;
				case '2':
					break;
				case '/':
					break;
				case '-':
					break;
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
			//cout << map[i][j] ;
		}
		cout << endl;
	}
}


void World::nextLevel() {
	level++;
}



void World::playerUp() {
	// 檢查前面有沒有箱子 
	// 沒有箱子 -> 是不是牆壁 ->
	int x = player.x();
	int y = player.y();

	int above = x - 1;

	if (above < 0 || charmap[x - 1][y] == icon::wall) { // (above < 0)超過map邊界 , (charmap[x - 1][y] == '/')遇到牆壁
		cout << "無法移動" << endl;
		return;
	}
	

	if ( charmap[x-1][y] == icon::none) { // 空地 可以往上
		char temp = charmap[x][y];
		charmap[x][y] = charmap[x - 1][y];
		charmap[x - 1][y] = temp;
	}
	else if (charmap[x - 1][y] == icon::box && charmap[x - 2][y] == icon::none) { // 如果上方是箱子 再檢查 箱子上方有沒有空間 
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

 