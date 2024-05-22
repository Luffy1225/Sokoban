#include "World.h"
#include "Tools.h"
#include <string>
#include <fstream> 
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <fstream>
 
#define LEVEL_AMOUNT 3

using namespace std;

World::World() {
	level = 1; // start with level one
	steps = 0; //步數
	stepsSum = 0;

	running = true;

	col = 0, row = 0;

	UI_main_X = 0;
	UI_main_Y = 1;
	UI_state_X = 0;
	UI_state_Y = 8;
	UI_map_X = 0;
	UI_map_Y = 10;


}


void World::drawmap() {

	Tools::gotoY(UI_map_Y);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			map[i][j]->print();
		}
		cout << endl;
	}

	//printOriginmap();
}

void World::intro(){ // 遊戲介紹
	Tools::SetColor(Col_blue);
	cout << " ================================================================ " << endl
		<< "|     ____    ______   _  __  ______   _____     _     _   _     |" << endl
		<< "|    / ___|  /  __  \\ | |/ / /  __  \\ |  _  )   / \\   | \\ | |    |" << endl
		<< "|    \\____ \\ | |  | | | ' /  | |  | | | |_) |  / _ \\  |  \\| |    |" << endl
		<< "|     ___) | | |__| | | . \\  | |__| | | |_) ) / ___ \\ | |\\  |    |" << endl
		<< "|    |____/  \\______/ |_|\\_\\ \\______/ |____/ /_/   \\_\\|_| \\_|    |" << endl
		<< "|                                                                |" << endl
		<< " ================================================================ " << endl<<endl;
	Tools::SetColor(Col_RESET);


	std::cout << "遊戲名稱：倉庫番\n\n";
	Tools::SetColor(Col_yellow); cout << "遊戲介紹："; Tools::SetColor(Col_RESET); cout << "\n《倉庫番》是一款以推箱子為主題的益智遊戲。在遊戲中，玩家將扮演一名倉庫工人，需要將箱子推動到指定的位置，達到指定數量即可過關。然而，推箱子並不是一件容易的事情，玩家需要考慮每一步的移動，避免陷入困境。\n\n";
	Tools::SetColor(Col_yellow); cout << "遊戲規則："; Tools::SetColor(Col_RESET); cout << "\n1. 玩家可以以「推」的方式移動箱子，向左、右、上、下四個方向移動。\n2. 玩家無法穿過牆壁，也無法將箱子拉動（只能推動箱子）。\n3. 箱子與玩家均無法穿過牆壁。\n4. 在測試關卡中，保證存在一條路徑可以將箱子推動到終點。\n5. 玩家可以任意移動，不一定要站在箱子旁邊。\n6. 即使箱子已經到達終點，仍可以被推動。\n7. 程式能夠自行判斷無解的情況，例如，箱子被推入死角無法再被推動，但死角並不是終點，則會告知玩家結束遊戲。\n\n";
	Tools::SetColor(Col_yellow); cout << "遊戲操作："; Tools::SetColor(Col_RESET); cout << "\n玩家可以使用「 W 」「 A 」「 S 」「 D 」操作，根據指示移動工人與箱子，推動箱子到指定位置即可通過關卡。\n\n";
	cout << "希望這份遊戲介紹與規則能幫助你更好地了解《倉庫番》的遊戲玩法！\n";
	system("pause");
	system("cls");
}

void World::start() { // 遊戲開始位置

	Tools::hideCursor();

	intro();
	drawUI();
	showstate("遊戲開始");

	play();

}

void World::play() { //遊玩主程式

	loadmap();
	drawmap();
	drawUI();
		
	int ch;

	while (running) {   

		if (checkwin() == true) {
			
			nextLevel();

			if (running) {
				celebrate();
				system("cls");
				loadmap();
				drawUI();
				drawmap();
			}

		}

		if (_kbhit()) {  // 如果有按鍵按下
			ch = _getch();  // 使用_getch()函數獲取按下的鍵值
			switch (ch) {
			case 'w' :
				//std::cout << "向上"  << std::endl;
				playerUp();
				update();

				break;
			case 'a' :
				//std::cout << "向左" << std::endl;
				playerLeft();
				update();

				break;
			case 's':
				//std::cout << "向下" << std::endl;
				playerDown();
				update();

				break;
			case 'd' :
				//std::cout << "向右" << std::endl;
				playerRight();
				update();

				break;
			case 'r':
				//std::cout << "向右" << std::endl;
				restart();

				break;
			case 27:  // 當按下ESC時循環，ESC鍵的鍵值是27
				running = false;
				break;
			default:
				string txt = "無效的鍵值：" + to_string(ch);
				showstate(txt , Col_red);
				break;
			}

			Tools::sleepMilsec(50);
		}
	}

}


void World::end(){ // 最終過關
	system("cls");
	Tools::gotoX(0);

	Tools::SetColor(Col_yellow);

	cout << " ================================================================ " << endl
		<< "|     ____    ______   _  __  ______   _____     _     _   _     |" << endl
		<< "|    / ___|  /  __  \\ | |/ / /  __  \\ |  _  )   / \\   | \\ | |    |" << endl
		<< "|    \\____ \\ | |  | | | ' /  | |  | | | |_) |  / _ \\  |  \\| |    |" << endl
		<< "|     ___) | | |__| | | . \\  | |__| | | |_) ) / ___ \\ | |\\  |    |" << endl
		<< "|    |____/  \\______/ |_|\\_\\ \\______/ |____/ /_/   \\_\\|_| \\_|    |" << endl
		<< "|                                                                |" << endl
		<< "|                                                                |" << endl
		<< "|                                                                |" << endl
		<< "|                                                                |" << endl
		<< "|                          恭喜過關!!!!                          |" << endl
		<< "|                     總花費步數 : "<< setw(5) <<stepsSum << " 步                      |" << endl
		<< "|                                                                |" << endl
		<< "|                 資工一   411285052   曾柏碩                    |" << endl
		<< "|                                                                |" << endl
		<< "|                                                                |" << endl
		<< "|                                                                |" << endl
		<< " ================================================================ " << endl;

	Tools::SetColor(Col_RESET);
}
//恭喜過關!!!!

void World::celebrate() {  //每關過關
	string txt = "恭喜通過 第 " + to_string(level) + " 關";
	showstate(txt , Col_yellow);
	system("pause");
}


void World::restart(){  
	
	steps = 0;
	play();
}

bool World::loadmap() {
	mapReset();

	string index;
	index = to_string(level);

	//index = "2";/////////////////////////////

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
					player.playerSetXYPos(i, j);
					map[i][j] = new Player(i, j);
				}
				else if (ch == Icon::box) {
					map[i][j] = new Box(i, j);
					// 做一些處理箱子的操作
				}
				else if (ch == Icon::target) {
					map[i][j] = new Target(i, j);
					// 做一些處理目標的操作
				}
				else if (ch == Icon::obstacle) {
					map[i][j] = new Obstacle(i, j);
					// 做一些處理牆壁的操作
				}
				else if (ch == Icon::none) {
					map[i][j] = new Block(i, j);
					// 做一些處理空地的操作
				}
				else {
					map[i][j] = nullptr;
					showstate("Null pointer", Col_red);
					// 對於其他情況的預設處理
				}

			}
		}
		return true;

	}
	file.close();
}

void World::mapReset() {
    for (int i = 0; i < map.size(); i++) {
        map[i].clear();
		charmap[i].clear();
    }
    map.clear();
	charmap.clear();
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

	if (level == LEVEL_AMOUNT) {
		end();
		running = false;
	}
	else
	{
		level++;
		stepsSum += steps;
		steps = 0;
	}
}


void World::playerUp() {
	int x = player.x(); // 獲取玩家的 x 座標
	int y = player.y(); // 獲取玩家的 y 座標

	int above = x - 1; // 計算玩家上方的座標

	// 檢查玩家上方是否超出地圖邊界或是遇到障礙物
	if (above < 0 || charmap[above][y] == Icon::obstacle) {
		showstate("無法移動" , Col_red);
		return; // 結束函式
	}

	steps++;


	// 如果玩家上方是空地，可以移動玩家
	if (charmap[above][y] == Icon::none) {
		// 交換玩家和空地的位置
		char temp = charmap[x][y];
		charmap[x][y] = charmap[above][y];
		charmap[above][y] = temp;

		// 更新地圖上玩家的位置
		player.playerAddX(-1);

		// 交換地圖上的Block指標
		Block* tempBlock = map[x][y];
		map[x][y] = map[above][y];
		map[above][y] = tempBlock;


	}
	// 如果玩家上方是箱子，檢查是否有足夠的空間移動箱子
	else if (charmap[above][y] == Icon::box) {
		if (charmap[x - 2][y] == Icon::none) {
			char temp = charmap[x][y];
			charmap[x][y] = charmap[x - 2][y];
			charmap[x - 2][y] = charmap[above][y];
			charmap[above][y] = temp;

			player.playerAddX(-1);

			// 交換地圖上的Block指標
			Block* tempBlock = map[x][y];
			map[x][y] = map[x - 2][y];
			map[x - 2][y] = map[above][y];
			map[above][y] = tempBlock;
		}
		else if (charmap[x - 2][y] == Icon::target) { // 碰到終點特例
			char temp = charmap[x][y];

			charmap[x - 2][y] = charmap[above][y];
			charmap[above][y] = temp;
			charmap[x][y] = '-';

			player.playerAddX(-1);

			// 交換地圖上的Block指標
			Block* tempBlock = map[x][y];
			map[x - 2][y] = map[above][y];
			map[above][y] = map[x][y];
			map[x][y] = new Block(x, y);
		}
	}
	else {
		cout << "未知情況" << endl; // 輸出未知情況的訊息
	}


}
void World::playerDown() {
	int x = player.x(); // 獲取玩家的 x 座標
	int y = player.y(); // 獲取玩家的 y 座標

	int below = x + 1; // 計算玩家下方的座標

	// 檢查玩家下方是否超出地圖邊界或是遇到障礙物
	if (below >= charmap.size() || charmap[below][y] == Icon::obstacle) {
		showstate("無法移動", Col_red);
		return; // 結束函式
	}

	steps++;


	// 如果玩家下方是空地，可以移動玩家
	if (charmap[below][y] == Icon::none) {
		// 交換玩家和空地的位置
		char temp = charmap[x][y];
		charmap[x][y] = charmap[below][y];
		charmap[below][y] = temp;

		// 更新地圖上玩家的位置
		player.playerAddX(1);

		// 交換地圖上的Block指標
		Block* tempBlock = map[x][y];
		map[x][y] = map[below][y];
		map[below][y] = tempBlock;


	}
	// 如果玩家下方是箱子，檢查是否有足夠的空間移動箱子
	else if (charmap[below][y] == Icon::box) {
		if (charmap[x + 2][y] == Icon::none) {
			char temp = charmap[x][y];
			charmap[x][y] = charmap[x + 2][y];
			charmap[x + 2][y] = charmap[below][y];
			charmap[below][y] = temp;

			player.playerAddX(1);

			// 交換地圖上的Block指標
			Block* tempBlock = map[x][y];
			map[x][y] = map[x + 2][y];
			map[x + 2][y] = map[below][y];
			map[below][y] = tempBlock;
		}
		else if (charmap[x + 2][y] == Icon::target) { // 碰到終點特例
			char temp = charmap[x][y];

			charmap[x + 2][y] = charmap[below][y];
			charmap[below][y] = temp;
			charmap[x][y] = '-';

			player.playerAddX(1);

			// 交換地圖上的Block指標
			Block* tempBlock = map[x][y];
			map[x + 2][y] = map[below][y];
			map[below][y] = map[x][y];
			map[x][y] = new Block(x, y);
		}
	}
	else {
		cout << "未知情況" << endl; // 輸出未知情況的訊息
	}

}
void World::playerLeft() {
	int x = player.x(); // 獲取玩家的 x 座標
	int y = player.y(); // 獲取玩家的 y 座標

	int left = y - 1; // 計算玩家左方的座標

	// 檢查玩家左方是否超出地圖邊界或是遇到障礙物
	if (left < 0 || charmap[x][left] == Icon::obstacle) {
		showstate("無法移動", Col_red);
		return; // 結束函式
	}

	steps++;
	// 如果玩家左方是空地，可以移動玩家
	if (charmap[x][left] == Icon::none) {
		// 交換玩家和空地的位置
		char temp = charmap[x][y];
		charmap[x][y] = charmap[x][left];
		charmap[x][left] = temp;

		// 更新地圖上玩家的位置
		player.playerAddY(-1);

		// 交換地圖上的Block指標
		Block* tempBlock = map[x][y];
		map[x][y] = map[x][left];
		map[x][left] = tempBlock;


	}
	// 如果玩家左方是箱子，檢查是否有足夠的空間移動箱子
	else if (charmap[x][left] == Icon::box) {
		if (charmap[x][y - 2] == Icon::none) {
			char temp = charmap[x][y];
			charmap[x][y] = charmap[x][y - 2];
			charmap[x][y - 2] = charmap[x][left];
			charmap[x][left] = temp;

			player.playerAddY(-1);

			// 交換地圖上的Block指標
			Block* tempBlock = map[x][y];
			map[x][y] = map[x][y - 2];
			map[x][y - 2] = map[x][left];
			map[x][left] = tempBlock;
		}
		else if (charmap[x][y - 2] == Icon::target) { // 碰到終點特例
			char temp = charmap[x][y];

			charmap[x][y - 2] = charmap[x][left];
			charmap[x][left] = temp;
			charmap[x][y] = '-';

			player.playerAddY(-1);

			// 交換地圖上的Block指標
			Block* tempBlock = map[x][y];
			map[x][y - 2] = map[x][left];
			map[x][left] = map[x][y];
			map[x][y] = new Block(x, y);
		}
	}
}
void World::playerRight() {
	int x = player.x(); // 獲取玩家的 x 座標
	int y = player.y(); // 獲取玩家的 y 座標

	int right = y + 1; // 計算玩家右方的座標

	// 檢查玩家右方是否超出地圖邊界或是遇到障礙物
	if (right >= charmap[0].size() || charmap[x][right] == Icon::obstacle) {
		showstate("無法移動", Col_red);
		return; // 結束函式
	}

	steps++;

	// 如果玩家右方是空地，可以移動玩家
	if (charmap[x][right] == Icon::none) {
		// 交換玩家和空地的位置
		char temp = charmap[x][y];
		charmap[x][y] = charmap[x][right];
		charmap[x][right] = temp;

		// 更新地圖上玩家的位置
		player.playerAddY(1);

		// 交換地圖上的Block指標
		Block* tempBlock = map[x][y];
		map[x][y] = map[x][right];
		map[x][right] = tempBlock;

	}
	// 如果玩家右方是箱子，檢查是否有足夠的空間移動箱子
	else if (charmap[x][right] == Icon::box) {
		if (charmap[x][y + 2] == Icon::none) {
			char temp = charmap[x][y];
			charmap[x][y] = charmap[x][y + 2];
			charmap[x][y + 2] = charmap[x][right];
			charmap[x][right] = temp;

			player.playerAddY(1);

			// 交換地圖上的Block指標
			Block* tempBlock = map[x][y];
			map[x][y] = map[x][y + 2];
			map[x][y + 2] = map[x][right];
			map[x][right] = tempBlock;
		}
		else if (charmap[x][y + 2] == Icon::target) { // 碰到終點特例
			char temp = charmap[x][y];

			charmap[x][y + 2] = charmap[x][right];
			charmap[x][right] = temp;
			charmap[x][y] = '-';

			player.playerAddY(1);

			// 交換地圖上的Block指標
			Block* tempBlock = map[x][y];
			map[x][y + 2] = map[x][right];
			map[x][right] = map[x][y];
			map[x][y] = new Block(x, y);
		}
	}
	else {
		cout << "未知情況" << endl; // 輸出未知情況的訊息
	}



}

 
void World::mainfresh() {
	Tools::gotoY(UI_main_Y);
	cout << "| 倉庫番                           行走步數: " << std::setw(5) << right << steps << " 步" << "   |" << endl;

}


void World::drawUI() {
	// gotoxy ui列
	Tools::gotoX(0);

	cout << " ======================================================= " << endl
		<< "| 倉庫番                           行走步數: " << std::setw(5) << right << steps << " 步" << "   |" << endl
		<< "|                                                       |" << endl
		//<< "| 玩家 : 0 , 箱子 : 1 , 終點: 2 , 牆壁 : /              |" << endl
		<< "| ";
	Tools::SetColor(Col_blue); cout << "玩家 : 0"; Tools::SetColor(Col_RESET); cout << " , ";
	Tools::SetColor(Col_shit); cout << "箱子 : 1"; Tools::SetColor(Col_RESET); cout << " , ";
	Tools::SetColor(Col_red); cout << "終點 : 2"; Tools::SetColor(Col_RESET); cout << " , ";
	Tools::SetColor(Col_gray); cout << "牆壁 : /"; Tools::SetColor(Col_RESET); cout << "             |" << endl;
		//"| 玩家 : 0 , 箱子 : 1 , 終點: 2 , 牆壁 : /              |"

	cout << "|                                                       |" << endl
		<< "| R : 重新該關卡                                        |" << endl
		<< "| W : 上 , S : 下 , A : 左 , D : 右                     |" << endl
		<< " ======================================================= " << endl
		;
}

void World::update() {
	mainfresh();
	showstate("                                                             ");
	drawmap();

}

void World::showstate(string state , Color color ) {

	//goto 狀態位置 清空
	Tools::gotoY(UI_state_Y);
	cout << "                                                        ";


	Tools::gotoY(UI_state_Y);
	Tools::SetColor(color);
	cout << "目前狀態: "  << state << endl;
	Tools::SetColor(Col_RESET);
}

bool World::checkwin() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (charmap[i][j] == '2') {
				return false;
				break;
			}
		}
	}
	return true;
}


void World::createMap() {
	//ofstream file();
}