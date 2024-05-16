#pragma once
#include <vector>
#include <iostream>
#include <string>

using namespace std;


class Block
{
protected:
	vector<string> shape;
	int sizeOfBlock;
	int pos_x;
	int pos_y;

	virtual void print();
		

public:


};

