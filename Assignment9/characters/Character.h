#ifndef CS327_CHARACTER_H
#define CS327_CHARACTER_H

#include <stdint.h>
#include "../descriptions/dice.h"

class Character {
public:
	char name[100];
	int color;
	uint8_t x;
	uint8_t y;
	uint8_t speed;
	char symbol;
};

class Player : public Character {

};

Player *generatePlayerCharacter();

void placePlayer();

void placePlayerWithCoords(int x, int y);

void initCharacterMap();

void initTeleportMap();

void initRememberedMap();

void moveToSpot(Character *character, int newX, int newY);

void tunnel(Character *character, int newX, int newY);

void playGame();

//void useMap(Character *character, DistancePosition distanceMap[TOTAL_HEIGHT][TOTAL_WIDTH]);

#endif //CS327_CHARACTER_H
