#ifndef CS327_CHARACTER_H
#define CS327_CHARACTER_H

#include <stdint.h>
#include "../descriptions/dice.h"
#include "./Object.h"
#include <iostream>

class Character {
public:
	char name[100];
	char description[100][78];
	char symbol;
	int color;
	int HP;
	Dice damage;
	uint8_t speed;
	uint8_t x;
	uint8_t y;
	void displayCharacter();
};

void initMaps();

void initRememberedMap();

void moveToSpot(Character *character, int newX, int newY);

int displayMonsterList(int offset, Character *player);

void tunnel(Character *character, int newX, int newY);

void playGame();

//void useMap(Character *character, DistancePosition distanceMap[TOTAL_HEIGHT][TOTAL_WIDTH]);

#endif //CS327_CHARACTER_H
