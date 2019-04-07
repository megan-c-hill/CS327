#ifndef CS327_SHARED_COMPONENTS_H
#define CS327_SHARED_COMPONENTS_H

#include <stdint.h>
#include "characters/Character.h"
#include "characters/characterHeap.h"
#include "descriptions/monsterDescription.h"
#include "descriptions/itemDescription.h"
#include <vector>

#define TOTAL_HEIGHT 21
#define TOTAL_WIDTH 80

using namespace std;

class DungeonPosition {
public:
	char symbol;
	uint8_t hardness;
};

class Room {
public:
	uint8_t x;
	uint8_t y;
	uint8_t width;
	uint8_t height;
};

class Position {
public:
	uint8_t x;
	uint8_t y;
};

class DistancePosition {
public:
	char symbol;
	int distance;
};

extern DungeonPosition dungeon[TOTAL_HEIGHT][TOTAL_WIDTH];
extern DistancePosition nonTunnelDistance[TOTAL_HEIGHT][TOTAL_WIDTH];
extern DistancePosition tunnelDistance[TOTAL_HEIGHT][TOTAL_WIDTH];
extern Character *characterMap[TOTAL_HEIGHT][TOTAL_WIDTH];
extern char teleportDungeon[TOTAL_HEIGHT][TOTAL_WIDTH];
extern char rememberedMap[TOTAL_HEIGHT][TOTAL_WIDTH];
extern vector<MonsterDescription> monsters;
extern vector<ItemDescription> items;
extern Room *rooms;
extern Position *upStairs;
extern Position *downStairs;
extern CharacterHeap *playerQueue;
extern Character *playerCharacter;
extern bool fogOfWarActivated;

void printDungeon(Player *player);

void printFullDungeon();

void drawRoom(int roomNumber);

#endif //CS327_SHARED_COMPONENTS_H
