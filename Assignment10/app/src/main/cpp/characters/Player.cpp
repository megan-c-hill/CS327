#include "Player.h"
#include "Monster.h"
#include "../shared-components.h"
#include "../generate-dungeon.h"
#include <cstring>
#include <unordered_map>
#include <algorithm>

//static const char EMPTY_ROW_TEXT[81] = "                                                                                ";

static unordered_map<string, int> const equipmentTypeIndexMap = {
		{"WEAPON",  0},
		{"OFFHAND", 1},
		{"RANGED",  2},
		{"ARMOR",   3},
		{"HELMET",  4},
		{"CLOAK",   5},
		{"GLOVES",  6},
		{"BOOTS",   7},
		{"AMULET",  8},
		{"LIGHT",   9},
		{"RING",    10}
};

Player *generatePlayerCharacter() {
	Player *pc = (Player *) malloc(sizeof(Player));

	pc->speed = 10;
	strcpy(pc->description[0], "This is you!");
	for(int i = 1; i < 100; i++) {
		strcpy(pc->description[i], "NONE");
	}
	pc->HP = 100;
//	pc->damage.push_back(Dice(0, 1, 4));
	pc->symbol = '@';
	strcpy(pc->name, "You");
//	pc->color = COLOR_BLUE;

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
			if(playerQueue == NULL) {
				pc->x = x;
				pc->y = y;
				characterMap[y][x] = pc;
				CharacterNode *head = newCharacterNode(pc, 0);
				playerQueue = newCharacterHeap(head);
				playerCharacter = pc;
			} else {
				playerCharacter->x = x;
				playerCharacter->y = y;
				characterMap[y][x] = playerCharacter;
				CharacterNode *head = newCharacterNode(playerCharacter, 0);
				playerQueue = newCharacterHeap(head);
			}
				isDone = true;
		}
	}
}

void pickup(Player *player) {
	if (objectMap[player->y][player->x] != NULL) {
		for (int i = 0; i < 10; i++) {
			if (player->inventory[i] == NULL) {
				player->inventory[i] = objectMap[player->y][player->x];
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

//void playerMoveToSpot(Player *character, int newX, int newY) {
//	moveToSpot(character, newX, newY);
//	pickup(character);
//}

void teleportMode(Player *player) {
//	bool fogOfWarStatus = fogOfWarActivated;
//	fogOfWarActivated = false;
//	int oldX = player->x;
//	int oldY = player->y;
//	int newX = oldX;
//	int newY = oldY;
//	teleportDungeon[oldY][oldX] = '*';
//	printDungeon(player);
//
//	char c = getchar();
//	while (c != 'r' && c != 't') {
//		if (c == 'y' || c == '7') {
//			newX--;
//			newY--;
//		} else if (c == 'k' || c == '8') {
//			newY--;
//		} else if (c == 'u' || c == '9') {
//			newX++;
//			newY--;
//		} else if (c == 'l' || c == '6') {
//			newX++;
//		} else if (c == ' ' || c == ',' || c == '5') {
//
//		} else if (c == 'h' || c == '4') {
//			newX--;
//		} else if (c == 'n' || c == '3') {
//			newX++;
//			newY++;
//		} else if (c == 'j' || c == '2') {
//			newY++;
//		} else if (c == 'b' || c == '1') {
//			newX--;
//			newY++;
//		}
//
//		if (newX > 0 && newX < 79 && newY > 0 && newY < 20) {
//			teleportDungeon[oldY][oldX] = ' ';
//			teleportDungeon[newY][newX] = '*';
//			oldX = newX;
//			oldY = newY;
//		} else {
//			newX = oldX;
//			newY = oldY;
//		}
//		printDungeon(player);
//		c = getchar();
//	}
//
//	if (c == 't') {
//		teleportDungeon[newY][newX] = ' ';
//		playerMoveToSpot(player, newX, newY);
//		printDungeon(player);
//	} else {
//		teleportDungeon[newY][newX] = ' ';
//		moveToSpot(player, rand() % (TOTAL_WIDTH - 5) + 1, rand() % (TOTAL_HEIGHT - 4) + 1);
//	}
//	fogOfWarActivated = fogOfWarStatus;
}

void targetMode(Player *player) {
//	bool fogOfWarStatus = fogOfWarActivated;
//	fogOfWarActivated = false;
//	int oldX = player->x;
//	int oldY = player->y;
//	int newX = oldX;
//	int newY = oldY;
//	teleportDungeon[oldY][oldX] = '*';
//	printDungeon(player);
//
//	char c = getchar();
//	while (c != 't' && c!=27) {
//		if (c == 'y' || c == '7') {
//			newX--;
//			newY--;
//		} else if (c == 'k' || c == '8') {
//			newY--;
//		} else if (c == 'u' || c == '9') {
//			newX++;
//			newY--;
//		} else if (c == 'l' || c == '6') {
//			newX++;
//		} else if (c == ' ' || c == ',' || c == '5') {
//
//		} else if (c == 'h' || c == '4') {
//			newX--;
//		} else if (c == 'n' || c == '3') {
//			newX++;
//			newY++;
//		} else if (c == 'j' || c == '2') {
//			newY++;
//		} else if (c == 'b' || c == '1') {
//			newX--;
//			newY++;
//		}
//
//		if (newX > 0 && newX < 79 && newY > 0 && newY < 20) {
//			teleportDungeon[oldY][oldX] = ' ';
//			teleportDungeon[newY][newX] = '*';
//			oldX = newX;
//			oldY = newY;
//		} else {
//			newX = oldX;
//			newY = oldY;
//		}
//		printDungeon(player);
//		c = getchar();
//	}
//
//	if (c == 't') {
//		teleportDungeon[newY][newX] = ' ';
//		if(characterMap[newY][newX] != NULL) {
//			(*characterMap[newY][newX]).displayCharacter();
//
//			while(getch() != 27);
//		}
//	}
//
//	teleportDungeon[newY][newX] = ' ';
//	fogOfWarActivated = fogOfWarStatus;
//	printDungeon(player);
}

int playerMove(Player *player) {
//	char c = getchar();
//	int x = player->x;
//	int y = player->y;
//	bool noOp = false;
//
//	if (c == 'y' || c == '7') {
//		x--;
//		y--;
//	} else if (c == 'k' || c == '8') {
//		y--;
//	} else if (c == 'u' || c == '9') {
//		x++;
//		y--;
//	} else if (c == 'l' || c == '6') {
//		x++;
//	} else if (c == ' ' || c == ',' || c == '5') {
//
//	} else if (c == 'h' || c == '4') {
//		x--;
//	} else if (c == 'n' || c == '3') {
//		x++;
//		y++;
//	} else if (c == 'j' || c == '2') {
//		y++;
//	} else if (c == 'b' || c == '1') {
//		x--;
//		y++;
//	} else if (c == '>' || c == '<') {
//
//	} else if (c == 'q' || c == 'Q') {
//		return -1;
//	} else if (c == 'm') {
//		displayMonsterList(0, player);
//		return playerMove(player);
//	} else if (c == 'g') {
//		teleportMode(player);
//		return 1;
//	} else if (c == 'i') {
//		(*player).displayInventory();
//		return playerMove(player);
//	} else if (c == 'e') {
//		(*player).displayEquipment();
//		return playerMove(player);
//	} else if (c == 'w') {
//		(*player).wearItem();
//		return playerMove(player);
//	} else if (c == 't') {
//		(*player).takeOffEquipment();
//		return playerMove(player);
//	} else if (c == 'x') {
//		(*player).expungeItem();
//		return playerMove(player);
//	} else if (c == 'd') {
//		(*player).dropItem();
//		return playerMove(player);
//	} else if (c == 'I') {
//		(*player).inspectItem();
//		return playerMove(player);
//	} else if (c == 'L') {
//		targetMode(player);
//		return playerMove(player);
//	} else if (c == 'f') {
//		fogOfWarActivated = !fogOfWarActivated;
//		printDungeon(player);
//		playerMove(player);
//		return 1;
//	} else {
//		noOp = true;
//	}
//
//	if ((dungeon[y][x].symbol == '<' && c == '<') || (dungeon[y][x].symbol == '>' && c == '>')) {
//		int numMonsters = rand() % 15 + 10;
//		int numItems = rand() % 10 + 15;
//
//		generateRandomFloor(numMonsters, numItems);
//		return 0;
//	} else if (dungeon[y][x].hardness == 0 && !noOp) {
////		mvaddstr(0, 0, EMPTY_ROW_TEXT);
////		refresh();
//		playerMoveToSpot(player, x, y);
//		return 1;
//	} else if (dungeon[y][x].hardness != 0) {
////		mvaddstr(0, 0, "That is not a valid move, try again");
////		refresh();
//	}
//
//	playerMove(player);
randomMove(player);
	return 1;
}

void Player::showInventory() {
//	initscr();
//
//	for (int i = 0; i < TOTAL_HEIGHT + 3; i++) {
//		mvaddstr(i, 0, EMPTY_ROW_TEXT);
//	}
//
//	mvaddstr(0, 0, "Player Inventory");
//	mvaddstr(1, 0, "----------------");
//
//	for (int i = 0; i < 10; i++) {
//		char itemData[81];
//		sprintf(itemData, "%c) %s",
//				48 + i,
//				inventory[i] ? inventory[i]->name : "");
//		mvaddstr(i + 3, 0, itemData);
//	}
//	refresh();
}

void Player::showEquipment() {
//	initscr();
//
//	for (int i = 0; i < TOTAL_HEIGHT + 3; i++) {
//		mvaddstr(i, 0, EMPTY_ROW_TEXT);
//	}
//
//	mvaddstr(0, 0, "Player Equipment");
//	mvaddstr(1, 0, "----------------");
//
//	for (int i = 0; i < 12; i++) {
//		char itemData[81];
//		sprintf(itemData, "%c) %s",
//				97 + i,
//				equipment[i] ? equipment[i]->name : "");
//		mvaddstr(i + 3, 0, itemData);
//	}
//	refresh();
}

void Player::displayInventory() {
//	showInventory();
//
//	while (getch() != 27);
//
//	printDungeon(this);
}

void Player::displayEquipment() {
//	showEquipment();
//
//	while (getch() != 27);
//
//	printDungeon(this);
}

void Player::wearItem() {
//	showInventory();
//
//	int c = getch();
//
//	if (inventory[c - 48] != NULL) {
//		int equipmentIndex = equipmentTypeIndexMap.at(inventory[c - 48]->type[0]);
//		if(equipmentIndex == 10 && equipment[10] != NULL) {
//			equipmentIndex = 11;
//		}
//		speed += inventory[c-48]->speed;
//		damage.push_back(inventory[c-48]->damage);
//
//		Object *temp = equipment[equipmentIndex];
//		if(temp != NULL) {
//			speed -= temp->speed;
//			int pos = 0;
//			for (int j = 0; j<damage.size(); j++) {
//				if(damage.at(j).base == temp->damage.base && damage.at(j).sides == temp->damage.sides && damage.at(j).dice == temp->damage.dice) {
//					pos = j;
//				}
//			}
//			damage.erase(damage.begin() + pos);
//		}
//		equipment[equipmentIndex] = inventory[c - 48];
//		inventory[c - 48] = temp;
//
//		showEquipment();
//		while (getch() != 27);
//	}
//
//	printDungeon(this);
}

void Player::takeOffEquipment() {
//	showEquipment();
//
//	int c = getch();
//
//	if (equipment[c - 97] != NULL) {
//		for (int i = 0; i < 10; i++) {
//			if (inventory[i] == NULL) {
//				inventory[i] = equipment[c - 97];
//				speed -= equipment[c-97]->speed;
//				int pos;
//				for (int j = 0; j<damage.size(); j++) {
//					if(damage.at(j).base == equipment[c-97]->damage.base && damage.at(j).sides == equipment[c-97]->damage.sides && damage.at(j).dice == equipment[c-97]->damage.dice) {
//						pos = j;
//					}
//				}
//				damage.erase(damage.begin() + pos);
//				equipment[c - 97] = NULL;
//				showInventory();
//
//				while (getch() != 27);
//				break;
//			}
//		}
//	}
//
//	printDungeon(this);
}

void Player::expungeItem() {
//	showInventory();
//
//	int c = getch();
//
//	free(inventory[c - 48]);
//	inventory[c - 48] = NULL;
//
//	showInventory();
//
//	while (getch() != 27);
//
//	printDungeon(this);
}

void Player::dropItem() {
//	showInventory();
//
//	int c = getch();
//
//	if (inventory[c - 48] != NULL && objectMap[y][x] == NULL) {
//		objectMap[y][x] = inventory[c - 48];
//		inventory[c - 48] = NULL;
//
//		showInventory();
//
//		while (getch() != 27);
//
//	}
//
//	printDungeon(this);
}

void Player::inspectItem() {
//	showInventory();
//
//	int c = getch();
//
//	if(inventory[c-48] != NULL) {
//		(*inventory[c-48]).showDetails();
//
//		while (getch() != 27);
//	}
//
//	printDungeon(this);
}
