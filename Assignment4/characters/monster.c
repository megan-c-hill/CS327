#include <stdlib.h>
#include <stdio.h>
#include <zconf.h>
#include "monster.h"
#include "../shared-components.h"

//TECH DEBT allow more monsters than dungeon spaces

#define NPC_SMART    0x00000001
#define NPC_TELE    0x00000002
#define NPC_TUNNEL    0x00000004
#define NPC_ERRATIC    0x00000008

int isErratic(Character *character) {
	return character->npm == NULL ? 0 : character->npm->characteristics & NPC_ERRATIC;
}

int isSmart(Character *character) {
	return character->npm == NULL ? 0 : character->npm->characteristics & NPC_SMART;
}

int isTelepathic(Character *character) {
	return character->npm == NULL ? 0 : character->npm->characteristics & NPC_TELE;
}

int isTunnelable(Character *character) {
	return character->npm == NULL ? 0 : character->npm->characteristics & NPC_TUNNEL;
}

char getSymbol(int number) {
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


Character *generateMonsterCharacter() {
	uint8_t characteristics;
	characteristics = rand() % 16;
//	characteristics = 6;

	Monster *npm = malloc(sizeof(Monster));
	npm->characteristics = characteristics;

	Character *monster = malloc(sizeof(Character));
	monster->npm = npm;
	monster->pc = NULL;
	monster->symbol = getSymbol(characteristics);
	monster->speed = rand() % 15 + 5;
	return monster;
};

Character *generatePlayerCharacter() {
	Player *pc = malloc(sizeof(Player));
	Character *playerCharacter = malloc(sizeof(Character));

	playerCharacter->pc = pc;
	playerCharacter->npm = NULL;
	playerCharacter->speed = 10;
	playerCharacter->symbol = '@';

	return playerCharacter;
}

void placeMonsters(int numMonsters) {
	int counter = 0;
	uint8_t x, y;
	while (counter < numMonsters) {
		x = rand() % (TOTAL_WIDTH - 5) + 1;
		y = rand() % (TOTAL_HEIGHT - 4) + 1;
		Character *monster = generateMonsterCharacter();

		if ((dungeon[y][x].symbol == '#' || dungeon[y][x].symbol == '.') && characterMap[y][x] == NULL) {
			monster->x = x;
			monster->y = y;
			characterMap[y][x] = monster;
			pushCharacter(playerQueue, monster, 0);
			counter++;
		}
	}
}

void placePlayer() {
	bool isDone = false;
	uint8_t x, y;
	while (!isDone) {
		x = rand() % (TOTAL_WIDTH - 5) + 1;
		y = rand() % (TOTAL_HEIGHT - 4) + 1;
		Character *pc = generatePlayerCharacter();

		if (dungeon[y][x].symbol == '#' || dungeon[y][x].symbol == '.') {
			pc->x = x;
			pc->y = y;
			playerPosition[0] = x;
			playerPosition[1] = y;
			characterMap[y][x] = pc;
			isDone = true;
			CharacterNode *head = newCharacterNode(pc, 0);
			playerQueue = newCharacterHeap(head);
		}
	}
}

void placePlayerWithCoords(int x, int y) {
	Character *pc = generatePlayerCharacter();
	pc->x = x;
	pc->y = y;
	characterMap[y][x] = pc;
	CharacterNode *head = newCharacterNode(pc, 0);
	playerQueue = newCharacterHeap(head);
}

void initCharacterMap() {
	for (int i = 0; i < TOTAL_HEIGHT; i++) {
		for (int j = 0; j < TOTAL_WIDTH; j++) {
			characterMap[i][j] = NULL;
		}

	}
}

void moveToSpot(Character *character, int newX, int newY) {
	characterMap[character->y][character->x] = NULL;
	character->x = newX;
	character->y = newY;
	if (characterMap[newY][newX] != NULL) {
		removeFromHeap(playerQueue, characterMap[newY][newX]);
	}
	characterMap[character->y][character->x] = character;
}

void tunnel(Character *character, int newX, int newY) {
	int hardness = dungeon[newY][newX].hardness - 85;
	if (hardness <= 0) {
		dungeon[newY][newX].hardness = 0;
		dungeon[newY][newX].symbol = '#';
		moveToSpot(character, newX, newY);

	} else {
		dungeon[newY][newX].hardness = hardness;
	}
}

void goTowardsPC(Character *character) {
	int xDirection = playerPosition[0] - character->x == 0 ? 0 : (playerPosition[0] - character->x) /
																 abs(playerPosition[0] - character->x);
	int yDirection = playerPosition[1] - character->y == 0 ? 0 : (playerPosition[1] - character->y) /
																 abs(playerPosition[1] - character->y);
	int newX = character->x + xDirection;
	int newY = character->y + yDirection;

	if (dungeon[newY][newX].hardness == 0) {
		moveToSpot(character, newX, newY);
	} else if (isTunnelable(character) && dungeon[newY][newX].hardness != 255) {
		tunnel(character, newX, newY);
	}
}

void randomMove(Character *character) {
	int changeX = 0;
	int changeY = 0;

	while (changeX == 0 && changeY == 0) {
		changeX = +rand() % 3 - 1;
		changeY = +rand() % 3 - 1;
	}

	uint8_t newX = (character->x) + changeX;
	uint8_t newY = (character->y) + changeY;

	if (dungeon[newY][newX].hardness == 0) {
		moveToSpot(character, newX, newY);
	} else if (isTunnelable(character) && dungeon[newY][newX].hardness != 255) {
		tunnel(character, newX, newY);
	} else {
		randomMove(character);
	}
}

void makeCharacterMove(Character *character) {
	if (isErratic(character) && rand() % 2 == 1) {
		randomMove(character);
	} else if (isSmart(character)) {
		//Use maps to go to last known pc unless is telepathic then go to current position
	} else if (isTelepathic(character)) {
		goTowardsPC(character);
	} else {
		//go in straight line to pc if visible else stay still
	}
}

void move() {
	int counter = 0;
	//Should end immediately if there are 0 monsters
	while (characterMap[playerPosition[1]][playerPosition[0]] -> symbol == '@' && playerQueue -> head -> next != NULL) { //Player is dead or only one player in queue
		CharacterNode *characterNode = popCharacterNode(playerQueue);
		if (characterNode->character->symbol == '@') {
			counter++;
			usleep(250000);
			printDungeon();
		}
		makeCharacterMove(characterNode->character);
		pushCharacter(playerQueue, characterNode->character, characterNode->priority + characterNode->character->speed);
	}
	printDungeon();
	printf("Game Over!\n");
}