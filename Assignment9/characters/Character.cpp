#include <stdlib.h>
#include <stdio.h>
#include <zconf.h>
#include <ncurses.h>
#include <cstring>
#include "Character.h"
#include "../shared-components.h"
#include "../distance/distance.h"
#include "../generate-dungeon.h"
#include "Monster.h"
#include <iostream>

static const char EMPTY_ROW_TEXT[81] = "                                                                                ";

Player *generatePlayerCharacter() {
	Player *pc = (Player *) malloc(sizeof(Player));

	pc->speed = 10;
	pc->symbol = '@';
	strcpy(pc->name, "You");
	pc->color = COLOR_BLUE;

	return pc;
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
			characterMap[y][x] = pc;
			isDone = true;
			CharacterNode *head = newCharacterNode(pc, 0);
			playerQueue = newCharacterHeap(head);
			playerCharacter = pc;
		}
	}
}

void placePlayerWithCoords(int x, int y) {
	Player *pc = generatePlayerCharacter();
	pc->x = x;
	pc->y = y;
	characterMap[y][x] = pc;
	CharacterNode *head = newCharacterNode(pc, 0);
	playerCharacter = pc;
	playerQueue = newCharacterHeap(head);
}

void initCharacterMap() {
	for (int i = 0; i < TOTAL_HEIGHT; i++) {
		for (int j = 0; j < TOTAL_WIDTH; j++) {
			characterMap[i][j] = NULL;
		}

	}
}

void initTeleportMap() {
	for (int i = 0; i < TOTAL_HEIGHT; i++) {
		for (int j = 0; j < TOTAL_WIDTH; j++) {
			teleportDungeon[i][j] = ' ';
		}
	}
}

//TODO combine at least two of these init maps
void initRememberedMap() {
	for (int y = 0; y < TOTAL_HEIGHT; y++) {
		for (int x = 0; x < TOTAL_WIDTH; x++) {
			if (y == 0 || y == TOTAL_HEIGHT - 1) {
				rememberedMap[y][x] = '-';
			} else if (x == 0 || x == TOTAL_WIDTH - 1) {
				rememberedMap[y][x] = '|';
			} else {
				rememberedMap[y][x] = ' ';
			}
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


int displayMonsterList(int offset, Player *player) {
	initscr();

	for (int i = 0; i < TOTAL_HEIGHT + 3; i++) {
		mvaddstr(i, 0, EMPTY_ROW_TEXT);
	}

	mvaddstr(0, 0, "Monster List");
	mvaddstr(1, 0, "------------");
	refresh();

	for (int i = 2; i < TOTAL_HEIGHT + 3; i++) {
		CharacterNode *monster = getCharacter(playerQueue, i - 2 + offset);
		if (monster != NULL) {
			int deltaX = playerCharacter->x - monster->character->x;
			int deltaY = playerCharacter->y - monster->character->y;
			char monsterData[81];
			sprintf(monsterData, "%c (%s) is %2d %s and %2d %s",
					monster->character->symbol,
					monster->character->name,
					abs(deltaY), deltaY >= 0 ? "north" : "south",
					abs(deltaX), deltaX >= 0 ? "west" : "east");
			mvaddstr(i, 0, monsterData);
		}
	}

	int c = getch();
	while (1) {
		if (c == KEY_UP) {
			return displayMonsterList(offset - 1 > 0 ? offset - 1 : 0, player);
		} else if (c == KEY_DOWN) {
			return displayMonsterList(offset + 22 < playerQueue->size ? offset + 1 : offset, player);
		} else if (c == 27) { //27 is ASCII for escape
			printDungeon(player);
			return 1;
		}

		c = getch();
	}
}

void teleportMode(Character *player) {
	bool fogOfWarStatus = fogOfWarActivated;
	fogOfWarActivated = false;
	int oldX = player->x;
	int oldY = player->y;
	int newX = oldX;
	int newY = oldY;
	teleportDungeon[oldY][oldX] = '*';
	printDungeon(static_cast<Player *>(player));

	char c = getchar();
	while (c != 'r' && c != 't') {
		if (c == 'y' || c == '7') {
			newX--;
			newY--;
		} else if (c == 'k' || c == '8') {
			newY--;
		} else if (c == 'u' || c == '9') {
			newX++;
			newY--;
		} else if (c == 'l' || c == '6') {
			newX++;
		} else if (c == ' ' || c == ',' || c == '5') {

		} else if (c == 'h' || c == '4') {
			newX--;
		} else if (c == 'n' || c == '3') {
			newX++;
			newY++;
		} else if (c == 'j' || c == '2') {
			newY++;
		} else if (c == 'b' || c == '1') {
			newX--;
			newY++;
		}

		if (newX > 0 && newX < 79 && newY > 0 && newY < 20) {
			teleportDungeon[oldY][oldX] = ' ';
			teleportDungeon[newY][newX] = '*';
			oldX = newX;
			oldY = newY;
		} else {
			newX = oldX;
			newY = oldY;
		}
		printDungeon(static_cast<Player *>(player));
		c = getchar();
	}

	if (c == 't') {
		teleportDungeon[newY][newX] = ' ';
		moveToSpot(player, newX, newY);
		printDungeon(static_cast<Player *>(player));
	} else {
		teleportDungeon[newY][newX] = ' ';
		moveToSpot(player, rand() % (TOTAL_WIDTH - 5) + 1, rand() % (TOTAL_HEIGHT - 4) + 1);
	}
	fogOfWarActivated = fogOfWarStatus;
}

int playerMove(Character *player) {
	char c = getchar();
	int x = player->x;
	int y = player->y;
	bool noOp = false;

	if (c == 'y' || c == '7') {
		x--;
		y--;
	} else if (c == 'k' || c == '8') {
		y--;
	} else if (c == 'u' || c == '9') {
		x++;
		y--;
	} else if (c == 'l' || c == '6') {
		x++;
	} else if (c == ' ' || c == ',' || c == '5') {

	} else if (c == 'h' || c == '4') {
		x--;
	} else if (c == 'n' || c == '3') {
		x++;
		y++;
	} else if (c == 'j' || c == '2') {
		y++;
	} else if (c == 'b' || c == '1') {
		x--;
		y++;
	} else if (c == '>' || c == '<') {

	} else if (c == 'q' || c == 'Q') {
		return -1;
	} else if (c == 'm') {
		displayMonsterList(0, static_cast<Player *>(player));
		return playerMove(player);
	} else if (c == 't') {
		teleportMode(player);
		return 1;
	} else if (c == 'f') {
		fogOfWarActivated = !fogOfWarActivated;
		printDungeon(static_cast<Player *>(player));
		playerMove(player);
		return 1;
	} else {
		noOp = true;
	}

	if ((dungeon[y][x].symbol == '<' && c == '<') || (dungeon[y][x].symbol == '>' && c == '>')) {
		int numMonsters = rand() % 15 + 10;
		int numItems = rand() % 10 + 15;

		generateRandomFloor(numMonsters, numItems);
		return 0;
	} else if (dungeon[y][x].hardness == 0 && !noOp) {
		mvaddstr(0, 0, EMPTY_ROW_TEXT);
		refresh();
		moveToSpot(player, x, y);
		return 1;
	} else if (dungeon[y][x].hardness != 0) {
		mvaddstr(0, 0, "That is not a valid move, try again");
		refresh();
	}

	playerMove(player);
	return 1;
}

void playGame() {
	while (playerIsInHeap(playerQueue) && playerQueue->head->next != NULL) {
		int status = 1;
		CharacterNode *characterNode = popCharacterNode(playerQueue);
		if (characterNode->character->symbol == '@') {
			printDungeon(static_cast<Player *>(characterNode->character));
			status = playerMove(characterNode->character);
			if (status == -1) {
				return;
			}
		} else {
			Monster *m = static_cast<Monster *>(characterNode->character);
			makeCharacterMove(m);
		}
		if (status != 0) {
			pushCharacter(playerQueue, characterNode->character,
						  characterNode->priority + characterNode->character->speed);
		}
	}

	fogOfWarActivated = false;
	printFullDungeon();

	if (playerIsInHeap(playerQueue)) {
		mvaddstr(0, 0, EMPTY_ROW_TEXT);
		mvaddstr(0, 0, "You Won!");
		refresh();
		usleep(5000000);
		return;
	} else {
		mvaddstr(0, 0, EMPTY_ROW_TEXT);
		mvaddstr(0, 0, "You Lose!");
		refresh();
		usleep(5000000);
		return;
	}
}