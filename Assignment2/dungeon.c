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
int rooms[MAX_ROOMS][4];

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
    char filePath[100] = "";
    strcat(filePath, getenv("HOME"));
    strcat(filePath, "/.rlg327/01.rlg327");

    printf("File Path: %s\n", filePath);

printf("%d\n", strlen(marker));

     FILE *file = fopen(filePath, "rb");
     fread(marker, sizeof(char), 12, file);
printf("%d\n", strlen(marker));
printf("%s\n", marker);
     fread(&version, 4, 1, file);
     fread(&size, 4, 1, file);
     fclose(file);
     printf("%d\n", strlen(marker));
     printf("Marker: %s, version: %d, size: %d\n", marker, be32toh(version), be32toh(size));
}

int main(int argc, char *argv[]) {
    loadDungeon();
    // generateRandomFloor();
    //printDungeon();
}

//00000000  52 4c 47 33 32 37 2d 53  32 30 31 39 00 00 00 00  |RLG327-S2019....|
//00000010  00 00 06 c7 10 0c ff ff  ff ff ff ff ff ff ff ff  |...Ç..ÿÿÿÿÿÿÿÿÿÿ|

