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
//	initscr();
//	keypad(stdscr, true);
//	curs_set(0);
//	refresh();
//	int seed = time(NULL);
//	char seedText[20];
//	mvaddstr(0, 0, seedText);
//	refresh();
//	srand(seed);
//
//	bool shouldSave = false;
//	bool shouldLoad = false;
//	bool shouldSetMonsters = false;
//	int numMonsters = 10;
//	char fileName[100] = "dungeon";
//	initCharacterMap();
//	initTeleportMap();
//	initRememberedMap();
//
//	for (int argIndex = 1; argIndex < argc; argIndex++) {
//		if (strcmp(argv[argIndex], "--save") == 0) {
//			shouldSave = true;
//		} else if (strcmp(argv[argIndex], "--load") == 0) {
//			shouldLoad = true;
//		} else if (strcmp(argv[argIndex], "--nummon") == 0) {
//			shouldSetMonsters = true;
//		} else {
//			if (shouldSetMonsters) {
//				numMonsters = (int) strtol(argv[argIndex], (char **) NULL, 10);
//			} else {
//				strcpy(fileName, argv[argIndex]);
//			}
//		}
//	}
//	fogOfWarActivated = true;
//
//	if (shouldLoad) {
//		loadDungeon(fileName, numMonsters);
//	} else {
//		generateRandomFloor(numMonsters);
//	}
//	if (shouldSave) {
//		saveDungeon(fileName);
//	}
//
//	free(rooms);
//	free(upStairs);
//	free(downStairs);
//
//	playGame();
//	endwin();

}
