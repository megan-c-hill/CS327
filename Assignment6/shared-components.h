#ifndef CS327_SHARED_COMPONENTS_H
#define CS327_SHARED_COMPONENTS_H

#include <stdint.h>
#include "characters/Character.h"
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

extern struct dungeonPosition dungeon[TOTAL_HEIGHT][TOTAL_WIDTH];
extern DistancePosition nonTunnelDistance[TOTAL_HEIGHT][TOTAL_WIDTH];
extern DistancePosition tunnelDistance[TOTAL_HEIGHT][TOTAL_WIDTH];
extern Character *characterMap[TOTAL_HEIGHT][TOTAL_WIDTH];
extern char teleportDungeon[TOTAL_HEIGHT][TOTAL_WIDTH];
extern char rememberedMap[TOTAL_HEIGHT][TOTAL_WIDTH];
extern struct room *rooms;
extern struct position *upStairs;
extern struct position *downStairs;
extern CharacterHeap *playerQueue;
extern Character *playerCharacter;
extern bool fogOfWarActivated;

void printDungeon(Player *player);

void printFullDungeon();

void drawRoom(int roomNumber);

#endif //CS327_SHARED_COMPONENTS_H
