#ifndef CS327_CHARACTER_H
#define CS327_CHARACTER_H

#include <stdint.h>
#include "../descriptions/dice.h"
#include "./Object.h"
#include <iostream>

class Character {
public:
	char name[100];
	int color;
	int HP;
	Dice damage;
	uint8_t x;
	uint8_t y;
	uint8_t speed;
	char symbol;
};

class Player : public Character {
public:
	Object* equipment[12];
	Object* inventory[10];
};

Player *generatePlayerCharacter();

void placePlayer();

void placePlayerWithCoords(int x, int y);

void initMaps();

void initRememberedMap();

void moveToSpot(Character *character, int newX, int newY);

void tunnel(Character *character, int newX, int newY);

void playGame();

//void useMap(Character *character, DistancePosition distanceMap[TOTAL_HEIGHT][TOTAL_WIDTH]);

#endif //CS327_CHARACTER_H
