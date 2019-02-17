#ifndef DIJKSTA
#define DIJKSTA

#include "shared-components.c"

struct distancePosition {
	char symbol;
	int distance;
};

struct distancePosition nonTunnelDistance[TOTAL_HEIGHT][TOTAL_WIDTH];

#include "heap.c"

uint8_t MAX_INT = 255;

void initNonTunnelArray() {
	for (int i = 0; i < TOTAL_HEIGHT; i++) {
		for (int j = 0; j < TOTAL_WIDTH; j++) {
			if (i == 0 || i == TOTAL_HEIGHT - 1) {
				nonTunnelDistance[i][j].symbol = '-';
			} else if (j == 0 || j == TOTAL_WIDTH - 1) {
				nonTunnelDistance[i][j].symbol = '|';
			} else {
				if(dungeon[i][j].hardness == 0) {
					nonTunnelDistance[i][j].symbol = 'X';
				} else {
					nonTunnelDistance[i][j].symbol = ' ';
				}
			}
			nonTunnelDistance[i][j].distance = MAX_INT;
		}
	}
}

void printArray(struct distancePosition dungeonMap[TOTAL_HEIGHT][TOTAL_WIDTH]) {
	for (int i = 0; i < TOTAL_HEIGHT; i++) {
		for (int j = 0; j < TOTAL_WIDTH; j++) {
			printf("%c", dungeonMap[i][j].symbol);
		}
		printf("\n");
	}
}

void shortestPath() {
	int playerX = playerPosition[0];
	int playerY = playerPosition[1];
	nonTunnelDistance[playerY][playerX].distance = 0;
	nonTunnelDistance[playerY][playerX].symbol = '0';
	Node *playerPosition = newNode(playerX, playerY);
	Heap *h = newHeap(playerPosition);

	while (!isEmpty(h)) {
		Node *parent = pop(h);
		int parentX = parent->x;
		int parentY = parent->y;
		int newDistance = nonTunnelDistance[parentY][parentX].distance + 1;

		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				int newY = parentY + i;
				int newX = parentX + j;
				if (dungeon[newY][newX].hardness == 0 && newDistance < nonTunnelDistance[newY][newX].distance) {
					nonTunnelDistance[newY][newX].distance = newDistance;
					nonTunnelDistance[newY][newX].symbol = newDistance % 10 + '0';
					push(h, newX, newY);
				}
			}
		}

	}
}

void nonTunnelingDistance() {
	initNonTunnelArray();
	shortestPath();
	printArray(nonTunnelDistance);

}

#endif
