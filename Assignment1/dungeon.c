#include <stdio.h>

void printDungeon(char dungeon[21][80]){
      int i, j;
      for(int i = 0; i<21; i++){
        for(int j = 0; j<80; j++){
            printf("%c", dungeon[i][j]);
       }
      printf("\n");
    }
}

int main(int argc, char *argv[]) {
    char dungeon[21][80];
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
    printDungeon(dungeon);
}
