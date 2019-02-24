#ifndef CS327_MONSTER_H
#define CS327_MONSTER_H

#include <stdint.h>
#include <stdbool.h>

typedef struct monster {
	uint8_t characteristics;
} Monster;

typedef struct player {

} Player;

typedef struct character {
	struct monster *npm;
	struct player *pc;
	uint8_t x;
	uint8_t y;
	uint8_t speed;
	char symbol;
} Character;

Character* generateMonsterCharacter();
Character* generatePlayerCharacter();
void placeMonsters(int numMonsters);
void placePlayer();
void placePlayerWithCoords(int x, int y);
void initCharacterMap();
void move();

#endif //CS327_MONSTER_H
