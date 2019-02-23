#ifndef CS327_HEAP_H
#define CS327_HEAP_H

// Node
typedef struct pathFindingNode {
	int x;
	int y;

	struct pathFindingNode* next;

} PathFindingNode;

typedef struct pathFindingHeap {
	PathFindingNode *head;
} PathFindingHeap;

PathFindingNode* newPathFindingNode(int x, int y);
PathFindingHeap * newPathFindingHeap(PathFindingNode *head);
PathFindingNode * pop(PathFindingHeap *h);
void push(PathFindingHeap *h, int x, int y, struct distancePosition distanceArr[TOTAL_HEIGHT][TOTAL_WIDTH]);
int isEmpty(PathFindingHeap *h);

#endif //CS327_HEAP_H
