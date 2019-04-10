#include "shared-components.h"

#include <stdio.h>
#include <cstdlib>
#include <ncurses.h>

static const char EMPTY_ROW_TEXT[81] = "                                                                                ";

DungeonPosition dungeon[TOTAL_HEIGHT][TOTAL_WIDTH];
DistancePosition nonTunnelDistance[TOTAL_HEIGHT][TOTAL_WIDTH];
DistancePosition tunnelDistance[TOTAL_HEIGHT][TOTAL_WIDTH];
Character *characterMap[TOTAL_HEIGHT][TOTAL_WIDTH];
Object *objectMap[TOTAL_HEIGHT][TOTAL_WIDTH];
char teleportDungeon[TOTAL_HEIGHT][TOTAL_WIDTH];
char rememberedMap[TOTAL_HEIGHT][TOTAL_WIDTH];
vector<MonsterDescription> monsters;
vector<ItemDescription> items;
Room *rooms;
Position *upStairs;
Position *downStairs;
CharacterHeap *playerQueue;
Character *playerCharacter;
bool fogOfWarActivated;

void drawRoom(int roomNumber) {
	for (int i = rooms[roomNumber].y; i < rooms[roomNumber].y + rooms[roomNumber].height; i++) {
		for (int j = rooms[roomNumber].x; j < rooms[roomNumber].x + rooms[roomNumber].width; j++) {
			dungeon[i][j].symbol = '.';
			dungeon[i][j].hardness = 0;
		}
	}
}

void printRememberedDungeon(int x, int y) {
	int i, j;
	mvaddstr(0, 0, EMPTY_ROW_TEXT);
	for (i = 0; i < TOTAL_HEIGHT; i++) {
		for (j = 0; j < TOTAL_WIDTH; j++) {
			if (characterMap[i][j] != NULL && abs(y - i) <= 2 && abs(x - j) <= 2) {
				attron(COLOR_PAIR(characterMap[i][j]->color));
				mvaddch(i + 1, j, characterMap[i][j]->symbol);
				attroff(COLOR_PAIR(characterMap[i][j]->color));
			} else if (objectMap[i][j] != NULL && abs(y - i) <= 2 && abs(x - j) <= 2) {
				attron(COLOR_PAIR(objectMap[i][j]->color));
				mvaddch(i + 1, j, objectMap[i][j]->symbol);
				attroff(COLOR_PAIR(objectMap[i][j]->color));
			} else {
				attron(COLOR_PAIR(COLOR_BLACK));
				mvaddch(i + 1, j, rememberedMap[i][j]);
				attroff(COLOR_PAIR(COLOR_BLACK));
			}
		}
	}
	mvaddstr(22, 0, EMPTY_ROW_TEXT);
	mvaddstr(23, 0, EMPTY_ROW_TEXT);
	refresh();
}

void printFullDungeon() {
	int i, j;
	mvaddstr(0, 0, EMPTY_ROW_TEXT);
	for (i = 0; i < TOTAL_HEIGHT; i++) {
		for (j = 0; j < TOTAL_WIDTH; j++) {
			if (teleportDungeon[i][j] != ' ') {
				attron(COLOR_PAIR(COLOR_BLUE));
				mvaddch(i + 1, j, teleportDungeon[i][j]);
				attroff(COLOR_PAIR(COLOR_BLUE));
			} else if (objectMap[i][j] != NULL) {
				attron(COLOR_PAIR(objectMap[i][j]->color));
				mvaddch(i + 1, j, objectMap[i][j]->symbol);
				attroff(COLOR_PAIR(objectMap[i][j]->color));
			} else if (characterMap[i][j] != NULL) {
				attron(COLOR_PAIR(characterMap[i][j]->color));
				mvaddch(i + 1, j, characterMap[i][j]->symbol);
				attroff(COLOR_PAIR(characterMap[i][j]->color));
			} else {
				attron(COLOR_PAIR(COLOR_BLACK));
				mvaddch(i + 1, j, dungeon[i][j].symbol);
				attroff(COLOR_PAIR(COLOR_BLACK));
			}
		}

	}
	mvaddstr(22, 0, EMPTY_ROW_TEXT);
	mvaddstr(23, 0, EMPTY_ROW_TEXT);

	refresh();
}

void printDungeon(Player *player) {
	int x = player->x;
	int y = player->y;

	for (int i = y - 2; i <= y + 2; i++) {
		for (int j = x - 2; j <= x + 2; j++) {
			if (i >= 0 && i < 21 && j >= 0 && j < 80) {
				rememberedMap[i][j] = dungeon[i][j].symbol;
			}
		}
	}

	if (fogOfWarActivated) {
		printRememberedDungeon(x, y);
	} else {
		printFullDungeon();
	}
}
