#include "World.h"
#include <string>
#include <fstream> 
#include <iostream>

using namespace std;

World::World() {

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

    string index;
    index = to_string(level);

    string filename = "mission" + index + ".txt";

	ifstream file(filename);
	
	if(file.fail()){
		cout << "Can't open the file : \"" + filename + "\"" << endl;
	}
	else{
			 
		cin >> row >> col ;
		
		for(int i = 0 ; i< row ; i++){
			for(int j = 0 j < col ; j++){
				char ch;
				cin >> ch;
				map[i][j] = ch; 
			}
		}
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


void World::printmap(){
	for(int i = 0 ; i < row ; i++){
		for(int j = 0 ; j < col ; j++){
			cout << map[i][j] ;
		}
		cout << endl;
	}
}


