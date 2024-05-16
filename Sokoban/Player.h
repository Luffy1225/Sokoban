#pragma once
#include "Block.h"

class Player : public Block
{
private:



public:
	
	Player();
	Player(int x , int y);





	int x();
	int y();
	
	void playerSetXYPos(int , int );
	void playerSet_Xpos(int );
	void playerSet_Ypos(int );

};

