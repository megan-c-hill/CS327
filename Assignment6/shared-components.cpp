#include "shared-components.h"

#include <stdio.h>
#include <ncurses.h>
static const char EMPTY_ROW_TEXT[81] = "                                                                                ";

struct dungeonPosition dungeon[TOTAL_HEIGHT][TOTAL_WIDTH];
DistancePosition nonTunnelDistance[TOTAL_HEIGHT][TOTAL_WIDTH];
DistancePosition tunnelDistance[TOTAL_HEIGHT][TOTAL_WIDTH];
Character *characterMap[TOTAL_HEIGHT][TOTAL_WIDTH];
struct room *rooms;
struct position *upStairs;
struct position *downStairs;
CharacterHeap *playerQueue;
Character *playerCharacter;

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
	mvaddstr(0, 0, EMPTY_ROW_TEXT);
	for (i = 0; i < TOTAL_HEIGHT; i++) {
		for (j = 0; j < TOTAL_WIDTH; j++) {
			if (characterMap[i][j] != NULL) {
				mvaddch(i + 1, j, characterMap[i][j]->symbol);
			} else {
				mvaddch(i + 1, j, dungeon[i][j].symbol);
			}
		}

	}
	mvaddstr(22, 0, EMPTY_ROW_TEXT);
	mvaddstr(23, 0, EMPTY_ROW_TEXT);
	refresh();
}