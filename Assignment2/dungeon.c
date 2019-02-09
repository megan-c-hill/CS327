#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#ifdef __APPLE__

#include <libkern/OSByteOrder.h>
#define htobe16(x) OSSwapHostToBigInt16(x)
#define be16toh(x) OSSwapBigToHostInt16(x)
#define htobe32(x) OSSwapHostToBigInt32(x)
#define be32toh(x) OSSwapBigToHostInt32(x)
#else
#include <endian.h>
#endif

#define MAX_ROOMS 8
#define TOTAL_HEIGHT 21
#define TOTAL_WIDTH 80

//ENHANCEMENT Generate Random Number of stairs
//ENHANCEMENT Generate random number of rooms
//ENHANCEMENT Unit tests
//ENHANCEMENT make corridors more random and have less of them
//TECH DEBT This file is getting pretty long
//ENHANCEMENT Validation on marker, version, number of rooms, presence of stairs?
//TECH DEBT Figure out how to split functionality into different files w/o loosing shared variables
//TECH DEBT Dynamically allocate size for room, upStairs and downStairs
//REMAINING FUNCTIONALITY Use switches to toggle between load and save or both
//ENHACEMENT Use dungeon as default but allow other values to be passed in

struct dungeonPosition {
    char symbol;
    uint8_t hardness;
};

struct room {
    uint8_t x;
    uint8_t y;
    uint8_t width;
    uint8_t height;
};

struct position {
    uint8_t x;
    uint8_t y;
};

struct dungeonPosition dungeon[TOTAL_HEIGHT][TOTAL_WIDTH];
struct room *rooms;
struct position *upStairs;
struct position *downStairs;
uint8_t playerPosition[2];
uint16_t numberOfRooms = 8;
uint16_t numberOfUpstairs = 1;
uint16_t numberOfDownstairs = 1;

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
    for (int i = rooms[roomNumber].y; i < rooms[roomNumber].y + rooms[roomNumber].height; i++) {
        for (int j = rooms[roomNumber].x; j < rooms[roomNumber].x + rooms[roomNumber].width; j++) {
            dungeon[i][j].symbol = '.';
            dungeon[i][j].hardness = 0;
        }
    }
}

void placeStairsAndPlayer() {
    uint8_t x, y;
    int i = 0;
    while (i < 3) {
        x = rand() % 78 + 1;
        y = rand() % 19 + 1;
        if (dungeon[y][x].hardness == 0) {
            if (i == 0) {
                numberOfDownstairs = 1;
                downStairs[0].x = x;
                downStairs[0].y = y;
                dungeon[y][x].symbol = '>';
            } else if (i == 1) {
                numberOfUpstairs = 1;
                upStairs[0].x = x;
                upStairs[0].y = y;
                dungeon[y][x].symbol = '<';
            } else {
                playerPosition[0] = x;
                playerPosition[1] = y;
                dungeon[y][x].symbol = '@';
            }
            i++;
        }
    }
}

void connectRooms() {
    for (int room = 0; room < MAX_ROOMS - 1; room++) {
        int x0 = rooms[room].x;
        int x1 = rooms[room + 1].x;
        int y0 = rooms[room].y;
        int y1 = rooms[room + 1].y;

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
    uint8_t x = rand() % (TOTAL_WIDTH - 5) + 1;
    uint8_t y = rand() % (TOTAL_HEIGHT - 4) + 1;
    uint8_t width = rand() % 8 + 4;
    uint8_t height = rand() % 6 + 3;
    numberOfRooms = roomNumber + 1;

    if (isLegalPlacement(x, y, width, height)) {
        rooms[roomNumber].x = x;
        rooms[roomNumber].y = y;
        rooms[roomNumber].width = width;
        rooms[roomNumber].height = height;
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
            uint8_t hardness = rand() % 255 + 1;
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

    rooms = malloc(sizeof(struct room) * numberOfRooms);
    for (i = 0; i < MAX_ROOMS; i++) {
        placeRoom(i);
    }
    upStairs = malloc(sizeof(struct position) * numberOfUpstairs);
    downStairs = malloc(sizeof(struct position) * numberOfDownstairs);
    connectRooms();
    placeStairsAndPlayer();
}

void readBasicInfo(FILE *file) {
    char marker[13];
    uint32_t version;
    uint32_t size;
    uint8_t hardness[TOTAL_HEIGHT][TOTAL_WIDTH];

    fread(marker, sizeof(char), 12, file);

    fread(&version, 4, 1, file);
    version = be32toh(version);

    fread(&size, 4, 1, file);
    size = be32toh(size);

    fseek(file, 2, SEEK_CUR);

    fread(hardness, 1, 1680, file);

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

}

void readRoomsAndStairs(FILE *file) {
    fseek(file, 20, SEEK_SET);
    fread(playerPosition, 1, 2, file);

    fseek(file, 1702, SEEK_SET);
    fread(&numberOfRooms, 2, 1, file);
    numberOfRooms = be16toh(numberOfRooms);
    rooms = malloc(sizeof(struct room) * numberOfRooms);
    fread(rooms, 1, 4 * numberOfRooms, file);

    fread(&numberOfUpstairs, 2, 1, file);
    numberOfUpstairs = be16toh(numberOfUpstairs);
    upStairs = malloc(sizeof(struct room) * numberOfUpstairs);
    fread(upStairs, 1, numberOfUpstairs * 2, file);

    fread(&numberOfDownstairs, 2, 1, file);
    numberOfDownstairs = be16toh(numberOfDownstairs);
    downStairs = malloc(sizeof(struct room) * numberOfDownstairs);
    fread(downStairs, 1, numberOfDownstairs * 2, file);

    for (int i = 0; i < numberOfRooms; i++) {
        drawRoom(i);
    }
    for (int j = 0; j < numberOfUpstairs; j++) {
        dungeon[upStairs[j].y][upStairs[j].x].symbol = '<';
    }
    for (int k = 0; k < numberOfDownstairs; k++) {
        dungeon[downStairs[k].y][downStairs[k].x].symbol = '>';
    }

    dungeon[playerPosition[1]][playerPosition[0]].symbol = '@';
}

FILE *openFile(char *fileName, char *openType) {
    char filePath[100] = "";
    strcat(filePath, getenv("HOME"));
    strcat(filePath, "/.rlg327/");
    strcat(filePath, fileName);

    FILE *file = fopen(filePath, openType);
    return file;
}

void loadDungeon(char *fileName) {
    FILE *file = openFile(fileName, "rb");
    readBasicInfo(file);
    readRoomsAndStairs(file);
    fclose(file);
}

void saveDungeon(char *fileName) {
    char filePath[100] = "";
    strcat(filePath, getenv("HOME"));
    strcat(filePath, "/.rlg327/");
    strcat(filePath, fileName);

    uint8_t hardness[TOTAL_HEIGHT][TOTAL_WIDTH];

    FILE *file = fopen(filePath, "wb");

    for (int i = 0; i < TOTAL_HEIGHT; i++) {
        for (int j = 0; j < TOTAL_WIDTH; j++) {
            hardness[i][j] = dungeon[i][j].hardness;
        }
    }

    fwrite("RLG327-S2019", 1, 12, file); //Marker
    int32_t versionToWrite = htobe32(0);
    fwrite(&versionToWrite, 4, 1, file); //Version
    uint32_t size = 1708 + 4 * numberOfRooms + 2 * numberOfUpstairs + 2 * numberOfDownstairs;
    uint32_t sizeToWrite = htobe32(size);
    fwrite(&sizeToWrite, 4, 1, file);
    fwrite(playerPosition, 1, 2, file);
    fwrite(hardness, 1, 1680, file);
    uint16_t numberOfRoomsToWrite = htobe16(numberOfRooms);
    fwrite(&numberOfRoomsToWrite, 1, 2, file);
    fwrite(rooms, 1, 4 * numberOfRooms, file);
    uint16_t numberOfUpstairsToWrite = htobe16(numberOfUpstairs);
    fwrite(&numberOfUpstairsToWrite, 1, 2, file);
    fwrite(upStairs, 1, 2 * numberOfUpstairs, file);
    uint16_t numberOfDownstairsToWrite = htobe16(numberOfDownstairs);
    fwrite(&numberOfDownstairsToWrite, 1, 2, file);
    fwrite(downStairs, 1, 2 * numberOfDownstairs, file);

    fclose(file);
}

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
}
