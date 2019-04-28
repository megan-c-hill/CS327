#include "Monster.h"
#include <unordered_map>
#include "../distance/distance.h"
#include "../shared-components.h"
#include <iostream>
#include <cstring>
#include <zconf.h>

using namespace std;

#define NPC_SMART    0x00000001
#define NPC_TELE    0x00000002
#define NPC_TUNNEL    0x00000004
#define NPC_ERRATIC    0x00000008
#define NPC_PASS    0x00000010
#define NPC_PICKUP    0x00000020
#define NPC_DESTROY    0x00000040
#define NPC_UNIQ    0x0000080
#define NPC_BOSS    0x00000100


static unordered_map<string, int> const abilMap = {
		{"SMART",   NPC_SMART},
		{"TELE",    NPC_TELE},
		{"TUNNEL",  NPC_TUNNEL},
		{"ERRATIC", NPC_ERRATIC},
		{"PASS",    NPC_PASS},
		{"PICKUP",  NPC_PICKUP},
		{"DESTROY", NPC_DESTROY},
		{"UNIQ",    NPC_UNIQ},
		{"BOSS",    NPC_BOSS},
		{"NONE", 0}
};

int hasCharacteristic(Monster *character, int characteristic) {
	return character->characteristics & characteristic;
}

int parseCharacteristics(char abilities[10][8]) {
	int characteristics = 0;
	for (int i = 0; i < 10 && strcmp(abilities[i], "NONE") != 0; i++) {
		characteristics += abilMap.at(abilities[i]);
	}
	return characteristics;
}

Monster *generateMonsterCharacter() {
	MonsterDescription md;
	bool hasMonster = false;
	int index = 1;
	while (!hasMonster) {
		int prob = rand() % 100 + 1;
		index = rand() % monsters.size();

		md = monsters.at(index);
		if (prob < md.rarity) {
			hasMonster = true;
		}
	}

	Monster *npm = (Monster *) malloc(sizeof(Monster));
	npm->characteristics = parseCharacteristics(md.abilities);
	strcpy(npm->name, md.name);
	npm->symbol = md.symbol;
	npm->speed = md.speed.getValue();
	npm->color = md.color[0];
	for (int i = 0; i < 100; i++) {
		strcpy(npm->description[i], md.description[i]);
	}
	npm->HP = md.HP.getValue();
//	npm->damage.push_back(md.damage); TODO: figure out why sigsegv
	npm->rarity = md.rarity;

	if (hasCharacteristic(npm, NPC_UNIQ)) {
		monsters.erase(monsters.begin() + index);
	}

	return npm;
};

void placeMonsters(int numMonsters) {
	int counter = 0;
	uint8_t x, y;
	int infiniteCounter = 0;
	while (counter < numMonsters) {
		x = rand() % (TOTAL_WIDTH - 2) + 1;
		y = rand() % (TOTAL_HEIGHT - 2) + 1;

		if (dungeon[y][x].hardness == 0 && characterMap[y][x] == NULL) {
			Monster *monster = generateMonsterCharacter();
			monster->x = x;
			monster->y = y;
			characterMap[y][x] = monster;
			pushCharacter(playerQueue, monster, 0);
			counter++;
			infiniteCounter = 0;
		} else if (infiniteCounter > 2000) {
			break;
		} else {
			infiniteCounter++;
		}
	}
}

bool pcIsVisible(Monster *character) {
//	int xDistance = abs(character->x - playerCharacter->x);
//	int yDistance = abs(character->y - playerCharacter->y);
//
//	if (hasCharacteristic(character, NPC_TELE)) {
//		character->knownPlayerX = playerCharacter->x;
//		character->knownPlayerY = playerCharacter->y;
//	}
//
//	int totalDistanceSquared = xDistance * xDistance + yDistance * yDistance;
//	if (totalDistanceSquared <= 25) {
//		if (hasCharacteristic(character, NPC_SMART)) {
//			character->knownPlayerX = playerCharacter->x;
//			character->knownPlayerY = playerCharacter->y;
//		}
//		return true;
//	}
//	return false;
return true;
}

void goTowardsPC(Monster *character) {
//	int xDirection = playerCharacter->x - character->x == 0 ? 0 : (playerCharacter->x - character->x) /
//																  abs(playerCharacter->x - character->x);
//	int yDirection = playerCharacter->y - character->y == 0 ? 0 : (playerCharacter->y - character->y) /
//																  abs(playerCharacter->y - character->y);
//	int newX = character->x + xDirection;
//	int newY = character->y + yDirection;
//
//	if (dungeon[newY][newX].hardness == 0) {
//		moveToSpot(character, newX, newY);
//	} else if (hasCharacteristic(character, NPC_TELE) && dungeon[newY][newX].hardness != 255) {
//		tunnel(character, newX, newY);
//	}
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
//	} else if (hasCharacteristic(character, NPC_TELE) && dungeon[newY][newX].hardness != 255) {
//		tunnel(character, newX, newY);
	} else {
		randomMove(character);
	}
}

void useMap(Character *character, DistancePosition distanceMap[TOTAL_HEIGHT][TOTAL_WIDTH]) {
//	int bestX = character->x;
//	int bestY = character->y;
//
//	for (int i = -1; i <= 1; i++) {
//		for (int j = -1; j <= 1; j++) {
//			if (distanceMap[character->y + i][character->x + j].distance < distanceMap[bestY][bestX].distance) {
//				bestX = character->x + j;
//				bestY = character->y + i;
//			}
//		}
//	}
//
//	if (dungeon[bestY][bestX].hardness != 0) {
//		tunnel(character, bestX, bestY);
//	} else {
//		moveToSpot(character, bestX, bestY);
//	}

}

void makeCharacterMove(Monster *character) {
//	if (hasCharacteristic(character, NPC_ERRATIC) && rand() % 2 == 1) {
		randomMove(character);
//	} else if (hasCharacteristic(character, NPC_SMART)) {
//		pcIsVisible(character);
//		if (character->knownPlayerX != 0) {
//			if (hasCharacteristic(character, NPC_TUNNEL)) {
//				tunnelingDistance(character->knownPlayerX, character->knownPlayerY);
//				useMap(character, tunnelDistance);
//			} else {
//				nonTunnelingDistance(character->knownPlayerX, character->knownPlayerY);
//				useMap(character, nonTunnelDistance);
//			}
//		}
//	} else if (pcIsVisible(character) || hasCharacteristic(character, NPC_TELE)) {
//		goTowardsPC(character);
//	} // else do nothing
}
