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
	vector<vector<Block*> > map; // �n�� ����i��ާ@ ���Ϋ��з|�� call by value �����D
	int row; 
	int col;

	Player player;
	
	
	int level;
	int steps;

#pragma region UIsetting

	int UI_main_X = 0;
	int UI_main_Y = 1;

	int UI_state_X = 0;
	int UI_state_Y = 8;

	int UI_map_X = 0;
	int UI_map_Y = 10;


#pragma endregion





	bool running ;

	void mapReset();

public:

	World();


	//���
	void drawUI();
	void showstate(string state);

	void mainfresh();


	void drawmap();
	void update();


	//�C������
	void start();
	void play();
	void intro();
	void nextLevel();
	void end();
	void restart();
	bool checkwin();
	void celebrate();


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

