#pragma once
#include <vector>
#include "Block.h"

using namespace std;

class World
{
private:
	vector<vector<char> > map;
	int row; 
	int col;
	
	
	int level;
	

	void mapReset();

public:

	World();
	void draw();
	void update();

	
	
	void intro();
	void nextLevel();
	void end();
	void restart();

	bool loadmap();
	void printOriginmap();
	void printmap();
	

	void moveBlockTo(int row , int col, Block);




};

