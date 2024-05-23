#include "World.h"
#include "Tools.h"
#include <windows.h> // gotoxy
#include <mmsystem.h> // playbgm 
#include <conio.h> // keyboard in
#include <string> // string
#include <fstream>  // file
#include <iostream> // io
#include <iomanip> // io
#include <thread> // thread
 
#pragma comment(lib, "winmm.lib") //music

#define LEVEL_AMOUNT 3

using namespace std;

World::World() {
	level = 1; // start with level one
	steps = 0; //�B��
	stepsSum = 0;

	MODE = -1;
	running = true;
	restartRequest = false;

	col = 0, row = 0;

	UI_main_X = 0;
	UI_main_Y = 1;
	UI_state_X = 0;
	UI_state_Y = 10;
	UI_map_X = 0;
	UI_map_Y = 12;

	


}


void World::drawmap() {

	Tools::gotoY(UI_map_Y);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			map[i][j]->print();
		}
		cout << endl;
	}

}

void World::drawLOGO(Color color) {
	Tools::SetColor(color);
	cout << " ================================================================ " << endl
		<< "|     ____    ______   _  __  ______   _____     _     _   _     |" << endl
		<< "|    / ___|  /  __  \\ | |/ / /  __  \\ |  _  )   / \\   | \\ | |    |" << endl
		<< "|    \\____ \\ | |  | | | ' /  | |  | | | |_) |  / _ \\  |  \\| |    |" << endl
		<< "|     ___) | | |__| | | . \\  | |__| | | |_) ) / ___ \\ | |\\  |    |" << endl
		<< "|    |____/  \\______/ |_|\\_\\ \\______/ |____/ /_/   \\_\\|_| \\_|    |" << endl
		<< "|                                                                |" << endl
	    << " ================================================================ " << endl;

	Tools::SetColor(Col_RESET);
}



void World::intro(){ // �C������

	drawLOGO(Col_blue);

	std::cout << "\n�C���W�١G�ܮw�f\n";
	Tools::SetColor(Col_yellow); cout << "�C�����СG"; Tools::SetColor(Col_RESET); cout << "\n�m�ܮw�f�n�O�@�ڥH���c�l���D�D���q���C���C�b�C�����A���a�N��t�@�W�ܮw�u�H�A�ݭn�N�c�l���ʨ���w����m�A�F����w�ƶq�Y�i�L���C�M�ӡA���c�l�ä��O�@��e�����Ʊ��A���a�ݭn�Ҽ{�C�@�B�����ʡA�קK���J�x�ҡC\n\n";
	Tools::SetColor(Col_yellow); cout << "�C���W�h�G"; Tools::SetColor(Col_RESET); cout << "\n1. ���a�i�H�H�u���v���覡���ʽc�l�A�V���B�k�B�W�B�U�|�Ӥ�V���ʡC\n2. ���a�L�k��L����A�]�L�k�N�c�l�԰ʡ]�u����ʽc�l�^�C\n3. �c�l�P���a���L�k��L����C\n4. �b�������d���A�O�Ҧs�b�@�����|�i�H�N�c�l���ʨ���I�C\n5. ���a�i�H���N���ʡA���@�w�n���b�c�l����C\n6. �Y�Ͻc�l�w�g��F���I�A���i�H�Q���ʡC\n7. �{������ۦ�P�_�L�Ѫ����p�A�Ҧp�A�c�l�Q���J�����L�k�A�Q���ʡA�������ä��O���I�A�h�|�i�����a�����C���C\n\n";
	Tools::SetColor(Col_yellow); cout << "�C���ާ@�G"; Tools::SetColor(Col_RESET); cout << "\n���a�i�H�ϥΡu W �v�u A �v�u S �v�u D �v�ާ@�A�ھګ��ܲ��ʤu�H�P�c�l�A���ʽc�l����w��m�Y�i�q�L���d�C\n\n";
	cout << "�Ʊ�o���C�����лP�W�h�����U�A��n�a�F�ѡm�ܮw�f�n���C�����k�I\n\n";

	Tools::SetColor(Col_red); cout << "!!!!���U Alt + Enter �i�J���ù� �H�K�X�{���~!!!!\n"; Tools::SetColor(Col_RESET);

	system("pause");
	system("cls");
}

void World::start() { // �C���}�l��m

	Tools::hideCursor();
	wstring wfilename = L"sokoban.wav";
	soundThread = thread(&World::playBGM, this, wfilename);

	// �T�O���֤w�g�}�l����
	Sleep(100);
	intro();
	modeSelect();
	system("cls");
	play();

}

void World::modeSelect() {

	bool selected = false;
	do {
		Tools::gotoY(1);
		drawLOGO();

		int choice;
		cout << "�п�J�a�ϼҦ� :" << endl;
		cout << "1. ���`�Ҧ� mission 1 ~ 3 " << endl;
		cout << "2. �U�мҦ� ����a��" << endl;
		cin >> choice;

		switch (choice)
		{

		case 1:
			MODE = 1;
			selected = true;
			break;

		case 2:
			MODE = 2;
			selected = true;
			break;

		default:
			system("cls");
			std::cout << "�L�Ī���ܡA�п�J 1 �� 2�C\n"; break;
		}


	} while (selected != true);

}



void World::play() { //�C���D�{��

	if (loadmap() == true) {
		drawUI();
		drawmap();
	}

	while (running) {

		//�ˬd�O�_���U���s�}�l���s�]�o�̰��]���U 'R' ��ӭ��s�}�l�^
		if (_kbhit()) {  // �p�G��������U
			int ch;
			ch = _getch();  // �ϥ�_getch()���������U�����
			switch (ch) {
			case 'w':
				playerUp();

				break;
			case 'a':
				playerLeft();

				break;
			case 's':
				playerDown();

				break;
			case 'd':
				playerRight();

				break;
			case 'r':
				restartRequest = true;
				restart();
				restartRequest = false;

				break;
			case 27:  // ����UESC�ɴ`���AESC�䪺��ȬO27
				running = false;
				break;
			default:
				string txt = "�L�Ī���ȡG" + to_string(ch);
				showstate(txt, Col_red);
				break;
			}

			// ��V�C���e��
			// �Ҧpø�s����B�a�ϵ�

			update();
			Tools::sleepMilsec(50); //delay ����פӧ�

			if (checkwin() == true) {
				stepsSum += steps;
				nextLevel();

				/*if (running) {
					celebrate();
					system("cls");
					loadmap();
					drawUI();
					drawmap();
				}*/

			}
			else if (checklose() == true) {
				showstate("�w�����I�� 'R' �䭫�s�}�l�A�Ϋ� ESC ���}�C���C", Col_red);

				while (true) {
					if (_kbhit()) {  // �p�G��������U
						int ch = _getch();  // �ϥ�_getch()���������U�����
						if (ch == 'r') {
							restartRequest = true;
							restart();
							restartRequest = false;
							break;
						}
						else if (ch == 27) {  // ����UESC��
							running = false;
							break;
						}
					}
				}
			}

		}
	}

	stopBGM();	

}

void World::end(){ // �̲׹L��
	system("cls");
	Tools::gotoX(0);

	Tools::SetColor(Col_yellow);

	cout << " ================================================================ " << endl
		<< "|     ____    ______   _  __  ______   _____     _     _   _     |" << endl
		<< "|    / ___|  /  __  \\ | |/ / /  __  \\ |  _  )   / \\   | \\ | |    |" << endl
		<< "|    \\____ \\ | |  | | | ' /  | |  | | | |_) |  / _ \\  |  \\| |    |" << endl
		<< "|     ___) | | |__| | | . \\  | |__| | | |_) ) / ___ \\ | |\\  |    |" << endl
		<< "|    |____/  \\______/ |_|\\_\\ \\______/ |____/ /_/   \\_\\|_| \\_|    |" << endl
		<< "|                                                                |" << endl
		<< "|                                                                |" << endl
		<< "|                                                                |" << endl
		<< "|                                                                |" << endl
		<< "|                          ���߹L��!!!!                          |" << endl
		<< "|                     �`��O�B�� : " << setw(5) << stepsSum << " �B                      |" << endl
		<< "|                                                                |" << endl
		<< "|                            Made by                             |" << endl
		<< "|                 ��u�@   411285052   ���f��                    |" << endl
		<< "|                                                                |" << endl
		<< "|                                                                |" << endl
		<< " ================================================================ " << endl <<endl;

	Tools::SetColor(Col_RESET);
	system("pause");
	system("cls");
}

void World::celebrate() {  //�C���L��
	string txt = "���߳q�L �� " + to_string(level) + " ��!!!!";
	showstate(txt , Col_yellow);
	system("pause");
}

void World::restart(){  
	
	steps = 0;
	loadmap();
	showstate("�C�����s�}�l",Col_red);
}

bool World::loadmap() {
	mapReset();

	ifstream file;
	string filename;

	if (MODE == 1) {  //���`�Ҧ�

		string index;
		index = to_string(level);
		//index = "2";/////////////////////////////

		filename = "mission" + index + ".txt";
		//filename = "w";
		Filename = filename;

	}
	else {  //�U�мҦ�
		if (restartRequest != true) {
			drawLOGO();

			cout << "�п�J �a���ɮצW��: ";
			cin >> filename;
			Filename = filename;
			system("cls");

		}

	}
	file = ifstream(Filename, ios::in);

	if (!file) {
		system("cls");
		Tools::SetColor(Col_red);
		cout << "Can't open the file : \"" + Filename + "\"" << endl;
		Tools::SetColor(Col_RESET);
		running = false;
		system("pause");
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
					
					player.SetXYPos(i, j);
					map[i][j] = new Player(i, j);
				}
				else if (ch == Icon::box) {
					Box* temp = new Box(i, j); // �ϥ� new �ʺA���t Box ����
					map[i][j] = temp; // �N���Цs�x�� map ��
					BoxVector.push_back(temp); // �N���Цs�x�� BoxVector ��
					// ���@�ǳB�z�c�l���ާ@
				}
				else if (ch == Icon::target) {
					Target* temp = new Target(i,j);
					map[i][j] = temp;
					targetVector.push_back(temp);
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
					showstate("Null pointer", Col_red);
					// ����L���p���w�]�B�z
				}

			}
		}

		showstate("�C���}�l");
		return true;

	}
	file.close();
}

void World::mapReset() {
    for (int i = 0; i < map.size(); i++) {
        map[i].clear();
		charmap[i].clear();
    }
    map.clear();
	charmap.clear();

	BoxVector.clear();
	targetVector.clear();
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

	if (level == LEVEL_AMOUNT || MODE == 2) {
		end();
		running = false;
	}
	else
	{
		celebrate();
		system("cls");

		level++;
		steps = 0;

		loadmap();
		drawUI();
		drawmap();


	}
}

void World::playerUp() {
	int x = player.x(); // ������a�� x �y��
	int y = player.y(); // ������a�� y �y��

	int above = x - 1; // �p�⪱�a�W�誺�y��

	// �ˬd���a�W��O�_�W�X�a����ɩάO�J���ê��
	if (above < 0 || charmap[above][y] == Icon::obstacle) {
		showstate("�L�k����" , Col_red);
		return; // �����禡
	}

	steps++;


	// �p�G���a�W��O�Ŧa�A�i�H���ʪ��a
	if (charmap[above][y] == Icon::none) {
		// �洫���a�M�Ŧa����m
		char temp = charmap[x][y];
		charmap[x][y] = charmap[above][y];
		charmap[above][y] = temp;

		// ��s�a�ϤW���a����m
		player.AddX(-1);

		// �洫�a�ϤW��Block����
		Block* tempBlock = map[x][y];
		map[x][y] = map[above][y];
		map[above][y] = tempBlock;

		// ��sBlock��m
		map[x][y]->SetXYPos(x, y);
		map[above][y]->SetXYPos(above,y);
	}
	// �p�G���a�W��O�c�l�A�ˬd�O�_���������Ŷ����ʽc�l
	else if (charmap[above][y] == Icon::box) {
		if (charmap[x - 2][y] == Icon::none) {
			char temp = charmap[x][y];
			charmap[x][y] = charmap[x - 2][y];
			charmap[x - 2][y] = charmap[above][y];
			charmap[above][y] = temp;

			player.AddX(-1);

			// �洫�a�ϤW��Block����
			Block* tempBlock = map[x][y];
			map[x][y] = map[x - 2][y];
			map[x - 2][y] = map[above][y];
			map[above][y] = tempBlock;

			map[x][y]->SetXYPos(x,y);
			map[above][y]->SetXYPos(above,y);
			map[x - 2][y]->SetXYPos(x-2,y);
		}
		else if (charmap[x - 2][y] == Icon::target) { // �I����I�S��
			char temp = charmap[x][y];

			charmap[x - 2][y] = charmap[above][y];
			charmap[above][y] = temp;
			charmap[x][y] = '-';

			player.AddX(-1);

			// �洫�a�ϤW��Block����
			Block* tempBlock = map[x][y];
			map[x - 2][y] = map[above][y];
			map[above][y] = map[x][y];
			map[x][y] = new Block(x, y);

			map[x][y]->SetXYPos(x, y);
			map[above][y]->SetXYPos(above, y);
			map[x - 2][y]->SetXYPos(x - 2, y);


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
		showstate("�L�k����", Col_red);
		return; // �����禡
	}

	steps++;

	// �p�G���a�U��O�Ŧa�A�i�H���ʪ��a
	if (charmap[below][y] == Icon::none) {
		// �洫���a�M�Ŧa����m
		char temp = charmap[x][y];
		charmap[x][y] = charmap[below][y];
		charmap[below][y] = temp;

		// ��s�a�ϤW���a����m
		player.AddX(1);

		// �洫�a�ϤW��Block����
		Block* tempBlock = map[x][y];
		map[x][y] = map[below][y];
		map[below][y] = tempBlock;

		// ��sBlock��m
		map[x][y]->SetXYPos(x, y);
		map[below][y]->SetXYPos(below, y);
	}
	// �p�G���a�U��O�c�l�A�ˬd�O�_���������Ŷ����ʽc�l
	else if (charmap[below][y] == Icon::box) {
		if (charmap[x + 2][y] == Icon::none) {
			char temp = charmap[x][y];
			charmap[x][y] = charmap[x + 2][y];
			charmap[x + 2][y] = charmap[below][y];
			charmap[below][y] = temp;

			player.AddX(1);

			// �洫�a�ϤW��Block����
			Block* tempBlock = map[x][y];
			map[x][y] = map[x + 2][y];
			map[x + 2][y] = map[below][y];
			map[below][y] = tempBlock;

			map[x][y]->SetXYPos(x, y);
			map[below][y]->SetXYPos(below, y);
			map[x + 2][y]->SetXYPos(x + 2, y);
		}
		else if (charmap[x + 2][y] == Icon::target) { // �I����I�S��
			char temp = charmap[x][y];

			charmap[x + 2][y] = charmap[below][y];
			charmap[below][y] = temp;
			charmap[x][y] = '-';

			player.AddX(1);

			// �洫�a�ϤW��Block����
			Block* tempBlock = map[x][y];
			map[x + 2][y] = map[below][y];
			map[below][y] = map[x][y];
			map[x][y] = new Block(x, y);

			map[x][y]->SetXYPos(x, y);
			map[below][y]->SetXYPos(below, y);
			map[x + 2][y]->SetXYPos(x + 2, y);
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
		showstate("�L�k����", Col_red);
		return; // �����禡
	}

	steps++;

	// �p�G���a����O�Ŧa�A�i�H���ʪ��a
	if (charmap[x][left] == Icon::none) {
		// �洫���a�M�Ŧa����m
		char temp = charmap[x][y];
		charmap[x][y] = charmap[x][left];
		charmap[x][left] = temp;

		// ��s�a�ϤW���a����m
		player.AddY(-1);

		// �洫�a�ϤW��Block����
		Block* tempBlock = map[x][y];
		map[x][y] = map[x][left];
		map[x][left] = tempBlock;

		// ��sBlock��m
		map[x][y]->SetXYPos(x, y);
		map[x][left]->SetXYPos(x, left);
	}
	// �p�G���a����O�c�l�A�ˬd�O�_���������Ŷ����ʽc�l
	else if (charmap[x][left] == Icon::box) {
		if (charmap[x][y - 2] == Icon::none) {
			char temp = charmap[x][y];
			charmap[x][y] = charmap[x][y - 2];
			charmap[x][y - 2] = charmap[x][left];
			charmap[x][left] = temp;

			player.AddY(-1);

			// �洫�a�ϤW��Block����
			Block* tempBlock = map[x][y];
			map[x][y] = map[x][y - 2];
			map[x][y - 2] = map[x][left];
			map[x][left] = tempBlock;

			map[x][y]->SetXYPos(x, y);
			map[x][left]->SetXYPos(x, left);
			map[x][y - 2]->SetXYPos(x, y - 2);
		}
		else if (charmap[x][y - 2] == Icon::target) { // �I����I�S��
			char temp = charmap[x][y];

			charmap[x][y - 2] = charmap[x][left];
			charmap[x][left] = temp;
			charmap[x][y] = '-';

			player.AddY(-1);

			// �洫�a�ϤW��Block����
			Block* tempBlock = map[x][y];
			map[x][y - 2] = map[x][left];
			map[x][left] = map[x][y];
			map[x][y] = new Block(x, y);

			map[x][y]->SetXYPos(x, y);
			map[x][left]->SetXYPos(x, left);
			map[x][y - 2]->SetXYPos(x, y - 2);
		}
	}
	else {
		cout << "�������p" << endl; // ��X�������p���T��
	}
}

void World::playerRight() {
	int x = player.x(); // ������a�� x �y��
	int y = player.y(); // ������a�� y �y��

	int right = y + 1; // �p�⪱�a�k�誺�y��

	// �ˬd���a�k��O�_�W�X�a����ɩάO�J���ê��
	if (right >= charmap[0].size() || charmap[x][right] == Icon::obstacle) {
		showstate("�L�k����", Col_red);
		return; // �����禡
	}

	steps++;

	// �p�G���a�k��O�Ŧa�A�i�H���ʪ��a
	if (charmap[x][right] == Icon::none) {
		// �洫���a�M�Ŧa����m
		char temp = charmap[x][y];
		charmap[x][y] = charmap[x][right];
		charmap[x][right] = temp;

		// ��s�a�ϤW���a����m
		player.AddY(1);

		// �洫�a�ϤW��Block����
		Block* tempBlock = map[x][y];
		map[x][y] = map[x][right];
		map[x][right] = tempBlock;

		// ��sBlock��m
		map[x][y]->SetXYPos(x, y);
		map[x][right]->SetXYPos(x, right);
	}
	// �p�G���a�k��O�c�l�A�ˬd�O�_���������Ŷ����ʽc�l
	else if (charmap[x][right] == Icon::box) {
		if (charmap[x][y + 2] == Icon::none) {
			char temp = charmap[x][y];
			charmap[x][y] = charmap[x][y + 2];
			charmap[x][y + 2] = charmap[x][right];
			charmap[x][right] = temp;

			player.AddY(1);

			// �洫�a�ϤW��Block����
			Block* tempBlock = map[x][y];
			map[x][y] = map[x][y + 2];
			map[x][y + 2] = map[x][right];
			map[x][right] = tempBlock;

			map[x][y]->SetXYPos(x, y);
			map[x][right]->SetXYPos(x, right);
			map[x][y + 2]->SetXYPos(x, y + 2);
		}
		else if (charmap[x][y + 2] == Icon::target) { // �I����I�S��
			char temp = charmap[x][y];

			charmap[x][y + 2] = charmap[x][right];
			charmap[x][right] = temp;
			charmap[x][y] = '-';

			player.AddY(1);

			// �洫�a�ϤW��Block����
			Block* tempBlock = map[x][y];
			map[x][y + 2] = map[x][right];
			map[x][right] = map[x][y];
			map[x][y] = new Block(x, y);

			map[x][y]->SetXYPos(x, y);
			map[x][right]->SetXYPos(x, right);
			map[x][y + 2]->SetXYPos(x, y + 2);
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
	Tools::gotoX(0);

	cout << " ======================================================= " << endl
		<< "| �ܮw�f                           �樫�B��: " << std::setw(5) << right << steps << " �B" << "   |" << endl
		<< "|                                                       |" << endl
		<< "|-------------------------------------------------------| " << endl
		<< "| ";
	Tools::SetColor(Col_blue); cout << "���a : 0"; Tools::SetColor(Col_RESET); cout << " , ";
	Tools::SetColor(Col_shit); cout << "�c�l : 1"; Tools::SetColor(Col_RESET); cout << " , ";
	Tools::SetColor(Col_red); cout << "���I : 2"; Tools::SetColor(Col_RESET); cout << " , ";
	Tools::SetColor(Col_gray); cout << "��� : /"; Tools::SetColor(Col_RESET); cout << "             |" << endl;
		//"| ���a : 0 , �c�l : 1 , ���I: 2 , ��� : /              |"
	cout << "|                                                       |" << endl;
	//Tools::SetColor(Col_red); cout << "!!!!���U Alt + Enter �i�J���ù� �H�K�X�{���~!!!!\n"; Tools::SetColor(Col_RESET);

	cout<< "| R : ���s�����d , Esc : ���}�C��                       |" << endl
		<< "| W : �W , S : �U , A : �� , D : �k                     |" << endl
		<< " ======================================================= " << endl
		;
}

void World::update() {
	mainfresh();
	showstate("                                                             ");
	drawmap();

}

void World::showstate(string state , Color color ) {

	//goto ���A��m �M��
	Tools::gotoY(UI_state_Y);
	cout << "                                                        ";

	Tools::gotoY(UI_state_Y);
	Tools::SetColor(color);
	cout << "�ثe���A: "  << state << endl;
	Tools::SetColor(Col_RESET);
}

bool World::checkwin() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (charmap[i][j] == '2') {
				return false;
				
			}
		}
	}
	return true;
}

bool World::checklose() {
	for (int i = 0; i < BoxVector.size(); i++) {
		int box_x = BoxVector[i]->x();
		int box_y = BoxVector[i]->y();

		if (charmap[box_x - 1][box_y] == '/' && charmap[box_x][box_y - 1] == '/') {
			return true;
		}
		else if (charmap[box_x - 1][box_y] == '/' && charmap[box_x][box_y + 1] == '/') {
			return true;
		}
		else if (charmap[box_x + 1][box_y] == '/' && charmap[box_x][box_y - 1] == '/') {
			return true;
		}
		else if (charmap[box_x + 1][box_y] == '/' && charmap[box_x][box_y + 1] == '/') {
			return true;
		}
		else
			return false;
	}
}

bool World::checkstate() {
	if (checklose() == true || checkwin() == true) {
		return true;
	}
	else {
		return false;
	}
}

void World::createMap() {
	//ofstream file();
}

void World::playBGM(const wstring& wfilename) {
	PlaySound(wfilename.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}

void World::stopBGM() {
	PlaySound(NULL, NULL, 0);
	if (soundThread.joinable()) {
		soundThread.join();
	}
}