#include "shared-components.h"

#include <stdio.h>

void drawRoom(int roomNumber) {
	for (int i = rooms[roomNumber].y; i < rooms[roomNumber].y + rooms[roomNumber].height; i++) {
		for (int j = rooms[roomNumber].x; j < rooms[roomNumber].x + rooms[roomNumber].width; j++) {
			dungeon[i][j].symbol = '.';
			dungeon[i][j].hardness = 0;
		}
	}
}

void printDungeon() {
	int i, j;
	for (i = 0; i < TOTAL_HEIGHT; i++) {
		for (j = 0; j < TOTAL_WIDTH; j++) {
			if(characterMap[i][j] != NULL){
				printf("%c", characterMap[i][j] -> symbol);
			} else {
				printf("%c", dungeon[i][j].symbol);
			}
		}
		printf("\n");
	}
}