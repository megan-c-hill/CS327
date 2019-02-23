#ifndef CS327_CHARACTER_HEAP_H
#define CS327_CHARACTER_HEAP_H

typedef struct characterNode {
	int x;
	int y;
	int speed;
	int priority;

	struct characterNode* next;

} CharacterNode;

typedef struct characterHeap {
	CharacterNode *head;
} CharacterHeap;

CharacterNode* newCharacterNode(int x, int y, int speed, int priority);
CharacterHeap * newCharacterHeap(CharacterNode *head);
CharacterNode * popCharacterNode(CharacterHeap *h);
void pushCharacter(CharacterHeap *h, int x, int y, int speed, int priority);
int isEmptyCharacterHeap(CharacterHeap *h);

#endif

