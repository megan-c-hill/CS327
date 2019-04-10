#ifndef CS327_ITEMDESCRIPTION_H
#define CS327_ITEMDESCRIPTION_H

#include "dice.h"
#include "../characters/Object.h"

class ItemDescription {
public:
	char name[100];
	char description[100][78];
	char type[19][11];
	int color;
	Dice hit;
	Dice damage;
	Dice dodge;
	Dice def;
	Dice weight;
	Dice speed;
	Dice attr;
	Dice value;
	char art[6];
	int rarity;
	bool assignedFields[14];
	bool fieldDoubleAssigned;

	ItemDescription();
	void print();
	Object* createObject();
};

int readObjectFile();


#endif
