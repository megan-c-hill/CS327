#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int min(int a, int b){
    if(a > b) {
        return b;
    } 
    return a;
}

int max (int a, int b) {
    if(a > b) {
        return a;
    }
    return b;
}

void printDungeon(char dungeon[21][80]){
      int i, j;
      for(int i = 0; i<21; i++){
        for(int j = 0; j<80; j++){
            printf("%c", dungeon[i][j]);
       }
      printf("\n");
   }
}

bool isLegalPlacement(char dungeon[21][80], int x, int y, int width, int height) {
    int i, j;
    if(y + height + 1 >= 21) return false;
    if(x + width + 1 >= 80) return false;

    for(i = y - 1; i < y + height + 1; i++){
        for(j = x - 1; j < x + width + 1; j++){
            if(dungeon[i][j] != ' '){
                return false;
            }
        }
    }
    return true;
}

void drawRoom (char dungeon[21][80], int x, int y, int width, int height){
    int i, j;
    for(i = y; i < y + height; i++){
        for (j = x; j < x +width; j++){
            dungeon[i][j] = '.';
        }
    }
}

void connectRooms(char dungeon[21][80], int rooms[6][4]){
    for(int room = 0; room < 5; room++){
        int x0 = rooms[room][0];
        int x1 = rooms[room + 1][0];
        int y0 = rooms[room][1];
        int y1 = rooms[room + 1][1];

        int x, y;
        int minY, maxX;
        minY = min(y0, y1);
        maxX = max(x0, x1);
        
        for(x = min(x0, x1); x < maxX; x++){
            if(dungeon[minY][x] == ' '){
                dungeon[minY][x] = '#';
            }
        }
        for(y = minY; y < max(y0, y1); y++){
            if(dungeon[y][maxX] == ' '){
                dungeon[y][maxX] = '#';
            }
        }
    }
}

void placeRoom(char dungeon[21][80], int rooms[6][4], int roomNumber){
    int x = rand() % 75 + 1;
    int y = rand() % 17 + 1;
    int width = rand() % 6 + 4;
    int height = rand() % 4 + 3;
    
    if(isLegalPlacement(dungeon, x, y, width, height)) {
        drawRoom(dungeon, x, y, width, height);
        rooms[roomNumber][0] = x;
        rooms[roomNumber][1] = y;
        rooms[roomNumber][2] = width;
        rooms[roomNumber][3] = height;
    } else {
        placeRoom(dungeon, rooms, roomNumber);
    }
}

int main(int argc, char *argv[]) {
    char dungeon[21][80];
    int MAX_ROOMS = 6;
    int rooms[MAX_ROOMS][4];
    int seed = time(NULL);
    printf("Seed: %d\n", seed);
    srand(seed);

    int i, j;
    for(int i = 0; i < 21; i++){
        for(int j = 0; j<80; j++){
            int value = ' ';
            if(i == 0 || i == 20) {
                value = '-';
            } else if (j == 0 || j == 79) {
                value = '|';
            }
            dungeon[i][j] = value;
        }
    }
    for(int i = 0; i< MAX_ROOMS; i++){
        placeRoom(dungeon, rooms, i);
    }
    connectRooms(dungeon, rooms);
    printDungeon(dungeon);
}
