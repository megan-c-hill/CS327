#include "dice.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Dice getDice(char *diceDescription) {
	//TODO make this right
	return Dice(1, 1, 1);
}

void readFile() {
	string line;
	char filePath[100] = "";
	strcat(filePath, getenv("HOME"));
	strcat(filePath, "/.rlg327/monster_desc_easy.txt");
	string expectedFirstLine = "RLG327 MONSTER DESCRIPTION 1";

	ifstream myfile(filePath);
	getline(myfile, line);
	if (myfile.is_open() && line.compare(expectedFirstLine) == 0) {
			while (getline(myfile, line)) {
				cout << line << endl;
			}
		myfile.close();
	} else cout << "File either does not exist or is incorrectly formatted" << endl;
}