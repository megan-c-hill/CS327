#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "shared-components.c"

#define MAX_ROOMS 8

//ENHANCEMENT Generate Random Number of stairs
//ENHANCEMENT Generate random number of rooms
//ENHANCEMENT make corridors more random and have less of them

bool isLegalPlacement(int x, int y, int width, int height) {
	int i, j;
	if (y + height + 1 >= TOTAL_HEIGHT) return false;
	if (x + width + 1 >= TOTAL_WIDTH) return false;

	for (i = y - 1; i < y + height + 1; i++) {
		for (j = x - 1; j < x + width + 1; j++) {
			if (dungeon[i][j].symbol != ' ') {
				return false;
			}
		}
	}
	return true;
}

void placeStairsAndPlayer() {
	uint8_t x, y;
	int i = 0;
	while (i < 3) {
		x = rand() % 78 + 1;
		y = rand() % 19 + 1;
		if (dungeon[y][x].hardness == 0) {
			if (i == 0) {
				numberOfDownstairs = 1;
				downStairs[0].x = x;
				downStairs[0].y = y;
				dungeon[y][x].symbol = '>';
			} else if (i == 1) {
				numberOfUpstairs = 1;
				upStairs[0].x = x;
				upStairs[0].y = y;
				dungeon[y][x].symbol = '<';
			} else {
				playerPosition[0] = x;
				playerPosition[1] = y;
				dungeon[y][x].symbol = '@';
			}
			i++;
		}
	}
}

void connectRooms() {
	for (int room = 0; room < MAX_ROOMS - 1; room++) {
		int x0 = rooms[room].x;
		int x1 = rooms[room + 1].x;
		int y0 = rooms[room].y;
		int y1 = rooms[room + 1].y;

		int x = x0;
		int y = y0;
		int xDirection = (x1 - x0) / abs(x1 - x0);
		int yDirection = (y1 - y0) / abs(y1 - y0);
		int count;

		for (count = 0; count < abs(x1 - x0); count++) {
			if (dungeon[y0][x].symbol == ' ') {
				dungeon[y0][x].symbol = '#';
				dungeon[y0][x].hardness = 0;
			}
			x = x + xDirection;
		}

		for (count = 0; count < abs(y1 - y0); count++) {
			if (dungeon[y][x].symbol == ' ') {
				dungeon[y][x].symbol = '#';
				dungeon[y][x].hardness = 0;
			}
			y = y + yDirection;
		}

	}
}

void placeRoom(int roomNumber) {
	uint8_t x = rand() % (TOTAL_WIDTH - 5) + 1;
	uint8_t y = rand() % (TOTAL_HEIGHT - 4) + 1;
	uint8_t width = rand() % 8 + 4;
	uint8_t height = rand() % 6 + 3;
	numberOfRooms = roomNumber + 1;

	if (isLegalPlacement(x, y, width, height)) {
		rooms[roomNumber].x = x;
		rooms[roomNumber].y = y;
		rooms[roomNumber].width = width;
		rooms[roomNumber].height = height;
		drawRoom(roomNumber);
	} else {
		placeRoom(roomNumber);
	}
}

void generateRandomFloor() {
	int seed = time(NULL);
	printf("Seed: %d\n", seed);
	srand(seed);

	int i, j;
	for (i = 0; i < TOTAL_HEIGHT; i++) {
		for (j = 0; j < TOTAL_WIDTH; j++) {
			char value = ' ';
			uint8_t hardness = rand() % 255 + 1;
			if (i == 0 || i == TOTAL_HEIGHT - 1) {
				value = '-';
				hardness = 255;
			} else if (j == 0 || j == TOTAL_WIDTH - 1) {
				value = '|';
				hardness = 255;
			}
			dungeon[i][j].symbol = value;
			dungeon[i][j].hardness = hardness;
		}
	}

	rooms = malloc(sizeof(struct room) * numberOfRooms);
	for (i = 0; i < MAX_ROOMS; i++) {
		placeRoom(i);
	}
	upStairs = malloc(sizeof(struct position) * numberOfUpstairs);
	downStairs = malloc(sizeof(struct position) * numberOfDownstairs);
	connectRooms();
	placeStairsAndPlayer();
}