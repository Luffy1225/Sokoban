#include "World.h"
#include <string>

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

void World::loadmap(){

    string index;
    index = to_string(level);

    string filename = "mission" + index + "txt";



}

void World::moveBlockTo(int row, int col, Block) {

}

void World::mapReset() {
    for (int i = 0; i < map.size(); i++) {
        map[i].clear();
    }
    map.clear();
}

