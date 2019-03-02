#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "generate-dungeon.h"
#include "shared-components.h"
#include "distance/distance.h"
#include "characters/monster.h"
#include <time.h>
#include <stdio.h>

//TECH DEBT / ENHANCEMENT Unit tests

int main(int argc, char *argv[]) {
	int seed = time(NULL);
	printf("Seed: %d\n", seed);
	srand(seed);

	bool shouldSave = false;
	bool shouldLoad = false;
	bool shouldSetMonsters = false;
	int numMonsters = 10;
	char fileName[100] = "dungeon";
	initCharacterMap();

	for (int argIndex = 1; argIndex < argc; argIndex++) {
		if (strcmp(argv[argIndex], "--save") == 0) {
			shouldSave = true;
		} else if (strcmp(argv[argIndex], "--load") == 0) {
			shouldLoad = true;
		} else if (strcmp(argv[argIndex], "--nummon") == 0) {
			shouldSetMonsters = true;
		} else {
			if (shouldSetMonsters) {
				numMonsters = (int) strtol(argv[argIndex], (char **) NULL, 10);
			} else {
				strcpy(fileName, argv[argIndex]);
			}
		}
	}

	if (shouldLoad) {
		loadDungeon(fileName, numMonsters);
	} else {
		generateRandomFloor(numMonsters);
	}
	if (shouldSave) {
		saveDungeon(fileName);
	}

	free(rooms);
	free(upStairs);
	free(downStairs);

	move();

}
