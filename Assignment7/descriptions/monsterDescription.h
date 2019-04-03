#ifndef CS327_MONSTERDESCRIPTION_H
#define CS327_MONSTERDESCRIPTION_H

#include "dice.h"

class MonsterDescription {
public:
	char name[100];
	char description[100][78];
	int color[8];
	Dice speed;
	char abilities[10][8];
	Dice HP;
	Dice damage;
	char symbol;
	int rarity;
	bool assignedFields[9];
	bool fieldDoubleAssigned;

	MonsterDescription();
	void print();
};

int readFile();


#endif
