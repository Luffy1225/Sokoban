#include "World.h"
#include <string>
#include <fstream> 
#include <iostream>

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
}
void World::end(){
}
void World::restart(){
}

bool World::loadmap(){


	string prefix = ""; // C:// ¤§Ãþªº

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
		map.resize(row, vector<char>(col));


		for(int i = 0 ; i< row ; i++){
			for (int j = 0; j < col; j++) {
				char ch;
				file >> ch;
				map[i][j] = ch; 
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
			cout << map[i][j] ;
		}
		cout << endl;
	}
}


void World::nextLevel() {
	level++;
}

