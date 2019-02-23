#ifndef CS327_SHARED_COMPONENTS_H
#define CS327_SHARED_COMPONENTS_H

#include <stdint.h>
#include "monster.h"

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

struct distancePosition {
	char symbol;
	int distance;
};

struct dungeonPosition dungeon[TOTAL_HEIGHT][TOTAL_WIDTH];
struct distancePosition nonTunnelDistance[TOTAL_HEIGHT][TOTAL_WIDTH];
struct distancePosition tunnelDistance[TOTAL_HEIGHT][TOTAL_WIDTH];
Character *characterMap[TOTAL_HEIGHT][TOTAL_WIDTH];
struct room *rooms;
struct position *upStairs;
struct position *downStairs;
uint8_t playerPosition[2];

void printDungeon();
void drawRoom(int roomNumber);

#endif //CS327_SHARED_COMPONENTS_H
