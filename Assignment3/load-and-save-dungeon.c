#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shared-components.c"

#ifdef __APPLE__

#include <libkern/OSByteOrder.h>
#define be16toh(x) OSSwapBigToHostInt16(x)
#define be32toh(x) OSSwapBigToHostInt32(x)
#define htobe16(x) OSSwapHostToBigInt16(x)
#define htobe32(x) OSSwapHostToBigInt32(x)
#else
#include <endian.h>
#endif

//ENHANCEMENT Validation version, number of rooms, presence of stairs?

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

	if(strcmp(marker, "RLG327-S2019") != 0){
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
	fread(playerPosition, 1, 2, file);

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

	dungeon[playerPosition[1]][playerPosition[0]].symbol = '@';
}

void loadDungeon(char *fileName) {
	FILE *file = openFile(fileName, "rb");
	readBasicInfo(file);
	readRoomsAndStairs(file);
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