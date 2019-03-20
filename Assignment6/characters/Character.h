#ifndef CS327_MONSTER_H
#define CS327_MONSTER_H

#include <stdint.h>
#include <stdbool.h>


class Character {
public:
	uint8_t x;
	uint8_t y;
	uint8_t speed;
	char symbol;
};

class Player : public Character {

};

class Monster : public Character {
public:
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

void playGame();

#endif //CS327_MONSTER_H
