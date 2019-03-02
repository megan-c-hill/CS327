#include "shared-components.h"

#include <stdio.h>
#include <ncurses.h>

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
			if (characterMap[i][j] != NULL) {
				mvaddch(i + 3, j, characterMap[i][j]->symbol);
			} else {
				mvaddch(i + 3, j, dungeon[i][j].symbol);
			}
		}

	}
	refresh();
}