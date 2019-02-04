#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <endian.h>

#define MAX_ROOMS 8
#define TOTAL_HEIGHT 21
#define TOTAL_WIDTH 80

struct position {
    char symbol;
    int hardness;
};

struct position dungeon[TOTAL_HEIGHT][TOTAL_WIDTH];
uint8_t rooms[][4];

void printDungeon() {
    int i, j;
    for (i = 0; i < TOTAL_HEIGHT; i++) {
        for (j = 0; j < TOTAL_WIDTH; j++) {
            printf("%c", dungeon[i][j].symbol);
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
            if (dungeon[i][j].symbol != ' ') {
                return false;
            }
        }
    }
    return true;
}

void drawRoom(int roomNumber) {
    int i, j;
    for (i = rooms[roomNumber][1]; i < rooms[roomNumber][1] + rooms[roomNumber][3]; i++) {
        for (j = rooms[roomNumber][0]; j < rooms[roomNumber][0] + rooms[roomNumber][2]; j++) {
            dungeon[i][j].symbol = '.';
            dungeon[i][j].hardness = 0;
        }
    }
}

void placeStairsAndPlayer() {
    int x, y;
    int i = 0;
    while (i < 2) {
        x = rand() % 78 + 1;
        y = rand() % 19 + 1;
        if (dungeon[y][x].hardness == 0) {
            if (i == 0) {
                dungeon[y][x].symbol = '>';
            } else if (i == 1) {
                dungeon[y][x].symbol = '<';
            } else {
                dungeon[y][x].symbol = '@';
            }
            i++;
        }
    }
}

void connectRooms() {
    for (int room = 0; room < MAX_ROOMS - 1; room++) {
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
            if (dungeon[y0][x].symbol == ' ') {
                dungeon[y0][x].symbol = '#';
                dungeon[y0][x].hardness = 0;
            }
            x = x + xDirection;
        }

        for (count = 0; count < abs(y1 - y0); count++) {
            if (dungeon[y][x].symbol == ' ') {
                dungeon[y][x].symbol = '#';
                dungeon[y][x].hardness = 0;
            }
            y = y + yDirection;
        }

    }
}

void placeRoom(int roomNumber) {
    int x = rand() % (TOTAL_WIDTH - 5) + 1;
    int y = rand() % (TOTAL_HEIGHT - 4) + 1;
    int width = rand() % 8 + 4;
    int height = rand() % 6 + 3;

    if (isLegalPlacement(x, y, width, height)) {
        rooms[roomNumber][0] = x;
        rooms[roomNumber][1] = y;
        rooms[roomNumber][2] = width;
        rooms[roomNumber][3] = height;
        drawRoom(roomNumber);
    } else {
        placeRoom(roomNumber);
    }
}

void generateRandomFloor() {
    int seed = time(NULL);
    printf("Seed: %d\n", seed);
    srand(seed);

    int i, j;
    for (i = 0; i < TOTAL_HEIGHT; i++) {
        for (j = 0; j < TOTAL_WIDTH; j++) {
            char value = ' ';
            int hardness = rand() % 255 + 1;
            if (i == 0 || i == TOTAL_HEIGHT - 1) {
                value = '-';
                hardness = 255;
            } else if (j == 0 || j == TOTAL_WIDTH - 1) {
                value = '|';
                hardness = 255;
            }
            dungeon[i][j].symbol = value;
            dungeon[i][j].hardness = hardness;
        }
    }
    for (i = 0; i < MAX_ROOMS; i++) {
        placeRoom(i);
    }
    connectRooms();
    placeStairsAndPlayer();
}

void loadDungeon(char *fileName) {
    char marker[13];
    uint32_t version;
    uint32_t size;
    uint8_t playerPos[2];
    uint8_t hardness[TOTAL_HEIGHT][TOTAL_WIDTH];
    uint8_t numRooms;
    uint8_t numUp;
    uint8_t numDown;

    char filePath[100] = "";
    strcat(filePath, getenv("HOME"));
    strcat(filePath, "/.rlg327/");
    strcat(filePath, fileName);

    FILE *file = fopen(filePath, "rb");
    fread(marker, sizeof(char), 12, file);
    fread(&version, 4, 1, file);
    version = be32toh(version);
    fread(&size, 4, 1, file);
    size = be32toh(size);
    fread(playerPos, 1, 2, file);
    fread(hardness, 1, 1680, file);
    fread(&numRooms, 1, 1, file);
    fread(rooms, 1, 4 * numRooms, file);
    fread(&numUp, 1, 1, file);
    uint8_t ups[numUp][2];
    fread(ups, 1, numUp * 2, file);
    fread(&numDown, 1, 1, file);
    uint8_t downs[numDown][2];
    fread(downs, 1, numDown * 2, file);

    for (int y = 0; y < TOTAL_HEIGHT; y++) {
        for (int x = 0; x < TOTAL_WIDTH; x++) {
            dungeon[y][x].hardness = hardness[y][x];
            if (y == 0 || y == TOTAL_HEIGHT - 1) {
                dungeon[y][x].symbol = '-';
            } else if (x == 0 || x == TOTAL_WIDTH - 1) {
                dungeon[y][x].symbol = '|';
            } else if (hardness[y][x] == 0) {
                dungeon[y][x].symbol = '#';
            } else {
                dungeon[y][x].symbol = ' ';
            }
        }
    }

    fclose(file);
    for (
            int i = 0;
            i < numRooms;
            i++) {
        drawRoom(i);
    }
    for (
            int j = 0;
            j < numUp;
            j++) {
        dungeon[ups[j][1]][ups[j][0]].
                symbol = '<';
    }
    for (
            int k = 0;
            k < numDown;
            k++) {
        dungeon[downs[k][1]][downs[k][0]].
                symbol = '>';
    }
    dungeon[playerPos[1]][playerPos[0]].
            symbol = '@';
}

int main(int argc, char *argv[]) {
    loadDungeon(argv[1]);
    // generateRandomFloor();
    printDungeon();
}
