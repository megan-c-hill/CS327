#ifndef CS327_MONSTER_H
#define CS327_MONSTER_H

#include <stdint.h>
#include <stdbool.h>

class Monster {
public:
	uint8_t characteristics;
	uint8_t knownPlayerX;
	uint8_t knownPlayerY;
};

class Player {

};

class Character {
public:
	Monster *npm;
	Player *pc;
	uint8_t x;
	uint8_t y;
	uint8_t speed;
	char symbol;
};

Character *generateMonsterCharacter();

Character *generatePlayerCharacter();

void placeMonsters(int numMonsters);

void placePlayer();

void placePlayerWithCoords(int x, int y);

void initCharacterMap();

void playGame();

#endif //CS327_MONSTER_H
