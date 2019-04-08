#ifndef CS327_MONSTER_H
#define CS327_MONSTER_H

#include "../descriptions/dice.h"
#include "Character.h"

class Monster : public Character {
public:
	char description[100][78];
	int HP;
	Dice damage;
	int rarity;
	int characteristics;
	uint8_t knownPlayerX;
	uint8_t knownPlayerY;
};

Monster *generateMonsterCharacter();

void placeMonsters(int numMonsters);

void makeCharacterMove(Monster *m);

#endif
