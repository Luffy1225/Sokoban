#pragma once
#include <vector>
#include "Block.h"

using namespace std;

class World
{
private:
	vector<vector<char>> map;
	int level = 1;


	void mapReset();

public:

	World();
	void draw();
	void update();

	void intro();
	void end();
	void restart();

	void loadmap();

	void moveBlockTo(int row , int col, Block);




};

