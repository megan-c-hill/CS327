#include "dice.h"
#include "itemDescription.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <unordered_map>

using namespace std;

enum colors {
	RED, GREEN, BLUE, CYAN, YELLOW, MAGENTA, WHITE, BLACK
};

static unordered_map<string, enum colors> const colorMap = {
		{"RED",     RED},
		{"GREEN",   GREEN},
		{"BLUE",    BLUE},
		{"CYAN",    CYAN},
		{"YELLOW",  YELLOW},
		{"MAGENTA", MAGENTA},
		{"WHITE",   WHITE},
		{"BLACK",   BLACK}
};

Dice parseDice2(string diceDescription) {
	unsigned long baseIndex = diceDescription.find_first_of('+');
	unsigned long diceIndex = diceDescription.find_first_of('d');
	int base = stoi(diceDescription.substr(0, baseIndex));
	int dice = stoi(diceDescription.substr(baseIndex + 1, diceIndex));
	int sides = stoi(diceDescription.substr(diceIndex + 1));
	return Dice(base, dice, sides);
}

void parseLine(string basic_string, ItemDescription *descr) {
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
		} else if (keyword.compare("TYPE") == 0) {
			if (descr->assignedFields[2]) {
				descr->fieldDoubleAssigned = true;
			}
			descr->assignedFields[2] = true;
			unsigned long nextIndex = data.find_first_of(' ');
			int count = 0;
			while (nextIndex < 100 && count < 9) {
				strcpy(descr->type[count], data.substr(0, nextIndex).c_str());
				count++;
				data = data.substr(nextIndex + 1);
				nextIndex = data.find_first_of(' ');
			}
			strcpy(descr->type[count], data.substr(0, nextIndex).c_str());
		}else if (keyword.compare("COLOR") == 0) {
			if (descr->assignedFields[3]) {
				descr->fieldDoubleAssigned = true;
			}
			descr->assignedFields[3] = true;
			enum colors c = colorMap.at(data);
			descr->color = c;
		} else if (keyword.compare("HIT") == 0) {
			if (descr->assignedFields[4]) {
				descr->fieldDoubleAssigned = true;
			}
			descr->assignedFields[4] = true;
			descr->hit = parseDice2(data);
		} else if (keyword.compare("DAM") == 0) {
			if (descr->assignedFields[5]) {
				descr->fieldDoubleAssigned = true;
			}
			descr->assignedFields[5] = true;
			descr->damage = parseDice2(data);
		} else if (keyword.compare("DODGE") == 0) {
			if (descr->assignedFields[6]) {
				descr->fieldDoubleAssigned = true;
			}
			descr->assignedFields[6] = true;
			descr->dodge = parseDice2(data);
		}else if (keyword.compare("DEF") == 0) {
			if (descr->assignedFields[7]) {
				descr->fieldDoubleAssigned = true;
			}
			descr->assignedFields[7] = true;
			descr->def = parseDice2(data);
		}else if (keyword.compare("WEIGHT") == 0) {
			if (descr->assignedFields[8]) {
				descr->fieldDoubleAssigned = true;
			}
			descr->assignedFields[8] = true;
			descr->weight = parseDice2(data);
		} else if (keyword.compare("SPEED") == 0) {
			if (descr->assignedFields[9]) {
				descr->fieldDoubleAssigned = true;
			}
			descr->assignedFields[9] = true;
			descr->speed = parseDice2(data);
		}else if (keyword.compare("ATTR") == 0) {
			if (descr->assignedFields[10]) {
				descr->fieldDoubleAssigned = true;
			}
			descr->assignedFields[10] = true;
			descr->attr = parseDice2(data);
		}else if (keyword.compare("VAL") == 0) {
			if (descr->assignedFields[11]) {
				descr->fieldDoubleAssigned = true;
			}
			descr->assignedFields[11] = true;
			descr->value = parseDice2(data);
		} else if (keyword.compare("ART") == 0) {
			if (descr->assignedFields[12]) {
				descr->fieldDoubleAssigned = true;
			}
			descr->assignedFields[12] = true;
			strcpy(descr->art, data.c_str());
		} else if (keyword.compare("RRTY") == 0) {
			if (descr->assignedFields[13]) {
				descr->fieldDoubleAssigned = true;
			}
			descr->assignedFields[13] = true;
			descr->rarity = stoi(data);
		} else {
			cout << "Invalid Keyword: " << keyword << endl;
		}
	}
}

int readObjectFile() {
	string line;
	char filePath[100] = "";
	strcat(filePath, getenv("HOME"));
	strcat(filePath, "/.rlg327/object_desc.txt");
  cout << filePath << endl;

	ifstream myfile(filePath);
	getline(myfile, line);

	ItemDescription *md = new ItemDescription();

	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			getline(myfile, line); //Eat empty line
			if (line.compare("BEGIN OBJECT") != 0) {
				cout << "Doesn't start with BEGIN OBJECT" << endl;
				return -1;
			}

			while (getline(myfile, line)) {
				if (line.compare("END") == 0) {
					(*md).print();
				}

				if (line.compare("DESC") == 0) {
					if (md->assignedFields[1]) {
						md->fieldDoubleAssigned = true;
					}
					md->assignedFields[1] = true;
					int count = 0;
					while (getline(myfile, line) && line.compare(".") != 0) {
						strcpy(md->description[count], line.c_str());
						count++;
					}
				} else if (line.compare("BEGIN OBJECT") == 0) {
					md = new ItemDescription();
				} else {
					parseLine(line, md);


				};
			}
		}
		myfile.close();
	} else cout << "File either does not exist or is incorrectly formatted" << endl;

	return 1;
}

ItemDescription::ItemDescription() {
	for (int i = 0; i < 100; i++) {
		strcpy(description[i], "NONE");
	}
	for (int i = 0; i < 19; i++) {
		strcpy(type[i], "NONE");
	}
	for (int i = 0; i < 14; i++) {
		assignedFields[i] = false;
	}
	fieldDoubleAssigned = false;
}

void ItemDescription::print() {
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
		cout << "TYPE: ";
		for (int i = 0; i < 19 && strcmp(type[i], "NONE") != 0; i++) {
			cout << type[i];
		}
		cout << endl;
		cout << "COLOR: " << color << endl;
		cout << "HIT: " << hit.print() << endl;
		cout << "DAM: " << damage.print() << endl;
		cout << "DODGE: " << dodge.print() << endl;
		cout << "DEFENSE: " << def.print() << endl;
		cout << "WEIGHT: " << weight.print() << endl;
		cout << "SPEED: " << speed.print() << endl;
		cout << "ATTRIBUTE: " << attr.print() << endl;
		cout << "VALUE: " << value.print() << endl;
		cout << "ARTIFACT: " << art << endl;
		cout << "RARITY: " << rarity << endl;
		cout << endl;
	}
}
