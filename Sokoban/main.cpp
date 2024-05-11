#include <string>
#include <iostream>
#include "World.h"



using namespace std;

int main()
{

    World  myWorld;
    myWorld.loadmap();
    myWorld.printOriginmap();
    myWorld.nextLevel();

    myWorld.loadmap();
    myWorld.printOriginmap();
    myWorld.nextLevel();

    myWorld.loadmap();
    myWorld.printOriginmap();


    return 0;
}
