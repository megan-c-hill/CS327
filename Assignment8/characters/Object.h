#ifndef CS327_OBJECT_H
#define CS327_OBJECT_H

#include "../descriptions/dice.h"

class Object {
public:
	char name[100];
	char description[100][78];
	char type[19][11];
	int color;
	int hit;
	Dice damage;
	int dodge;
	int def;
	int weight;
	int speed;
	int attr;
	int value;
	char art[6];
	int rarity;
	int x;
	int y;
};

Object* generateObject();

void placeItems(int numItems);

#endif //CS327_OBJECT_H
