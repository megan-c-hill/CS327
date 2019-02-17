#include "shared-components.c"
#include <string.h>
#include <stdlib.h>

#ifdef __APPLE__

#include <libkern/OSByteOrder.h>
#define htobe16(x) OSSwapHostToBigInt16(x)
#define htobe32(x) OSSwapHostToBigInt32(x)
#else
#include <endian.h>
#endif

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