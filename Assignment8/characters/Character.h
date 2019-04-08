#ifndef CS327_MONSTER_H
#define CS327_MONSTER_H

#include <stdint.h>
#include "../descriptions/dice.h"

class Character {
public:
	char name[100];
	int color[8];
	uint8_t x;
	uint8_t y;
	uint8_t speed;
	char symbol;
};

class Player : public Character {

};

class Monster : public Character {
public:
	char description[100][78];
	int speed;
	int HP;
	Dice damage;
	int rarity;
	uint8_t characteristics;
	uint8_t knownPlayerX;
	uint8_t knownPlayerY;
};

Monster *generateMonsterCharacter();

Player *generatePlayerCharacter();

void placeMonsters(int numMonsters);

void placePlayer();

void placePlayerWithCoords(int x, int y);

void initCharacterMap();

void initTeleportMap();

void initRememberedMap();

void playGame();

#endif //CS327_MONSTER_H
