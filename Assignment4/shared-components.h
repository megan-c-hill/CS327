#ifndef CS327_SHARED_COMPONENTS_H
#define CS327_SHARED_COMPONENTS_H

#include <stdint.h>
#include "characters/monster.h"
#include "characters/characterHeap.h"

#define TOTAL_HEIGHT 21
#define TOTAL_WIDTH 80

struct dungeonPosition {
	char symbol;
	uint8_t hardness;
};

struct room {
	uint8_t x;
	uint8_t y;
	uint8_t width;
	uint8_t height;
};

struct position {
	uint8_t x;
	uint8_t y;
};

typedef struct distancePosition {
	char symbol;
	int distance;
} DistancePosition;

struct dungeonPosition dungeon[TOTAL_HEIGHT][TOTAL_WIDTH];
DistancePosition nonTunnelDistance[TOTAL_HEIGHT][TOTAL_WIDTH];
DistancePosition tunnelDistance[TOTAL_HEIGHT][TOTAL_WIDTH];
Character *characterMap[TOTAL_HEIGHT][TOTAL_WIDTH];
struct room *rooms;
struct position *upStairs;
struct position *downStairs;
CharacterHeap* playerQueue;
Character* playerCharacter;

void printDungeon();
void drawRoom(int roomNumber);

#endif //CS327_SHARED_COMPONENTS_H
