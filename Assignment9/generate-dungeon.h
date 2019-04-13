#ifndef CS327_GENERATE_DUNGEON_H
#define CS327_GENERATE_DUNGEON_H

void generateRandomFloor(int numMonsters, int numItems);

void saveDungeon(char *fileName);

void loadDungeon(char *fileName, int numMonsters);

#endif //CS327_GENERATE_DUNGEON_H
