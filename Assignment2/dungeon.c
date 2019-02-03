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
uint8_t rooms[6][4];

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
            } else if(i == 1){
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

void loadDungeon(){
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
    strcat(filePath, "/.rlg327/01.rlg327");

    printf("File Path: %s\n", filePath);

    FILE *file = fopen(filePath, "rb");
    fread(marker, sizeof(char), 12, file);
    fread(&version, 4, 1, file);
    version = be32toh(version);
    fread(&size, 4, 1, file);
    size = be32toh(size);
    fread(playerPos, 1, 2, file);
    fread(hardness, 1, 1680, file);
    fread(&numRooms, 1, 1, file);
    uint8_t tempRooms[numRooms][4];
    fread(tempRooms, 1, 4 * numRooms, file);
    fread(&numUp, 1, 1, file);
    uint8_t ups[numUp][2];
    fread(ups, 1, numUp * 2, file);
    fread(&numDown, 1, 1, file);
    uint8_t downs[numDown][2];
    fread(downs, 1, numDown * 2, file);

    for(int y = 0; y<TOTAL_HEIGHT; y++){
        for(int x = 0; x<TOTAL_WIDTH; x++) {
            dungeon[y][x].hardness = hardness[y][x];
            if (y == 0 || y == TOTAL_HEIGHT - 1) {
                dungeon[y][x].symbol = '-';
            } else if (x == 0 || x == TOTAL_WIDTH - 1) {
                dungeon[y][x].symbol = '|';
            } else {
                dungeon[y][x].symbol = ' ';
            }
        }
    }

    for(int index = 0; index < numRooms; index++){
        printf("tempRoom: x:%d, y:%d, width:%d, height:%d\n", tempRooms[index][0], tempRooms[index][1], tempRooms[index][2], tempRooms[index][3]);
        rooms[index][0] = tempRooms[index][0];
        rooms[index][1] = tempRooms[index][1];
        rooms[index][2] = tempRooms[index][2];
        rooms[index][3] = tempRooms[index][3];
        printf("Room: x:%d, y:%d, width:%d, height:%d\n", rooms[index][0], rooms[index][1], rooms[index][2], rooms[index][3]);
    }

    fclose(file);
    for(int i = 0; i<numRooms; i++){
        drawRoom(i);
printf("Room: x:%d, y:%d, width:%d, height:%d\n", rooms[i][0], rooms[i][1], rooms[i][2], rooms[i][3]);
    }
    for(int j = 0; j<numUp; j++){
        dungeon[ups[j][1]][ups[j][0]].symbol = '<';
    }
    for(int k = 0; k<numDown; k++){
        dungeon[downs[k][1]][downs[k][0]].symbol = '>';
    }
    dungeon[playerPos[1]][playerPos[0]].symbol = '@';

    printf("%d\n", strlen(marker));
    printf("Marker: %s, version: %d, size: %d\n", marker, version, size);
    printf("Player: x: %d, y:%d\n", playerPos[0], playerPos[1]);
    printf("numRooms:%d\n", numRooms);
    for (int i1 = 0; i1 < numRooms; i1++) {
        printf("Room: x:%d, y:%d, width:%d, height:%d\n", rooms[i1][0], rooms[i1][1], rooms[i1][2], rooms[i1][3]);
    }
    printf("numUp: %d\n", numUp);
    for (int j1 = 0; j1 < numUp; j1++) {
        printf("UpStairs: x:%d, y:%d\n", ups[j1][0], ups[j1][1]);
    }
    printf("numDown: %d\n", numDown);
    for (int k1 = 0; k1 < numDown; k1++) {
        printf("downStairs: x:%d, y:%d\n", downs[k1][0], downs[k1][1]);
    }
}

int main(int argc, char *argv[]) {
    loadDungeon();
    // generateRandomFloor();
    printDungeon();
}

//00000000  52 4c 47 33 32 37 2d 53  32 30 31 39 00 00 00 00  |RLG327-S2019....|
//00000010  00 00 06 c7 10 0c ff ff  ff ff ff ff ff ff ff ff  |...Ç..ÿÿÿÿÿÿÿÿÿÿ|


//000006a0  ff ff ff ff ff ff 06 10  0c 04 06 0e 02 09 06 30  |ÿÿÿÿÿÿ.........0|
//000006b0  0a 08 04 09 08 04 04 18  02 08 04 23 08 04 03 01  |...........#....|
//000006c0  18 03 02 1c 02 1f 04

//numRooms:6
//Room: x:69, y:4, width:6, height:3
//Room: x:25, y:3, width:6, height:4
//Room: x:12, y:9, width:11, height:6
//Room: x:33, y:6, width:10, height:4
//Room: x:68, y:12, width:5, height:3
//Room: x:44, y:11, width:7, height:7

