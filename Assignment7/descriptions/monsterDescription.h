#ifndef CS327_MONSTERDESCRIPTION_H
#define CS327_MONSTERDESCRIPTION_H

#include "dice.h"

class MonsterDescription {
public:
	char* name;
	char* description;
	int color[8];
	Dice speed;
	char* abilities[10];
	Dice HP;
	Dice damage;
	char symbol;
	int rarity;
};

int readFile();


#endif
