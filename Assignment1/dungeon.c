#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_ROOMS 6
#define TOTAL_HEIGHT 21
#define TOTAL_WIDTH 80

char dungeon[TOTAL_HEIGHT][TOTAL_WIDTH];

void printDungeon() {
    int i, j;
    for (i = 0; i < TOTAL_HEIGHT; i++) {
        for (j = 0; j < TOTAL_WIDTH; j++) {
            printf("%c", dungeon[i][j]);
        }
        printf("\n");
    }
}

bool isLegalPlacement(int x, int y, int width, int height) {
    int i, j;
    if (y + height + 1 >= TOTAL_HEIGHT) return false;
    if (x + width + 1 >= TOTAL_WIDTH) return false;

    for (i = y - 1; i < y + height + 1; i++) {
        for (j = x - 1; j < x + width + 1; j++) {
            if (dungeon[i][j] != ' ') {
                return false;
            }
        }
    }
    return true;
}

void drawRoom(int x, int y, int width, int height) {
    int i, j;
    for (i = y; i < y + height; i++) {
        for (j = x; j < x + width; j++) {
            dungeon[i][j] = '.';
        }
    }
}

void placeStairs() {
    int x, y;
    int i = 0;
    while (i < 2) {
        x = rand() % 78 + 1;
        y = rand() % 19 + 1;
        if (dungeon[y][x] == '.' || dungeon[y][x] == '#') {
            if (i == 0) {
                dungeon[y][x] = '>';
            } else {
                dungeon[y][x] = '<';
            }
            i++;
        }
    }
}

void connectRooms(int rooms[6][4]) {
    for (int room = 0; room < 5; room++) {
        int x0 = rooms[room][0];
        int x1 = rooms[room + 1][0];
        int y0 = rooms[room][1];
        int y1 = rooms[room + 1][1];

        int x = x0;
        int y = y0;
        int xDirection = (x1 - x0) / abs(x1 - x0);
        int yDirection = (y1 - y0) / abs(y1 - y0);
        int count;

        for (count = 0; count < abs(x1 - x0); count++) {
            if (dungeon[y0][x] == ' ') {
                dungeon[y0][x] = '#';
            }
            x = x + xDirection;
        }

        for (count = 0; count < abs(y1 - y0); count++) {
            if (dungeon[y][x] == ' ') {
                dungeon[y][x] = '#';
            }
            y = y + yDirection;
        }

    }
}

void placeRoom(int rooms[MAX_ROOMS][4], int roomNumber) {
    int x = rand() % (TOTAL_WIDTH - 5) + 1;
    int y = rand() % (TOTAL_HEIGHT - 4) + 1;
    int width = rand() % 6 + 4;
    int height = rand() % 4 + 3;

    if (isLegalPlacement(x, y, width, height)) {
        drawRoom(x, y, width, height);
        rooms[roomNumber][0] = x;
        rooms[roomNumber][1] = y;
        rooms[roomNumber][2] = width;
        rooms[roomNumber][3] = height;
    } else {
        placeRoom(rooms, roomNumber);
    }
}

void generateRandomFloor() {
    int rooms[MAX_ROOMS][4];
    int seed = time(NULL);
    printf("Seed: %d\n", seed);
    srand(seed);

    int i, j;
    for (i = 0; i < TOTAL_HEIGHT; i++) {
        for (j = 0; j < TOTAL_WIDTH; j++) {
            char value = ' ';
            if (i == 0 || i == TOTAL_HEIGHT - 1) {
                value = '-';
            } else if (j == 0 || j == TOTAL_WIDTH - 1) {
                value = '|';
            }
            dungeon[i][j] = value;
        }
    }
    for (i = 0; i < MAX_ROOMS; i++) {
        placeRoom(rooms, i);
    }
    connectRooms(rooms);
    placeStairs();
}

int main(int argc, char *argv[]) {
    generateRandomFloor();
    printDungeon();
}
