#include "dice.h"
#include "monsterDescription.h"
#include "../shared-components.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <android/asset_manager.h>
#include "monsterDescriptionFile.h"
//#include <ncurses.h>

using namespace std;

static unordered_map<string, int> const colorMap = {
		{"WHITE", 	0},
		{"RED",     1},
		{"GREEN",   2},
		{"BLUE",    3},
		{"CYAN",    4},
		{"YELLOW",  5},
		{"MAGENTA", 6},
		{"BLACK",   7}
};

Dice parseDice(string diceDescription) {
	unsigned long baseIndex = diceDescription.find_first_of('+');
	unsigned long diceIndex = diceDescription.find_first_of('d');
	int base = stoi(diceDescription.substr(0, baseIndex));
	int dice = stoi(diceDescription.substr(baseIndex + 1, diceIndex));
	int sides = stoi(diceDescription.substr(diceIndex + 1));
	return Dice(base, dice, sides);
}

void parseLine(string basic_string, MonsterDescription *descr) {
	unsigned long index = basic_string.find_first_of(' ');
	if (index < 100) { //If there's not another space index gives really long garbage, so 100 checks that
		string keyword = basic_string.substr(0, index);
		string data = basic_string.substr(index + 1);

		if (keyword.compare("NAME") == 0) {
			if (descr->assignedFields[0]) {
				descr->fieldDoubleAssigned = true;
			}
			descr->assignedFields[0] = true;
			strcpy(descr->name, data.c_str());
		} else if (keyword.compare("SYMB") == 0) {
			if (descr->assignedFields[7]) {
				descr->fieldDoubleAssigned = true;
			}
			descr->assignedFields[7] = true;
			descr->symbol = (char) data.at(0);
		} else if (keyword.compare("COLOR") == 0) {
			if (descr->assignedFields[2]) {
				descr->fieldDoubleAssigned = true;
			}
			descr->assignedFields[2] = true;
			unsigned long nextIndex = data.find_first_of(' ');
			int count = 0;
			while (nextIndex < 100 && count < 8) {
				int c = colorMap.at(data.substr(0, nextIndex));
				descr->color[count] = c;
				count++;
				data = data.substr(nextIndex + 1);
				nextIndex = data.find_first_of(' ');
			}
			int c = colorMap.at(data.substr(0, nextIndex));
			descr->color[count] = c;
		} else if (keyword.compare("DAM") == 0) {
			if (descr->assignedFields[6]) {
				descr->fieldDoubleAssigned = true;
			}
			descr->assignedFields[6] = true;
			descr->damage = parseDice(data);
		} else if (keyword.compare("SPEED") == 0) {
			if (descr->assignedFields[3]) {
				descr->fieldDoubleAssigned = true;
			}
			descr->assignedFields[3] = true;
			descr->speed = parseDice(data);
		} else if (keyword.compare("ABIL") == 0) {
			if (descr->assignedFields[4]) {
				descr->fieldDoubleAssigned = true;
			}
			descr->assignedFields[4] = true;
			unsigned long nextIndex = data.find_first_of(' ');
			int count = 0;
			while (nextIndex < 100 && count < 9) {
				strcpy(descr->abilities[count], data.substr(0, nextIndex).c_str());
				count++;
				data = data.substr(nextIndex + 1);
				nextIndex = data.find_first_of(' ');
			}
			strcpy(descr->abilities[count], data.substr(0, nextIndex).c_str());
		} else if (keyword.compare("RRTY") == 0) {
			if (descr->assignedFields[8]) {
				descr->fieldDoubleAssigned = true;
			}
			descr->assignedFields[8] = true;
			descr->rarity = stoi(data);
		} else if (keyword.compare("HP") == 0) {
			if (descr->assignedFields[5]) {
				descr->fieldDoubleAssigned = true;
			}
			descr->assignedFields[5] = true;
			descr->HP = parseDice(data);
		} else {
			cout << "Invalid Keyword: " << keyword << endl;
		}
	}
}

int readMonsterFile() {
	string line;
	initMonsterDescriptionFile();

	MonsterDescription *md = new MonsterDescription();
	md->color[0] = 1;
	int i = 2;

		while (i < 350) { //Hardcoded for length
			line = monsterDescriptionFile[i];
			i++;
			if (line.compare("BEGIN MONSTER") != 0) {
				cout << "Doesn't start with BEGIN MONSTER" << endl;
				return -1;
			}

			while (i < 350) {
				if (line.compare("END") == 0) {
					monsters.push_back(*md);
				}

				if (line.compare("DESC") == 0) {
					if (md->assignedFields[1]) {
						md->fieldDoubleAssigned = true;
					}
					md->assignedFields[1] = true;
					int count = 0;
					while (i < 350 && strcmp(monsterDescriptionFile[i], ".") != 0) {
					    line = monsterDescriptionFile[i];
					    i++;
						strcpy(md->description[count], line.c_str());
						count++;
					}
				} else if (line.compare("BEGIN MONSTER") == 0) {
					md = new MonsterDescription();
				} else {
					parseLine(line, md);
				};
                line = monsterDescriptionFile[i];
                i++;
			}
		}

	return 1;
}

MonsterDescription::MonsterDescription() {
	for (int i = 0; i < 100; i++) {
		strcpy(description[i], "NONE");
	}
	for (int i = 0; i < 8; i++) {
		color[i] = 9;
	}
	for (int i = 0; i < 9; i++) {
		strcpy(abilities[i], "NONE");
		assignedFields[i] = false;
	}
	fieldDoubleAssigned = false;
}

void MonsterDescription::print() {
	bool allFieldsAssigned = true;
	for (int i = 0; i < 9; i++) {
		if(!assignedFields[i]) {
			allFieldsAssigned = false;
		}
	}
	if(allFieldsAssigned && !fieldDoubleAssigned) {
		cout << "NAME: " << name << endl;
		cout << "DESCR: " << endl;
		for (int i = 0; i < 100 && strcmp(description[i], "NONE") != 0; i++) {
			cout << description[i] << endl;
		}
		cout << "COLOR: ";
		for (int i = 0; i < 8 && color[i] != 9; i++) {
			cout << color[i] << " ";
		}
		cout << endl;
		cout << "SPEED: " << speed.print() << endl;
		cout << "ABIL: ";
		for (int i = 0; i < 8 && strcmp(abilities[i], "NONE") != 0; i++) {
			cout << abilities[i] << " ";
		}
		cout << endl;
		cout << "HP: " << HP.print() << endl;
		cout << "DAM: " << damage.print() << endl;
		cout << "SYMB: " << symbol << endl;
		cout << "RRTY: " << to_string(rarity) << endl << endl;
	}
}
