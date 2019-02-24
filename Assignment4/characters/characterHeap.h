#ifndef CS327_CHARACTER_HEAP_H
#define CS327_CHARACTER_HEAP_H

#include "monster.h"

typedef struct characterNode {
	int priority;

	Character* character;
	struct characterNode* next;

} CharacterNode;

typedef struct characterHeap {
	CharacterNode *head;
} CharacterHeap;

CharacterNode* newCharacterNode(Character* character, int priority);
CharacterHeap * newCharacterHeap(CharacterNode *head);
CharacterNode * popCharacterNode(CharacterHeap *h);
void pushCharacter(CharacterHeap *h, Character* character, int priority);
int isEmptyCharacterHeap(CharacterHeap *h);
void removeFromHeap(CharacterHeap *h, Character* character);
bool isInHeap(CharacterHeap *h, Character* character);

#endif

