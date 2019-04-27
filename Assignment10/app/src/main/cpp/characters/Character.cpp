//#include <stdlib.h>
//#include <stdio.h>
//#include <zconf.h>
//#include <cstring>
//#include "Character.h"
//#include "Player.h"
#include "../shared-components.h"
//#include "../distance/distance.h"
//#include "../generate-dungeon.h"
//#include "Monster.h"
//#include <iostream>
//
//static const char EMPTY_ROW_TEXT[81] = "                                                                                ";
//
//int isBoss(Character *character) {
//	if (character->symbol == '@') {
//		return 0;
//	}
//
//	return static_cast<Monster*>(character)->characteristics & 0x00000100;
//}

void initMaps() {
	for (int i = 0; i < TOTAL_HEIGHT; i++) {
		for (int j = 0; j < TOTAL_WIDTH; j++) {
			teleportDungeon[i][j] = ' ';
			characterMap[i][j] = NULL;
			objectMap[i][j] = NULL;
		}
	}
}

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
//
//void moveToSpot(Character *character, int newX, int newY) {
//	if (characterMap[newY][newX] != NULL) {
//		if (character->symbol == '@' || characterMap[newY][newX]->symbol == '@') {
//			int damage = (*character).getDamage();
//			Character *victim = characterMap[newY][newX];
//			victim->HP -= damage;
////			mvprintw(0, 0, "Damage: %d", damage);
////			refresh();
//			usleep(500000);
//			if (victim->HP <= 0) {
//				if (isBoss(victim)) {
//					bossKilled = true;
//				}
//				removeFromHeap(playerQueue, victim);
//				characterMap[victim->y][victim->x] = NULL;
//			}
//		} else {
//			Character *temp = characterMap[newY][newX];
//			temp->x = character->x;
//			temp->y = character->y;
//			characterMap[temp->y][temp->x] = temp;
//			character->x = newX;
//			character->y = newY;
//			characterMap[character->y][character->x] = character;
//		}
//	} else {
//		characterMap[character->y][character->x] = NULL;
//		character->x = newX;
//		character->y = newY;
//		characterMap[character->y][character->x] = character;
//	}
//}
//
//void tunnel(Character *character, int newX, int newY) {
//	int hardness = dungeon[newY][newX].hardness - 85;
//	if (hardness <= 0) {
//		dungeon[newY][newX].hardness = 0;
//		dungeon[newY][newX].symbol = '#';
//		moveToSpot(character, newX, newY);
//
//	} else {
//		dungeon[newY][newX].hardness = hardness;
//	}
//}
//
//
//int displayMonsterList(int offset, Character *player) {
////	initscr();
////
////	for (int i = 0; i < TOTAL_HEIGHT + 3; i++) {
////		mvaddstr(i, 0, EMPTY_ROW_TEXT);
////	}
////
////	mvaddstr(0, 0, "Monster List");
////	mvaddstr(1, 0, "------------");
////	refresh();
////
////	for (int i = 2; i < TOTAL_HEIGHT + 3; i++) {
////		CharacterNode *monster = getCharacter(playerQueue, i - 2 + offset);
////		if (monster != NULL) {
////			int deltaX = playerCharacter->x - monster->character->x;
////			int deltaY = playerCharacter->y - monster->character->y;
////			char monsterData[81];
////			sprintf(monsterData, "%c (%s) is %2d %s and %2d %s",
////					monster->character->symbol,
////					monster->character->name,
////					abs(deltaY), deltaY >= 0 ? "north" : "south",
////					abs(deltaX), deltaX >= 0 ? "west" : "east");
////			mvaddstr(i, 0, monsterData);
////		}
////	}
////
////	int c = getch();
////	while (1) {
////		if (c == KEY_UP) {
////			return displayMonsterList(offset - 1 > 0 ? offset - 1 : 0, player);
////		} else if (c == KEY_DOWN) {
////			return displayMonsterList(offset + 22 < playerQueue->size ? offset + 1 : offset, player);
////		} else if (c == 27) { //27 is ASCII for escape
////			printDungeon(static_cast<Player *>(player));
////			return 1;
////		}
////
////		c = getch();
////	}
//return 1;
//}
//
void playGame() {
//	while (playerIsInHeap(playerQueue) && !bossKilled) {
//		int status = 1;
//		CharacterNode *characterNode = popCharacterNode(playerQueue);
//		if (characterNode->character->symbol == '@') {
//			printDungeon(static_cast<Player *>(characterNode->character));
//			status = playerMove(static_cast<Player *>(characterNode->character));
//			if (status == -1) {
//				return;
//			}
//		} else {
//			Monster *m = static_cast<Monster *>(characterNode->character);
//			makeCharacterMove(m);
//		}
//		if (status != 0) {
//			pushCharacter(playerQueue, characterNode->character,
//						  characterNode->priority + characterNode->character->speed);
//		}
//	}
//
//	fogOfWarActivated = false;
//	printFullDungeon();
//
//	if (playerIsInHeap(playerQueue)) {
////		mvaddstr(0, 0, EMPTY_ROW_TEXT);
////		mvaddstr(0, 0, "You Won!");
////		refresh();
////		usleep(5000000);
//		return;
//	} else {
////		mvaddstr(0, 0, EMPTY_ROW_TEXT);
////		mvaddstr(0, 0, "You Lose!");
////		refresh();
////		usleep(5000000);
//		return;
//	}
}
//
//void Character::displayCharacter() {
////	initscr();
////
////	for (int i = 0; i < TOTAL_HEIGHT + 3; i++) {
////		mvaddstr(i, 0, EMPTY_ROW_TEXT);
////	}
////
////	mvaddstr(0, 0, "Character Details");
////	mvaddstr(1, 0, "-----------------");
////
////	mvprintw(2, 0, "NAME: %s", name);
////	mvprintw(3, 0, "DESC: ");
////	int index = 4;
////
////	for (int i = 0; i < 100 && strcmp(description[i], "NONE") != 0; i++) {
////		mvprintw(index, 0, description[i]);
////		index++;
////	}
////	index++;
////	mvprintw(index, 0, "SYMB: %c", symbol);
////	mvprintw(index + 1, 0, "COLOR: %d", color);
////	mvprintw(index + 2, 0, "HP: %d", HP);
////	mvprintw(index + 3, 0, "DAMAGE: ");
////	for (int i = 0; i < damage.size(); i++) {
////		mvprintw(index + 3, 7 + 8 * i, "%s", damage.at(i).print().c_str());
////	}
////
////	mvprintw(index + 4, 0, "SPEED: %d", speed);
////	mvprintw(index + 5, 0, "POSITION: (%d, %d)", x, y);
////	refresh();
//}
//
//int Character::getDamage() {
//	int totalDamage = 0;
//	for (int i = 0; i < damage.size(); i++) {
//		totalDamage += damage.at(i).getValue();
//	}
//	return totalDamage;
//}
