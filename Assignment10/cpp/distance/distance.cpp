#include "../shared-components.h"
#include "pathFindingHeap.h"
#include <stdio.h>

uint8_t MAX_INT = 255;

void initNonTunnelArray() {
	for (int i = 0; i < TOTAL_HEIGHT; i++) {
		for (int j = 0; j < TOTAL_WIDTH; j++) {
			if (i == 0 || i == TOTAL_HEIGHT - 1) {
				nonTunnelDistance[i][j].symbol = '-';
			} else if (j == 0 || j == TOTAL_WIDTH - 1) {
				nonTunnelDistance[i][j].symbol = '|';
			} else {
				if (dungeon[i][j].hardness == 0) {
					nonTunnelDistance[i][j].symbol = 'X';
				} else {
					nonTunnelDistance[i][j].symbol = ' ';
				}
			}
			nonTunnelDistance[i][j].distance = MAX_INT;
		}
	}
}

void initTunnelArray() {
	for (int i = 0; i < TOTAL_HEIGHT; i++) {
		for (int j = 0; j < TOTAL_WIDTH; j++) {
			if (i == 0 || i == TOTAL_HEIGHT - 1) {
				tunnelDistance[i][j].symbol = '-';
			} else if (j == 0 || j == TOTAL_WIDTH - 1) {
				tunnelDistance[i][j].symbol = '|';
			} else {
				tunnelDistance[i][j].symbol = 'X';
			}
			tunnelDistance[i][j].distance = MAX_INT;
		}
	}
}

void shortestPath(DistancePosition distanceArr[TOTAL_HEIGHT][TOTAL_WIDTH], int isTunnelable, int x, int y) {
	distanceArr[y][x].distance = 0;
	distanceArr[y][x].symbol = '@';
	PathFindingNode *playerPosition = newPathFindingNode(x, y);
	PathFindingHeap *h = newPathFindingHeap(playerPosition);

	while (!isEmpty(h)) {
		PathFindingNode *parent = pop(h);
		int parentX = parent->x;
		int parentY = parent->y;

		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				int newY = parentY + i;
				int newX = parentX + j;
				if (newX > 0 && newX < TOTAL_WIDTH - 1 && newY > 0 && newY < TOTAL_HEIGHT - 1) {
					int newDistance = distanceArr[parentY][parentX].distance + (dungeon[parentY][parentX].hardness / 85) + 1;
					if ((dungeon[newY][newX].hardness == 0 || isTunnelable) && newDistance < distanceArr[newY][newX].distance) {
						distanceArr[newY][newX].distance = newDistance;
						distanceArr[newY][newX].symbol = newDistance % 10 + '0';
						push(h, newX, newY, distanceArr);
					}
				}
			}
		}

	}
}

void nonTunnelingDistance(int x, int y) {
	initNonTunnelArray();
	shortestPath(nonTunnelDistance, 0, x, y);

}

void tunnelingDistance(int x, int y) {
	initTunnelArray();
	shortestPath(tunnelDistance, 1, x, y);
}
