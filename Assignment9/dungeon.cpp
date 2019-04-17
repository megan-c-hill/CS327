#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "generate-dungeon.h"
#include "shared-components.h"
#include "distance/distance.h"
#include "characters/Character.h"
#include "descriptions/monsterDescription.h"
#include "descriptions/itemDescription.h"
#include <time.h>
#include <stdio.h>
#include <ncurses.h>

//TECH DEBT / ENHANCEMENT Unit tests

int main(int argc, char *argv[]) {
	readMonsterFile();
	readObjectFile();
	initscr();
	keypad(stdscr, true);
	start_color();
	curs_set(0);
	refresh();
	int seed = time(NULL);
	char seedText[20];
	mvaddstr(0, 0, seedText);
	refresh();
	srand(seed);

	init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
	init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
	init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(COLOR_BLACK, COLOR_BLACK, COLOR_WHITE);
	init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);

	bool shouldSave = false;
	bool shouldLoad = false;
	bool shouldSetMonsters = false;
	bool shouldSetItems = false;
	bossKilled = false;
	int numMonsters = 10;
	int numItems = 15;
	char fileName[100] = "dungeon";
	initMaps();
	initRememberedMap();

	for (int argIndex = 1; argIndex < argc; argIndex++) {
		if (strcmp(argv[argIndex], "--save") == 0) {
			shouldSave = true;
		} else if (strcmp(argv[argIndex], "--load") == 0) {
			shouldLoad = true;
		} else if (strcmp(argv[argIndex], "--nummon") == 0) {
			shouldSetMonsters = true;
		} else if (strcmp(argv[argIndex], "--numitems") == 0) {
			shouldSetItems = true;
		} else {
			if(shouldSetItems) {
				numItems = (int) strtol(argv[argIndex], (char**) NULL, 10);
			} else if (shouldSetMonsters) {
				numMonsters = (int) strtol(argv[argIndex], (char **) NULL, 10);
			} else {
				strcpy(fileName, argv[argIndex]);
			}
		}
	}
	fogOfWarActivated = true;

	if (shouldLoad) {
		loadDungeon(fileName, numMonsters);
	} else {
		generateRandomFloor(numMonsters, numItems);
	}
	if (shouldSave) {
		saveDungeon(fileName);
	}

	free(rooms);
	free(upStairs);
	free(downStairs);

	playGame();
	endwin();

}
