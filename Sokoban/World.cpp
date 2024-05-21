#include "World.h"
#include "Tools.h"
#include <string>
#include <fstream> 
#include <iostream>
#include <iomanip>
#include <conio.h>
 
#define LEVEL_AMOUNT 3


using namespace std;

World::World() {
	level = 1; // start with level one
	steps = 0; //�B��

	running = true;

	col = 0, row = 0;
}


void World::drawmap() {

	Tools::gotoY(UI_map_Y);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			map[i][j]->print();
		}
		cout << endl;
	}

	//printOriginmap();
}

void World::intro(){ // �C������
	std::cout << "�C���W�١G�ܮw�f\n\n"
		<< "�C�����СG\n�m�ܮw�f�n�O�@�ڥH���c�l���D�D���q���C���C�b�C�����A���a�N��t�@�W�ܮw�u�H�A�ݭn�N�c�l���ʨ���w����m�A�F����w�ƶq�Y�i�L���C�M�ӡA���c�l�ä��O�@��e�����Ʊ��A���a�ݭn�Ҽ{�C�@�B�����ʡA�קK���J�x�ҡC\n\n"
		<< "�C���W�h�G\n1. ���a�i�H�H�u���v���覡���ʽc�l�A�V���B�k�B�W�B�U�|�Ӥ�V���ʡC\n2. ���a�L�k��L����A�]�L�k�N�c�l�԰ʡ]�u����ʽc�l�^�C\n3. �c�l�P���a���L�k��L����C\n4. �b�������d���A�O�Ҧs�b�@�����|�i�H�N�c�l���ʨ���I�C\n5. ���a�i�H���N���ʡA���@�w�n���b�c�l����C\n6. �Y�Ͻc�l�w�g��F���I�A���i�H�Q���ʡC\n7. �{������ۦ�P�_�L�Ѫ����p�A�Ҧp�A�c�l�Q���J�����L�k�A�Q���ʡA�������ä��O���I�A�h�|�i�����a�����C���C\n\n"
		<< "�C���ާ@�G\n���a�i�H�ϥ���L�ηƹ��i��ާ@�A�ھګ��ܲ��ʤu�H�P�c�l�A���ʽc�l����w��m�Y�i�q�L���d�C\n\n"
		<< "�Ʊ�o���C�����лP�W�h�����U�A��n�a�F�ѡm�ܮw�f�n���C�����k�I\n";
	system("pause");
	system("cls");
}

void World::start() { // �C���}�l��m

	Tools::hideCursor();

	intro();
	drawUI();
	showstate("�C���}�l");

	play();

}

void World::play() { //�C���D�{��

	loadmap();
	drawmap();
		
	int ch;

	while (running) {   

		if (checkwin() == true) {
			
			nextLevel();

			if (running) {
				celebrate();
				system("cls");
				loadmap();
				drawUI();
				drawmap();
			}

		}

		if (_kbhit()) {  // �p�G��������U
			ch = _getch();  // �ϥ�_getch()���������U�����
			switch (ch) {
			case 'w' :
				//std::cout << "�V�W"  << std::endl;
				playerUp();
				steps++;
				update();

				break;
			case 'a' :
				//std::cout << "�V��" << std::endl;
				playerLeft();
				steps++;
				update();

				break;
			case 's':
				//std::cout << "�V�U" << std::endl;
				playerDown();
				steps++;
				update();

				break;
			case 'd' :
				//std::cout << "�V�k" << std::endl;
				playerRight();
				steps++;
				update();

				break;
			case 27:  // ����UESC�ɴ`���AESC�䪺��ȬO27
				running = false;
				break;
			default:
				string txt = "�L�Ī���ȡG" + to_string(ch);
				showstate(txt);
				break;
			}

			Tools::sleepMilsec(50);
		}
	}

}


void World::end(){ // �̲׹L��
	for (int i = 0; i < 100; i++) {
		cout << "���ߧ��������}��!!!!!!!!!" << endl;
	}
}

void World::celebrate() {  //�C���L��
	string txt = "���߳q�L �� " + to_string(level) + " ��";
	showstate(txt);
	system("pause");
}


void World::restart(){  
	level = 0;
	play();
}

bool World::loadmap() {
	mapReset();

	string index;
	index = to_string(level);

	//index = "2";/////////////////////////////

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
					player.playerSetXYPos(i, j);
					map[i][j] = new Player(i, j);
				}
				else if (ch == Icon::box) {
					map[i][j] = new Box(i, j);
					// ���@�ǳB�z�c�l���ާ@
				}
				else if (ch == Icon::target) {
					map[i][j] = new Target(i, j);
					// ���@�ǳB�z�ؼЪ��ާ@
				}
				else if (ch == Icon::obstacle) {
					map[i][j] = new Obstacle(i, j);
					// ���@�ǳB�z������ާ@
				}
				else if (ch == Icon::none) {
					map[i][j] = new Block(i, j);
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
		charmap[i].clear();
    }
    map.clear();
	charmap.clear();
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

	if (level == LEVEL_AMOUNT) {
		end();
		running = false;
	}
	else
	{
		level++;
	}
}


void World::playerUp() {
	int x = player.x(); // ������a�� x �y��
	int y = player.y(); // ������a�� y �y��

	int above = x - 1; // �p�⪱�a�W�誺�y��

	// �ˬd���a�W��O�_�W�X�a����ɩάO�J���ê��
	if (above < 0 || charmap[above][y] == Icon::obstacle) {
		showstate("�L�k����");
		return; // �����禡
	}

	// �p�G���a�W��O�Ŧa�A�i�H���ʪ��a
	if (charmap[above][y] == Icon::none) {
		// �洫���a�M�Ŧa����m
		char temp = charmap[x][y];
		charmap[x][y] = charmap[above][y];
		charmap[above][y] = temp;

		// ��s�a�ϤW���a����m
		player.playerAddX(-1);

		// �洫�a�ϤW��Block����
		Block* tempBlock = map[x][y];
		map[x][y] = map[above][y];
		map[above][y] = tempBlock;


	}
	// �p�G���a�W��O�c�l�A�ˬd�O�_���������Ŷ����ʽc�l
	else if (charmap[above][y] == Icon::box) {
		if (charmap[x - 2][y] == Icon::none) {
			char temp = charmap[x][y];
			charmap[x][y] = charmap[x - 2][y];
			charmap[x - 2][y] = charmap[above][y];
			charmap[above][y] = temp;

			player.playerAddX(-1);

			// �洫�a�ϤW��Block����
			Block* tempBlock = map[x][y];
			map[x][y] = map[x - 2][y];
			map[x - 2][y] = map[above][y];
			map[above][y] = tempBlock;
		}
		else if (charmap[x - 2][y] == Icon::target) { // �I����I�S��
			char temp = charmap[x][y];

			charmap[x - 2][y] = charmap[above][y];
			charmap[above][y] = temp;
			charmap[x][y] = '-';

			player.playerAddX(-1);

			// �洫�a�ϤW��Block����
			Block* tempBlock = map[x][y];
			map[x - 2][y] = map[above][y];
			map[above][y] = map[x][y];
			map[x][y] = new Block(x, y);
		}
	}
	else {
		cout << "�������p" << endl; // ��X�������p���T��
	}


}
void World::playerDown() {
	int x = player.x(); // ������a�� x �y��
	int y = player.y(); // ������a�� y �y��

	int below = x + 1; // �p�⪱�a�U�誺�y��

	// �ˬd���a�U��O�_�W�X�a����ɩάO�J���ê��
	if (below >= charmap.size() || charmap[below][y] == Icon::obstacle) {
		showstate("�L�k����");
		return; // �����禡
	}

	// �p�G���a�U��O�Ŧa�A�i�H���ʪ��a
	if (charmap[below][y] == Icon::none) {
		// �洫���a�M�Ŧa����m
		char temp = charmap[x][y];
		charmap[x][y] = charmap[below][y];
		charmap[below][y] = temp;

		// ��s�a�ϤW���a����m
		player.playerAddX(1);

		// �洫�a�ϤW��Block����
		Block* tempBlock = map[x][y];
		map[x][y] = map[below][y];
		map[below][y] = tempBlock;


	}
	// �p�G���a�U��O�c�l�A�ˬd�O�_���������Ŷ����ʽc�l
	else if (charmap[below][y] == Icon::box) {
		if (charmap[x + 2][y] == Icon::none) {
			char temp = charmap[x][y];
			charmap[x][y] = charmap[x + 2][y];
			charmap[x + 2][y] = charmap[below][y];
			charmap[below][y] = temp;

			player.playerAddX(1);

			// �洫�a�ϤW��Block����
			Block* tempBlock = map[x][y];
			map[x][y] = map[x + 2][y];
			map[x + 2][y] = map[below][y];
			map[below][y] = tempBlock;
		}
		else if (charmap[x + 2][y] == Icon::target) { // �I����I�S��
			char temp = charmap[x][y];

			charmap[x + 2][y] = charmap[below][y];
			charmap[below][y] = temp;
			charmap[x][y] = '-';

			player.playerAddX(1);

			// �洫�a�ϤW��Block����
			Block* tempBlock = map[x][y];
			map[x + 2][y] = map[below][y];
			map[below][y] = map[x][y];
			map[x][y] = new Block(x, y);
		}
	}
	else {
		cout << "�������p" << endl; // ��X�������p���T��
	}

}
void World::playerLeft() {
	int x = player.x(); // ������a�� x �y��
	int y = player.y(); // ������a�� y �y��

	int left = y - 1; // �p�⪱�a���誺�y��

	// �ˬd���a����O�_�W�X�a����ɩάO�J���ê��
	if (left < 0 || charmap[x][left] == Icon::obstacle) {
		showstate("�L�k����");
		return; // �����禡
	}

	// �p�G���a����O�Ŧa�A�i�H���ʪ��a
	if (charmap[x][left] == Icon::none) {
		// �洫���a�M�Ŧa����m
		char temp = charmap[x][y];
		charmap[x][y] = charmap[x][left];
		charmap[x][left] = temp;

		// ��s�a�ϤW���a����m
		player.playerAddY(-1);

		// �洫�a�ϤW��Block����
		Block* tempBlock = map[x][y];
		map[x][y] = map[x][left];
		map[x][left] = tempBlock;


	}
	// �p�G���a����O�c�l�A�ˬd�O�_���������Ŷ����ʽc�l
	else if (charmap[x][left] == Icon::box) {
		if (charmap[x][y - 2] == Icon::none) {
			char temp = charmap[x][y];
			charmap[x][y] = charmap[x][y - 2];
			charmap[x][y - 2] = charmap[x][left];
			charmap[x][left] = temp;

			player.playerAddY(-1);

			// �洫�a�ϤW��Block����
			Block* tempBlock = map[x][y];
			map[x][y] = map[x][y - 2];
			map[x][y - 2] = map[x][left];
			map[x][left] = tempBlock;
		}
		else if (charmap[x][y - 2] == Icon::target) { // �I����I�S��
			char temp = charmap[x][y];

			charmap[x][y - 2] = charmap[x][left];
			charmap[x][left] = temp;
			charmap[x][y] = '-';

			player.playerAddY(-1);

			// �洫�a�ϤW��Block����
			Block* tempBlock = map[x][y];
			map[x][y - 2] = map[x][left];
			map[x][left] = map[x][y];
			map[x][y] = new Block(x, y);
		}
	}
}
void World::playerRight() {
	int x = player.x(); // ������a�� x �y��
	int y = player.y(); // ������a�� y �y��

	int right = y + 1; // �p�⪱�a�k�誺�y��

	// �ˬd���a�k��O�_�W�X�a����ɩάO�J���ê��
	if (right >= charmap[0].size() || charmap[x][right] == Icon::obstacle) {
		showstate("�L�k����");
		return; // �����禡
	}

	// �p�G���a�k��O�Ŧa�A�i�H���ʪ��a
	if (charmap[x][right] == Icon::none) {
		// �洫���a�M�Ŧa����m
		char temp = charmap[x][y];
		charmap[x][y] = charmap[x][right];
		charmap[x][right] = temp;

		// ��s�a�ϤW���a����m
		player.playerAddY(1);

		// �洫�a�ϤW��Block����
		Block* tempBlock = map[x][y];
		map[x][y] = map[x][right];
		map[x][right] = tempBlock;

	}
	// �p�G���a�k��O�c�l�A�ˬd�O�_���������Ŷ����ʽc�l
	else if (charmap[x][right] == Icon::box) {
		if (charmap[x][y + 2] == Icon::none) {
			char temp = charmap[x][y];
			charmap[x][y] = charmap[x][y + 2];
			charmap[x][y + 2] = charmap[x][right];
			charmap[x][right] = temp;

			player.playerAddY(1);

			// �洫�a�ϤW��Block����
			Block* tempBlock = map[x][y];
			map[x][y] = map[x][y + 2];
			map[x][y + 2] = map[x][right];
			map[x][right] = tempBlock;
		}
		else if (charmap[x][y + 2] == Icon::target) { // �I����I�S��
			char temp = charmap[x][y];

			charmap[x][y + 2] = charmap[x][right];
			charmap[x][right] = temp;
			charmap[x][y] = '-';

			player.playerAddY(1);

			// �洫�a�ϤW��Block����
			Block* tempBlock = map[x][y];
			map[x][y + 2] = map[x][right];
			map[x][right] = map[x][y];
			map[x][y] = new Block(x, y);
		}
	}
	else {
		cout << "�������p" << endl; // ��X�������p���T��
	}



}

 
void World::mainfresh() {
	Tools::gotoY(UI_main_Y);
	cout << "| �ܮw�f                           �樫�B��: " << std::setw(5) << right << steps << " �B" << "   |" << endl;

}


void World::drawUI() {
	// gotoxy ui�C
	cout << " ======================================================= " << endl
		<< "| �ܮw�f                           �樫�B��: " << std::setw(5) << right << steps << " �B" << "   |" << endl
		<< "|                                                       |" << endl
		<< "| ���a : 0 , �c�l : 1 , ���I: 2 , ��� : /              |" << endl
		<< "|                                                       |" << endl
		<< "|                                                       |" << endl
		<< "| W : �W , S : �U , A : �� , D : �k                     |" << endl
		<< " ======================================================= " << endl
		;
}//const char Icon::player = '0';

void World::update() {
	mainfresh();
	showstate("");
	drawmap();

}

void World::showstate(string state) {
	//goto ���A��m
	Tools::gotoY(UI_state_Y);
	cout << "�ثe���A: "  << state << endl;
}


bool World::checkwin() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (charmap[i][j] == '2') {
				return false;
				break;
			}
		}
	}
	return true;
}