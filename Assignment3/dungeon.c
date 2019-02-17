#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "generate-dungeon.c"
#include "load-and-save-dungeon.c"
#include "dijkstra.h"

//TECH DEBT / ENHANCEMENT Unit tests

int main(int argc, char *argv[]) {
    bool shouldSave = false;
    bool shouldLoad = false;
    char fileName[100] = "dungeon";

    for (int argIndex = 1; argIndex < argc; argIndex++) {
        if (strcmp(argv[argIndex], "--save") == 0) {
            shouldSave = true;
        } else if (strcmp(argv[argIndex], "--load") == 0) {
            shouldLoad = true;
        } else {
            strcpy(fileName, argv[argIndex]);
        }
    }

    if (shouldLoad) {
        loadDungeon(fileName);
    } else {
        generateRandomFloor();
    }

    if (shouldSave) {
        saveDungeon(fileName);
    }

    free(rooms);
    free(upStairs);
    free(downStairs);

    printDungeon();

    nonTunnelingDistance();
    tunnelingDistance();
}
