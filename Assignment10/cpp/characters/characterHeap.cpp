// C code to implement Priority Queue using Linked List
// taken from https://www.geeksforgeeks.org/priority-queue-using-linked-list/
// pretty drastically modified, but I still feel like I should give credit just to be safe
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../shared-components.h"
#include "characterHeap.h"

CharacterNode *newCharacterNode(Character *character, int priority) {
	CharacterNode *temp = (CharacterNode *) malloc(sizeof(CharacterNode));
	temp->character = character;
	temp->priority = priority;
	temp->next = NULL;

	return temp;
}


CharacterHeap *newCharacterHeap(CharacterNode *head) {
	CharacterHeap *temp = (CharacterHeap *) malloc(sizeof(CharacterNode));
	temp->head = head;
	temp->size = 1;
	return temp;
}

CharacterNode *popCharacterNode(CharacterHeap *h) {
	CharacterNode *data = newCharacterNode(h->head->character, h->head->priority);
	CharacterNode *temp = h->head;
	h->head = h->head->next;
	h->size--;
	free(temp);
	return data;
}

void pushCharacter(CharacterHeap *h, Character *character, int p) {
	CharacterNode *temp = newCharacterNode(character, p);
	h->size++;

	if (h->head == NULL) {
		h->head = temp;
		return;
	}

	CharacterNode *start = h->head;

	if (h->head->priority > p) {

		// Insert New Node before head
		temp->next = h->head;
		h->head = temp;
	} else {
		while (start->next != NULL && start->next->priority < p) {
			start = start->next;
		}

		temp->next = start->next;
		start->next = temp;
	}
}

bool isEqual(Character *character1, Character *character2) {
	bool xMatch = character1->x == character2->x;
	bool yMatch = character1->y == character2->y;
	bool symbolMatch = character1->symbol == character2->symbol;
	bool speedMatch = character1->speed == character2->speed;

	return xMatch && yMatch && symbolMatch && speedMatch;
}

/**
 * Disclaimer: Assumes the character is in the heap and will mess up pretty bad if it isn't
 * @param h
 * @param character
 */
void removeFromHeap(CharacterHeap *h, Character *character) {
	h->size--;
	if (isEqual(h->head->character, character)) {
		h->head = h->head->next;
		return;
	}
	CharacterNode *temp = h->head;
	while (!isEqual(temp->next->character, character)) {
		temp = temp->next;
	}

	temp->next = temp->next->next;
}

bool playerIsInHeap(CharacterHeap *h) {
	CharacterNode *temp = h->head;

	while (temp != NULL) {
		if (isEqual(temp->character, playerCharacter)) {
			return true;
		}
		temp = temp->next;
	}

	return false;
}

CharacterNode *getCharacter(CharacterHeap *h, int index) {
	CharacterNode *temp = h->head;
	for (int i = 0; i < index && temp != NULL; i++) {
		temp = temp->next;
	}

	return temp;
}
