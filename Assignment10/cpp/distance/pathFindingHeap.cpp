// C code to implement Priority Queue using Linked List
// taken from https://www.geeksforgeeks.org/priority-queue-using-linked-list/
// pretty drastically modified, but I still feel like I should give credit just to be safe
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../shared-components.h"
#include "pathFindingHeap.h"

PathFindingNode *newPathFindingNode(int x, int y) {
	PathFindingNode *temp = (PathFindingNode *) malloc(sizeof(PathFindingNode));
	temp->x = x;
	temp->y = y;
	temp->next = NULL;

	return temp;
}


PathFindingHeap *newPathFindingHeap(PathFindingNode *head) {
	PathFindingHeap *temp = (PathFindingHeap *) malloc(sizeof(PathFindingNode));
	temp->head = head;
	return temp;
}

PathFindingNode *pop(PathFindingHeap *h) {
	PathFindingNode *data = newPathFindingNode(h->head->x, h->head->y);
	PathFindingNode *temp = h->head;
	h->head = h->head->next;
	free(temp);
	return data;
}

void push(PathFindingHeap *h, int x, int y, DistancePosition distanceArr[TOTAL_HEIGHT][TOTAL_WIDTH]) {
	PathFindingNode *temp = newPathFindingNode(x, y);
	if (h->head == NULL) {
		h->head = temp;
		return;
	}
	PathFindingNode *start = h->head;


	if (distanceArr[h->head->y][h->head->x].distance > distanceArr[y][x].distance) {
		temp->next = h->head;
		h->head = temp;
	} else {
		while (start->next != NULL && distanceArr[start->next->y][start->next->x].distance < distanceArr[y][x].distance) {
			start = start->next;
		}

		temp->next = start->next;
		start->next = temp;
	}
}

int isEmpty(PathFindingHeap *h) {
	return h->head == NULL;
}