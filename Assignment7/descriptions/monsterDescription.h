#ifndef CS327_MONSTERDESCRIPTION_H
#define CS327_MONSTERDESCRIPTION_H

#include "dice.h"

class MonsterDescription {
public:
	char name[100];
	char description[100][77];
	int color[8];
	Dice speed;
	char abilities[10][7];
	Dice HP;
	Dice damage;
	char symbol;
	int rarity;

	MonsterDescription();
	void print();
};

int readFile();


#endif
