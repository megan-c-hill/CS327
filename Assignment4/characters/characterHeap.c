// C code to implement Priority Queue using Linked List
// taken from https://www.geeksforgeeks.org/priority-queue-using-linked-list/
// pretty drastically modified, but I still feel like I should give credit just to be safe
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../shared-components.h"
#include "characterHeap.h"

CharacterNode* newCharacterNode(Character *character, int priority)
{
	CharacterNode* temp = (CharacterNode*)malloc(sizeof(CharacterNode));
	temp -> character = character;
	temp->priority = priority;
	temp->next = NULL;

	return temp;
}


CharacterHeap * newCharacterHeap(CharacterNode *head){
	CharacterHeap * temp = (CharacterHeap*)malloc(sizeof(CharacterNode));
	temp -> head = head;
	return temp;
}

CharacterNode * popCharacterNode(CharacterHeap *h)
{
	CharacterNode* data = newCharacterNode(h->head->character, h->head->priority);
	CharacterNode* temp = h -> head;
	h -> head = h->head->next;
	free(temp);
	return data;
}

void pushCharacter(CharacterHeap* h, Character* character, int p){
	CharacterNode* temp = newCharacterNode(character, p);

	if(h->head == NULL){
		h->head = temp;
		return;
	}

	CharacterNode *start = h->head;

	if (h->head->priority > p) {

		// Insert New Node before head
		temp->next = h->head;
		h->head = temp;
	}
	else {
		while (start->next != NULL && start->next->priority < p) {
			start = start->next;
		}

		temp->next = start->next;
		start->next = temp;
	}
}

int isEmptyCharacterHeap(CharacterHeap *h)
{
	return h -> head == NULL;
}

