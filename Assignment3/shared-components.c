#include <stdint.h>
#include <stdio.h>

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

struct dungeonPosition dungeon[TOTAL_HEIGHT][TOTAL_WIDTH];
struct room *rooms;
struct position *upStairs;
struct position *downStairs;
uint8_t playerPosition[2];
uint16_t numberOfRooms = 8;
uint16_t numberOfUpstairs = 1;
uint16_t numberOfDownstairs = 1;