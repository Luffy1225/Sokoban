#include "World.h"
#include <string>
#include <fstream> 
#include <iostream>

enum icon {
	player = '0',
	wall = '/',
	none = '-',
	box = '1',
	target = '2',
};



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
	std::cout << "�C���W�١G�ܮw�f\n\n"
		<< "�C�����СG\n�m�ܮw�f�n�O�@�ڥH���c�l���D�D���q���C���C�b�C�����A���a�N��t�@�W�ܮw�u�H�A�ݭn�N�c�l���ʨ���w����m�A�F����w�ƶq�Y�i�L���C�M�ӡA���c�l�ä��O�@��e�����Ʊ��A���a�ݭn�Ҽ{�C�@�B�����ʡA�קK���J�x�ҡC\n\n"
		<< "�C���W�h�G\n1. ���a�i�H�H�u���v���覡���ʽc�l�A�V���B�k�B�W�B�U�|�Ӥ�V���ʡC\n2. ���a�L�k��L����A�]�L�k�N�c�l�԰ʡ]�u����ʽc�l�^�C\n3. �c�l�P���a���L�k��L����C\n4. �b�������d���A�O�Ҧs�b�@�����|�i�H�N�c�l���ʨ���I�C\n5. ���a�i�H���N���ʡA���@�w�n���b�c�l����C\n6. �Y�Ͻc�l�w�g��F���I�A���i�H�Q���ʡC\n7. �{������ۦ�P�_�L�Ѫ����p�A�Ҧp�A�c�l�Q���J�����L�k�A�Q���ʡA�������ä��O���I�A�h�|�i�����a�����C���C\n\n"
		<< "�C���ާ@�G\n���a�i�H�ϥ���L�ηƹ��i��ާ@�A�ھګ��ܲ��ʤu�H�P�c�l�A���ʽc�l����w��m�Y�i�q�L���d�C\n\n"
		<< "�Ʊ�o���C�����лP�W�h�����U�A��n�a�F�ѡm�ܮw�f�n���C�����k�I\n";
	system("pause");
	system("cls");
}

void World::start() {
	intro();
	loadmap();


}


void World::end(){
}
void World::restart(){
}

bool World::loadmap(){


	string prefix = ""; // C:// ������

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
		//map.resize(row, vector<char>(col));
		charmap.resize(row, vector<char>(col));
		//map.resize(row, vector<Block>(col));
		map.resize(row, vector<Block*>(col));


		for(int i = 0 ; i< row ; i++){
			for (int j = 0; j < col; j++) {
				char ch;
				file >> ch;
				charmap[i][j] = ch; 



				switch (ch)
				{
				case '0':
					player.playerSetXYPos(row, col);
					break;

				case '1':
					break;
				case '2':
					break;
				case '/':
					break;
				case '-':
					break;
				}
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
			//cout << map[i][j] ;
		}
		cout << endl;
	}
}


void World::nextLevel() {
	level++;
}



void World::playerUp() {
	// �ˬd�e�����S���c�l 
	// �S���c�l -> �O���O��� ->
	int x = player.x();
	int y = player.y();

	int above = x - 1;

	if (above < 0 || charmap[x - 1][y] == icon::wall) { // (above < 0)�W�Lmap��� , (charmap[x - 1][y] == '/')�J�����
		cout << "�L�k����" << endl;
		return;
	}
	

	if ( charmap[x-1][y] == icon::none) { // �Ŧa �i�H���W
		char temp = charmap[x][y];
		charmap[x][y] = charmap[x - 1][y];
		charmap[x - 1][y] = temp;
	}
	else if (charmap[x - 1][y] == icon::box && charmap[x - 2][y] == icon::none) { // �p�G�W��O�c�l �A�ˬd �c�l�W�観�S���Ŷ� 
		// x-2    x-1
		// x-1     x
		// x      x-2
		char temp = charmap[x][y];
		charmap[x][y] = charmap[x - 2][y];
		charmap[x - 2][y] = charmap[x - 1][y];
		charmap[x - 1][y] = temp;
	}
	else
	{
		cout << "�������p" << endl;
	}
}
void World::playerDown() {

}
void World::playerLeft() {

}
void World::playerRight() {

}

 