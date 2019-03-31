#include "dice.h"
#include "monsterDescription.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Dice parseDice(string diceDescription) {
	unsigned long baseIndex = diceDescription.find_first_of('+');
	unsigned long diceIndex = diceDescription.find_first_of('d');
	int base = stoi(diceDescription.substr(0, baseIndex));
	int dice = stoi(diceDescription.substr(baseIndex + 1, diceIndex));
	int sides = stoi(diceDescription.substr(diceIndex + 1));
	return Dice(base, dice, sides);
}

int parseLine(string basic_string, MonsterDescription *descr) {
	unsigned long index = basic_string.find_first_of(' ');
	if (index < 100) {
		string keyword = basic_string.substr(0, index);
		string data = basic_string.substr(index);

		if (keyword.compare("NAME") == 0) {
			descr->name = (char *) data.c_str();
		} else if (keyword.compare("SYMB") == 0) {
			descr->symbol = (char) data.at(0);
		} else if (keyword.compare("COLOR") == 0) {
			// TODO parse down to ints
		} else if (keyword.compare("DAM") == 0) {
			descr->damage = parseDice(data);
//			cout << descr->damage.base << '+' << descr->damage.dice << 'd' << descr->damage.sides << endl;
		} else if (keyword.compare("SPEED") == 0) {
			descr->speed = parseDice(data);
		} else if (keyword.compare("ABIL") == 0) {
			// TODO parse further
			descr->abilities[0] = (char *) data.c_str();
		} else if (keyword.compare("RRTY") == 0) {
			descr->rarity = stoi(data);
		} else if (keyword.compare("HP") == 0) {
			descr->HP = parseDice(data);
		} else {
			cout << "Invalid" << keyword << endl;
			return -1;
		}
	}

	return 1;
}

int readFile() {
	string line;
	char filePath[100] = "";
	strcat(filePath, getenv("HOME"));
	strcat(filePath, "/.rlg327/monster_desc_easy.txt");

	ifstream myfile(filePath);
	getline(myfile, line);

	MonsterDescription *md = new MonsterDescription();
	md->color[0] = 1;

	if (myfile.is_open() && line.compare("RLG327 MONSTER DESCRIPTION 1") == 0) {
		while (getline(myfile, line)) {
			getline(myfile, line); //Eat empty line
			if (line.compare("BEGIN MONSTER") != 0) {
				cout << "Doesn't start with BEGIN MONSTER" << endl;
				return -1;
			}

			while (getline(myfile, line)) {
				if (line.compare("END") == 0) {
					return 1;
				}

				if (line.compare("DESC") == 0) {
					getline(myfile, line);
					md->description = (char *) line.c_str();
					cout << "Description: " << md->description << endl;
				} else if (parseLine(line, md) == 1) {

				};

			}
		}
		myfile.close();
	} else cout << "File either does not exist or is incorrectly formatted" << endl;
	return 1;
}