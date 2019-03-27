#ifndef CS327_MONSTERDESCRIPTION_H
#define CS327_MONSTERDESCRIPTION_H

#include "dice.h"

class MonsterDescription {
public:
	char* name;
	char* description;
	char * color;
	Dice speed;
	char* abailities;
	Dice HP;
	Dice damage;
	char symbol;
	int rarity;
};

void readFile();


#endif
