// C code to implement Priority Queue using Linked List
// taken from https://www.geeksforgeeks.org/priority-queue-using-linked-list/
// pretty drastically modified, but I still feel like I should give credit just to be safe
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "shared-components.h"
#include "heap.h"

// Function to Create A New Node 
Node* newNode(int x, int y)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->x = x;
	temp->y = y;
	temp->next = NULL;

	return temp;
}


Heap * newHeap(Node *head){
	Heap * temp = (Heap*)malloc(sizeof(Node));
	temp -> head = head;
	return temp;
}

// Removes the element with the 
// highest priority form the list 
Node * pop(Heap *h)
{
	Node* data = h->head;
	Node* temp = h -> head;
	h -> head = h->head->next;
	free(temp);
	return data;
}

// Function to push according to priority 
void push(Heap *h, int x, int y, struct distancePosition distanceArr[TOTAL_HEIGHT][TOTAL_WIDTH])
{
	// Create new Node
	Node* temp = newNode(x, y);
	if(h->head == NULL){
		h->head = temp;
		return;
	}
	Node* start = h -> head;


	// Special Case: The head of list has lesser
	// priority than new node. So insert new
	// node before head node and change head node.
	if (distanceArr[h->head->y][h->head->x].distance > distanceArr[y][x].distance) {
		// Insert New Node before head
		temp->next = h -> head;
		h -> head = temp;
	}
	else {

		// Traverse the list and find a
		// position to insert new node
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
int isEmpty(Heap *h)
{
	return h -> head == NULL;
}