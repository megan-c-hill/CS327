// C code to implement Priority Queue using Linked List
// taken from https://www.geeksforgeeks.org/priority-queue-using-linked-list/
// pretty drastically modified, but I still feel like I should give credit just to be safe
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../shared-components.h"
#include "pathFindingHeap.h"

// Function to Create A New Node 
PathFindingNode* newPathFindingNode(int x, int y)
{
	PathFindingNode* temp = (PathFindingNode*)malloc(sizeof(PathFindingNode));
	temp->x = x;
	temp->y = y;
	temp->next = NULL;

	return temp;
}


PathFindingHeap * newPathFindingHeap(PathFindingNode *head){
	PathFindingHeap * temp = (PathFindingHeap*)malloc(sizeof(PathFindingNode));
	temp -> head = head;
	return temp;
}

// Removes the element with the 
// highest priority form the list 
PathFindingNode * pop(PathFindingHeap *h)
{
	PathFindingNode* data = newPathFindingNode(h->head->x, h->head->y);
	PathFindingNode* temp = h -> head;
	h -> head = h->head->next;
	free(temp);
	return data;
}

// Function to push according to priority 
void push(PathFindingHeap *h, int x, int y, struct distancePosition distanceArr[TOTAL_HEIGHT][TOTAL_WIDTH])
{
	// Create new Node
	PathFindingNode* temp = newPathFindingNode(x, y);
	if(h->head == NULL){
		h->head = temp;
		return;
	}
	PathFindingNode* start = h -> head;


	// Special Case: The head of list has lesser
	// priority than new PathFindingNode. So insert new
	// PathFindingNode before head PathFindingNode and change head PathFindingNode.
	if (distanceArr[h->head->y][h->head->x].distance > distanceArr[y][x].distance) {
		// Insert New Node before head
		temp->next = h -> head;
		h -> head = temp;
	}
	else {

		// Traverse the list and find a
		// position to insert new PathFindingNode
		while (start->next != NULL && distanceArr[start->next->y][start->next->x].distance < distanceArr[y][x].distance) {
			start = start->next;
		}

		// Either at the ends of the list
		// or at required position
		temp->next = start->next;
		start->next = temp;
	}
}

// Function to check is list is empty 
int isEmpty(PathFindingHeap *h)
{
	return h -> head == NULL;
}