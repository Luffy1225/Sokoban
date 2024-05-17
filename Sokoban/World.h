#pragma once
#include <vector>
#include "Block.h"
#include "Player.h"
#include "Box.h"
#include "Obstacle.h"
#include "Target.h"


using namespace std;

class World
{
private:
	//vector<vector<char> > map;
	vector<vector<char> > charmap;
	//vector<vector<Block> > map;
	vector<vector<Block*> > map; // 要對 物件進行操作 不用指標會有 call by value 的問題
	int row; 
	int col;

	Player player;
	
	
	int level;
	int times;

	void mapReset();

public:

	World();


	//顯示
	void drawUI();
	void showstate(string state);

	void drawmap();
	void update();


	//遊戲機制
	void start();
	void play();
	void intro();
	void nextLevel();
	void end();
	void restart();
	bool checkwin();

	bool loadmap();
	void printOriginmap();
	void printmap();
	

	void moveBlockTo(int row , int col, Block);

	bool Diecheck();

	void playerUp();
	void playerDown();
	void playerLeft();
	void playerRight();


};

