#include "World.h"
#include <string>
#include <fstream> 
#include <iostream>
#include <iomanip>

using namespace std;

World::World() {
	level = 1; // start with level one
	times = 0; //�B��
	col = 0, row = 0;

	cout << "World Initial" << endl;
}


void World::drawmap() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			map[i][j]->print();
		}
		cout << endl;
	}
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
	drawUI();
	showstate("�C���}�l");

	play();

}

void World::play() {
	loadmap();
	drawmap();

}


void World::end(){
}
void World::restart(){
}

bool World::loadmap() {
	string index;
	index = to_string(level);

	string filename = "mission" + index + ".txt";

	ifstream file(filename, ios::in);

	if (!file) {
		cout << "Can't open the file : \"" + filename + "\"" << endl;

		return false;
	}
	else {

		file >> row >> col;
		charmap.resize(row, vector<char>(col));
		map.resize(row, vector<Block*>(col));

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				char ch;
				file >> ch;
				charmap[i][j] = ch;
				
				if (ch == Icon::player) {
					player.playerSetXYPos(row, col);
					map[i][j] = new Player(row, col);
				}
				else if (ch == Icon::box) {
					map[i][j] = new Box(row, col);
					// ���@�ǳB�z�c�l���ާ@
				}
				else if (ch == Icon::target) {
					map[i][j] = new Target(row, col);
					// ���@�ǳB�z�ؼЪ��ާ@
				}
				else if (ch == Icon::obstacle) {
					map[i][j] = new Obstacle(row, col);
					// ���@�ǳB�z������ާ@
				}
				else if (ch == Icon::none) {
					map[i][j] = new Block(row, col);
					// ���@�ǳB�z�Ŧa���ާ@
				}
				else {
					map[i][j] = nullptr;
					showstate("Null pointer");
					// ����L���p���w�]�B�z
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
			cout << charmap[i][j] ;
		}
		cout << endl;
	}
}
void World::nextLevel() {
	level++;
	system("cls");
	loadmap();
	play();

}


void World::playerUp() {
	// �ˬd�e�����S���c�l 
	// �S���c�l -> �O���O��� ->
	int x = player.x();
	int y = player.y();

	int above = x - 1;

	if (above < 0 || charmap[x - 1][y] == Icon::obstacle) { // (above < 0)�W�Lmap��� , (charmap[x - 1][y] == '/')�J�����
		cout << "�L�k����" << endl;
		return;
	}
	

	if ( charmap[x-1][y] == Icon::none) { // �Ŧa �i�H���W
		char temp = charmap[x][y];
		charmap[x][y] = charmap[x - 1][y];
		charmap[x - 1][y] = temp;
	}
	else if (charmap[x - 1][y] == Icon::box && charmap[x - 2][y] == Icon::none) { // �p�G�W��O�c�l �A�ˬd �c�l�W�観�S���Ŷ� 
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

 
void World::drawUI() {
	// gotoxy ui�C
	cout << " ======================================================= " << endl
		<< "| �ܮw�f                           �樫�B��: " << std::setw(5) << right << times << " �B" << "   |" << endl
		<< "|                                                       |" << endl
		<< "| W : �W , S : �U , A : �� , D : �k                     |" << endl
		<< " ======================================================= " << endl
		;
}

void World::showstate(string state) {
	//goto ���A��m
	cout << "�ثe���A: "  << state << endl;
}


