#ifndef CS327_MONSTER_H
#define CS327_MONSTER_H

#include <stdint.h>
#include <stdbool.h>

struct monster {
	uint8_t characteristics;
};

struct player {

};

struct character {
	struct monster *npm;
	struct player *pc;
	uint8_t x;
	uint8_t y;
	uint8_t speed;
	char symbol;
};

struct character* generateMonsterCharacter();
struct character* generatePlayerCharacter();
void placeMonsters(int numMonsters);
void placePlayer();
void placePlayerWithCoords(int x, int y);

#endif //CS327_MONSTER_H
