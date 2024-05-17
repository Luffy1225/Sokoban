#pragma once

#ifndef ICON_H
#define ICON_H

#include <vector>
#include <iostream>
#include <string>
#include <map>

using namespace std;

class Icon {
public:
	static const char player;
	static const char obstacle;
	static const char none;
	static const char box;
	static const char target;
};

//const char Icon::player = '0';
//const char Icon::obstacle = '/';
//const char Icon::none = '-';
//const char Icon::box = '1';
//const char Icon::target = '2';

class Block
{

protected:

	vector<string> shape;
	int sizeOfBlock= 0;
	int pos_x;
	int pos_y;

		

public:
	virtual void print();
	Block(int x, int y);
	Block();

};

#endif // ICON_H
