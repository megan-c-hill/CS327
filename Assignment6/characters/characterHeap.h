#ifndef CS327_CHARACTER_HEAP_H
#define CS327_CHARACTER_HEAP_H

#include "Character.h"

class CharacterNode {
public:
	int priority;

	Character *character;
	CharacterNode *next;

};

class CharacterHeap {
public:
	CharacterNode *head;
	int size;
};

CharacterNode *newCharacterNode(Character *character, int priority);

CharacterHeap *newCharacterHeap(CharacterNode *head);

CharacterNode *popCharacterNode(CharacterHeap *h);

void pushCharacter(CharacterHeap *h, Character *character, int priority);

void removeFromHeap(CharacterHeap *h, Character *character);

bool playerIsInHeap(CharacterHeap *h);

CharacterNode * getCharacter(CharacterHeap *h, int index);

#endif

