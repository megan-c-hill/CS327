#ifndef CS327_PATH_FINDING_HEAP_H
#define CS327_PATH_FINDING_HEAP_H

#include "../shared-components.h"

class PathFindingNode {
public:
	int x;
	int y;

	PathFindingNode *next;

};

class PathFindingHeap {
public:
	PathFindingNode *head;
};

PathFindingNode *newPathFindingNode(int x, int y);

PathFindingHeap *newPathFindingHeap(PathFindingNode *head);

PathFindingNode *pop(PathFindingHeap *h);

void push(PathFindingHeap *h, int x, int y, DistancePosition distanceArr[TOTAL_HEIGHT][TOTAL_WIDTH]);

int isEmpty(PathFindingHeap *h);

#endif
