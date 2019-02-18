#ifndef CS327_HEAP_H
#define CS327_HEAP_H

// Node
typedef struct node {
	int x;
	int y;

	struct node* next;

} Node;

typedef struct heap {
	Node *head;
} Heap;

Node* newNode(int x, int y);
Heap * newHeap(Node *head);
Node * pop(Heap *h);
void push(Heap *h, int x, int y, struct distancePosition distanceArr[TOTAL_HEIGHT][TOTAL_WIDTH]);
int isEmpty(Heap *h);

#endif //CS327_HEAP_H
