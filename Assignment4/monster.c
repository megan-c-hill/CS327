#include <stdlib.h>
#include "monster.h"
#include "shared-components.h"

#define NPC_SMART    0x00000001
#define NPC_TELE    0x00000002
#define NPC_TUNNEL    0x00000004
#define NPC_ERRATIC    0x00000008

#define has_characteristic(character, bit) \
    ((character) -> npm -> characteristics & NPC_##bit);

char getSymbol(int number){
	switch (number) {
		case 0:
			return '0';
		case 1:
			return '1';
		case 2:
			return '2';
		case 3:
			return '3';
		case 4:
			return '4';
		case 5:
			return '5';
		case 6:
			return '6';
		case 7:
			return '7';
		case 8:
			return '8';
		case 9:
			return '9';
		case 10:
			return 'a';
		case 11:
			return 'b';
		case 12:
			return 'c';
		case 13:
			return 'd';
		case 14:
			return 'e';
		case 15:
			return 'f';
		default:
			return '!';
	}
}


struct character* generateMonsterCharacter() {
	uint8_t characteristics;
	characteristics = rand() % 16;

	struct monster *npm = malloc(sizeof(struct monster));
	npm -> characteristics = characteristics;

	struct character *monster = malloc(sizeof(struct character));
	monster -> npm = npm;
	monster -> pc = NULL;
	monster -> symbol = getSymbol(characteristics);
	monster -> speed = rand() % 15 + 5;
	return monster;
};

struct character * generatePlayerCharacter() {
	struct player *pc = malloc(sizeof(struct player));
	struct character *playerCharacter = malloc(sizeof(struct character));

	playerCharacter -> pc = pc;
	playerCharacter -> npm = NULL;
	playerCharacter -> speed = 10;
	playerCharacter -> symbol = '@';

	return playerCharacter;
}

void placeMonsters (int numMonsters){
	int counter = 0;
	uint8_t x, y;
	while(counter < numMonsters){
		x = rand() % (TOTAL_WIDTH - 5) + 1;
		y = rand() % (TOTAL_HEIGHT - 4) + 1;
		struct character *monster = generateMonsterCharacter();

		if(dungeon[y][x].symbol == '#' || dungeon[y][x].symbol == '.'){
			dungeon[y][x].symbol = monster -> symbol;
			monster -> x = x;
			monster -> y = y;
			counter ++;
		}
	}
}

void placePlayer(){
	int counter = 0;
	uint8_t x, y;
	while(counter < 1){
		x = rand() % (TOTAL_WIDTH - 5) + 1;
		y = rand() % (TOTAL_HEIGHT - 4) + 1;
		struct character *monster = generatePlayerCharacter();

		if(dungeon[y][x].symbol == '#' || dungeon[y][x].symbol == '.'){
			dungeon[y][x].symbol = monster -> symbol;
			monster -> x = x;
			monster -> y = y;
			counter ++;
		}
	}
}

void placePlayerWithCoords(int x, int y){
	struct character *pc = generatePlayerCharacter();

	pc -> x = x;
	pc -> y = y;
}