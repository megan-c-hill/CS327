#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "shared-components.h"
#include <string.h>
#include "shared-components.h"
#include "characters/monster.h"

#ifdef __APPLE__

#include <libkern/OSByteOrder.h>

#define be16toh(x) OSSwapBigToHostInt16(x)
#define be32toh(x) OSSwapBigToHostInt32(x)
#define htobe16(x) OSSwapHostToBigInt16(x)
#define htobe32(x) OSSwapHostToBigInt32(x)
#else
#include <endian.h>
#endif

#define MAX_ROOMS 8

//ENHANCEMENT Generate Random Number of stairs
//ENHANCEMENT Generate random number of rooms
//ENHANCEMENT make corridors more random and have less of them
//ENHANCEMENT Validation version, number of rooms, presence of stairs?
//TECH DEBT Don't allow user to enter more monsters than my algorithm lets them place
//TECH DEBT Give user helpful message if they don't give switches and command line arguments in the order I want

uint16_t numberOfRooms = 8;
uint16_t numberOfUpstairs = 1;
uint16_t numberOfDownstairs = 1;


FILE *openFile(char *fileName, char *openType) {
	char filePath[100] = "";
	strcat(filePath, getenv("HOME"));
	strcat(filePath, "/.rlg327/");
	strcat(filePath, fileName);

	FILE *file = fopen(filePath, openType);
	return file;
}


void readBasicInfo(FILE *file) {
	char marker[13];
	uint32_t version;
	uint32_t size;
	uint8_t hardness[TOTAL_HEIGHT][TOTAL_WIDTH];

	fread(marker, sizeof(char), 12, file);

	if (strcmp(marker, "RLG327-S2019") != 0) {
		fprintf(stderr, "The marker does not match the expected value\n");
		exit(-1);
	}

	fread(&version, 4, 1, file);
	version = be32toh(version);

	fread(&size, 4, 1, file);
	size = be32toh(size);

	fseek(file, 2, SEEK_CUR);

	fread(hardness, 1, 1680, file);

	for (int y = 0; y < TOTAL_HEIGHT; y++) {
		for (int x = 0; x < TOTAL_WIDTH; x++) {
			dungeon[y][x].hardness = hardness[y][x];
			if (y == 0 || y == TOTAL_HEIGHT - 1) {
				dungeon[y][x].symbol = '-';
			} else if (x == 0 || x == TOTAL_WIDTH - 1) {
				dungeon[y][x].symbol = '|';
			} else if (hardness[y][x] == 0) {
				dungeon[y][x].symbol = '#';
			} else {
				dungeon[y][x].symbol = ' ';
			}
		}
	}

}

void readRoomsAndStairs(FILE *file) {
	fseek(file, 20, SEEK_SET);
	uint8_t playerPosition[2];
	fread(playerPosition, 1, 2, file);
	placePlayerWithCoords(playerPosition[0], playerPosition[1]);

	fseek(file, 1702, SEEK_SET);
	fread(&numberOfRooms, 2, 1, file);
	numberOfRooms = be16toh(numberOfRooms);
	rooms = malloc(sizeof(struct room) * numberOfRooms);
	fread(rooms, 1, 4 * numberOfRooms, file);

	fread(&numberOfUpstairs, 2, 1, file);
	numberOfUpstairs = be16toh(numberOfUpstairs);
	upStairs = malloc(sizeof(struct room) * numberOfUpstairs);
	fread(upStairs, 1, numberOfUpstairs * 2, file);

	fread(&numberOfDownstairs, 2, 1, file);
	numberOfDownstairs = be16toh(numberOfDownstairs);
	downStairs = malloc(sizeof(struct room) * numberOfDownstairs);
	fread(downStairs, 1, numberOfDownstairs * 2, file);

	for (int i = 0; i < numberOfRooms; i++) {
		drawRoom(i);
	}
	for (int j = 0; j < numberOfUpstairs; j++) {
		dungeon[upStairs[j].y][upStairs[j].x].symbol = '<';
	}
	for (int k = 0; k < numberOfDownstairs; k++) {
		dungeon[downStairs[k].y][downStairs[k].x].symbol = '>';
	}

//	dungeon[playerPosition[1]][playerPosition[0]].symbol = '@';
}

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
	while (i < 2) {
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
			}
			i++;
		}
	}
	placePlayer();
}

void connectRooms() {
	for (int room = 0; room < MAX_ROOMS - 1; room++) {
		int x0 = rooms[room].x;
		int x1 = rooms[room + 1].x;
		int y0 = rooms[room].y;
		int y1 = rooms[room + 1].y;

		int x = x0;
		int y = y0;
		int xDirection = x1 - x0 == 0 ? 0 : (x1 - x0) / abs(x1 - x0);
		int yDirection = y1 - y0 == 0 ? 0 : (y1 - y0) / abs(y1 - y0);
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


void loadDungeon(char *fileName, int numMonsters) {
	FILE *file = openFile(fileName, "rb");
	readBasicInfo(file);
	readRoomsAndStairs(file);
	placeMonsters(numMonsters);
	fclose(file);
}

void saveDungeon(char *fileName) {
	char filePath[100] = "";
	strcat(filePath, getenv("HOME"));
	strcat(filePath, "/.rlg327/");
	strcat(filePath, fileName);

	uint8_t hardness[TOTAL_HEIGHT][TOTAL_WIDTH];

	FILE *file = fopen(filePath, "wb");

	for (int i = 0; i < TOTAL_HEIGHT; i++) {
		for (int j = 0; j < TOTAL_WIDTH; j++) {
			hardness[i][j] = dungeon[i][j].hardness;
		}
	}

	fwrite("RLG327-S2019", 1, 12, file); //Marker
	int32_t versionToWrite = htobe32(0);
	fwrite(&versionToWrite, 4, 1, file); //Version
	uint32_t size = 1708 + 4 * numberOfRooms + 2 * numberOfUpstairs + 2 * numberOfDownstairs;
	uint32_t sizeToWrite = htobe32(size);
	fwrite(&sizeToWrite, 4, 1, file);
	uint8_t playerPosition[2] = {playerCharacter->x, playerCharacter->y};
	fwrite(playerPosition, 1, 2, file);
	fwrite(hardness, 1, 1680, file);
	uint16_t numberOfRoomsToWrite = htobe16(numberOfRooms);
	fwrite(&numberOfRoomsToWrite, 1, 2, file);
	fwrite(rooms, 1, 4 * numberOfRooms, file);
	uint16_t numberOfUpstairsToWrite = htobe16(numberOfUpstairs);
	fwrite(&numberOfUpstairsToWrite, 1, 2, file);
	fwrite(upStairs, 1, 2 * numberOfUpstairs, file);
	uint16_t numberOfDownstairsToWrite = htobe16(numberOfDownstairs);
	fwrite(&numberOfDownstairsToWrite, 1, 2, file);
	fwrite(downStairs, 1, 2 * numberOfDownstairs, file);

	fclose(file);
}

void generateRandomFloor(int numMonsters) {
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
	placeMonsters(numMonsters);
}