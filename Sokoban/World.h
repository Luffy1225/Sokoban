#pragma once
#include <vector>
#include "Block.h"
#include "Player.h"
#include "Box.h"
#include "Obstacle.h"
#include "Target.h"
#include "Tools.h"


using namespace std;

class World
{
private:
	vector<vector<char> > charmap;
	vector<vector<Block*> > map; // 要對 物件進行操作 不用指標會有 call by value 的問題
	vector<Target*> targetVector;
	vector<Box*> BoxVector;


	int row; 
	int col;

	Player player;
	
	int MODE; // 讀檔 模式 1. 正常模式 2. 助教模式
	
	int level; 
	int steps;
	int stepsSum;
	string Filename;


	thread soundThread;
#pragma region UIsetting

	int UI_main_X;
	int UI_main_Y;
	int UI_state_X;
	int UI_state_Y;
	int UI_map_X;
	int UI_map_Y;


#pragma endregion

	bool running;
	bool restartRequest;

	void mapReset();

public:

	World();


	//顯示
	void drawLOGO(Color color = Col_RESET);
	void drawUI();
	void showstate(string state , Color color = Col_RESET);

	void mainfresh();

	void drawmap();
	void update();

	//遊戲機制
	void start();
	void intro();
	void modeSelect();
	void play();
	void nextLevel();
	void end();
	void restart();
	bool checkwin();
	bool checklose();
	bool checkstate();
	void celebrate();


	bool loadmap();
	void printOriginmap();
	void printmap();

	bool Diecheck();

	void playerUp();
	void playerDown();
	void playerLeft();
	void playerRight();

	//地圖 
	void createMap();


	//音樂
	void playBGM(const wstring& wfilename);
	void stopBGM();

};

