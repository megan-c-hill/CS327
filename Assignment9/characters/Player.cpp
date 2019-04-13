#include "Player.h"
#include <ncurses.h>
#include "../shared-components.h"
#include "../generate-dungeon.h"

static const char EMPTY_ROW_TEXT[81] = "                                                                                ";

Player *generatePlayerCharacter() {
	Player *pc = (Player *) malloc(sizeof(Player));

	pc->speed = 10;
	pc->HP = 100;
	pc->damage = Dice(0, 1, 4);
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

void pickup(Player *player) {
	if(objectMap[player->y][player->x] != NULL) {
		for(int i = 0; i < 10; i++) {
			if(player->inventory[i] == NULL) {
				player->inventory[i] = objectMap[player->x][player->y];
				objectMap[player->y][player->x] = NULL;
				return;
			}
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

void playerMoveToSpot(Player *character, int newX, int newY) {
	characterMap[character->y][character->x] = NULL;
	character->x = newX;
	character->y = newY;
	if (characterMap[newY][newX] != NULL) {
		removeFromHeap(playerQueue, characterMap[newY][newX]);
	}
	characterMap[character->y][character->x] = character;
	pickup(character);
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

int playerMove(Player *player) {
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
		playerMoveToSpot(static_cast<Player *>(player), x, y);
		return 1;
	} else if (dungeon[y][x].hardness != 0) {
		mvaddstr(0, 0, "That is not a valid move, try again");
		refresh();
	}

	playerMove(player);
	return 1;
}
