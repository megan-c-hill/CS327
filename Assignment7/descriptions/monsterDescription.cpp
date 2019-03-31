#include "dice.h"
#include "monsterDescription.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Dice getDice(char *diceDescription) {
	//TODO make this right
	return Dice(1, 1, 1);
}


int readFile() {
	string line;
	char filePath[100] = "";
	strcat(filePath, getenv("HOME"));
	strcat(filePath, "/.rlg327/monster_desc_easy.txt");
	string expectedFirstLine = "RLG327 MONSTER DESCRIPTION 1";
	string beginMonster = "BEGIN MONSTER";
	string endMonster = "END";

	ifstream myfile(filePath);
	getline(myfile, line);

	char* name;
	char description[78];
	int color[8];
	Dice speed;
	char* abilities[10];
	Dice HP;
	Dice damage;
	char symbol;
	int rarity;

	if (myfile.is_open() && line.compare(expectedFirstLine) == 0) {
		while (getline(myfile, line)) {
			getline(myfile, line); //Eat empty line
			if (line.compare(beginMonster) != 0) {
				cout << "Doesn't start with BEGIN MONSTER" << endl;
				return -1;
			}

			while(getline(myfile, line)) {
				if(line.compare(endMonster) == 0) {
					return 1;
				}

				cout << line << endl;
			}
		}
		myfile.close();
	} else cout << "File either does not exist or is incorrectly formatted" << endl;
	return 1;
}