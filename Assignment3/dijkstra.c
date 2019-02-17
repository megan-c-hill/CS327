#ifndef SHARED_COMPONENTS
#define SHARED_COMPONENTS

#include <limits.h>
#include "shared-components.c"
#endif
#include "heap.c"

char nonTunnelDistance[TOTAL_HEIGHT][TOTAL_WIDTH];

void initNonTunnelArray(){
	for(int i = 0; i<TOTAL_HEIGHT; i++){
		for(int j = 0; j<TOTAL_WIDTH; j++){
			if (i == 0 || i == TOTAL_HEIGHT - 1){
				nonTunnelDistance[i][j] = '-';
			} else if (j == 0 || j == TOTAL_WIDTH - 1) {
				nonTunnelDistance[i][j] = '|';
			} else {
				nonTunnelDistance[i][j] = ' ';
			}
		}
	}
}

void printArray(char dungeonMap[TOTAL_HEIGHT][TOTAL_WIDTH]){
	for(int i = 0; i<TOTAL_HEIGHT; i++){
		for(int j = 0; j<TOTAL_WIDTH; j++){
			printf("%c", dungeonMap[i][j]);
		}
		printf("\n");
	}
}


/**
 * 1) Initialize distances of all vertices as infinite.

2) Create an empty priority_queue pq.  Every item
   of pq is a pair (weight, vertex). Weight (or
   distance) is used used as first item  of pair
   as first item is by default used to compare
   two pairs

3) Insert source vertex into pq and make its
   distance as 0.

4) While either pq doesn't become empty
    a) Extract minimum distance vertex from pq.
       Let the extracted vertex be u.
    b) Loop through all adjacent of u and do
       following for every vertex v.

           // If there is a shorter path to v
           // through u.
           If dist[v] > dist[u] + weight(u, v)

               (i) Update distance of v, i.e., do
                     dist[v] = dist[u] + weight(u, v)
               (ii) Insert v into the pq (Even if v is
                    already there)

5) Print distance array dist[] to print all shortest
   paths.
 */

//void dijkstra(){
//	static corridor_path_t path[DUNGEON_Y][DUNGEON_X], *p;
//	static uint32_t initialized = 0;
//	heap_t h; //1)
//	uint32_t x, y;
//
//	if (!initialized) {
//		for (y = 0; y < DUNGEON_Y; y++) {
//			for (x = 0; x < DUNGEON_X; x++) {
//				path[y][x].pos[dim_y] = y;
//				path[y][x].pos[dim_x] = x;
//			}
//		}
//		initialized = 1;
//	}
//
//	for (y = 0; y < DUNGEON_Y; y++) {
//		for (x = 0; x < DUNGEON_X; x++) {
//			path[y][x].cost = INT_MAX;
//		}
//	}
//
//	heap_init(&h, corridor_path_cmp, NULL);
//
//	for (y = 0; y < DUNGEON_Y; y++) {
//		for (x = 0; x < DUNGEON_X; x++) {
//			if (mapxy(x, y) != 255) {
//				path[y][x].hn = heap_insert(&h, &path[y][x]);
//			} else {
//				path[y][x].hn = NULL;
//			}
//		}
//	}
//
//	while ((p = heap_remove_min(&h))) {
//		p->hn = NULL;
//
//		if ((p->pos[dim_y] == to[dim_y]) && p->pos[dim_x] == to[dim_x]) {
//			for (x = to[dim_x], y = to[dim_y];
//				 (x != from[dim_x]) || (y != from[dim_y]);
//				 p = &path[y][x], x = p->from[dim_x], y = p->from[dim_y]) {
//				if (mapxy(x, y) != ter_floor_room) {
//					mapxy(x, y) = ter_floor_hall;
//					hardnessxy(x, y) = 0;
//				}
//			}
//			heap_delete(&h);
//			return;
//		}
//
//		if ((path[p->pos[dim_y] - 1][p->pos[dim_x]    ].hn) &&
//			(path[p->pos[dim_y] - 1][p->pos[dim_x]    ].cost >
//			 p->cost + hardnesspair(p->pos))) {
//			path[p->pos[dim_y] - 1][p->pos[dim_x]    ].cost =
//					p->cost + hardnesspair(p->pos);
//			path[p->pos[dim_y] - 1][p->pos[dim_x]    ].from[dim_y] = p->pos[dim_y];
//			path[p->pos[dim_y] - 1][p->pos[dim_x]    ].from[dim_x] = p->pos[dim_x];
//			heap_decrease_key_no_replace(&h, path[p->pos[dim_y] - 1]
//			[p->pos[dim_x]    ].hn);
//		}
//		if ((path[p->pos[dim_y]    ][p->pos[dim_x] - 1].hn) &&
//			(path[p->pos[dim_y]    ][p->pos[dim_x] - 1].cost >
//			 p->cost + hardnesspair(p->pos))) {
//			path[p->pos[dim_y]    ][p->pos[dim_x] - 1].cost =
//					p->cost + hardnesspair(p->pos);
//			path[p->pos[dim_y]    ][p->pos[dim_x] - 1].from[dim_y] = p->pos[dim_y];
//			path[p->pos[dim_y]    ][p->pos[dim_x] - 1].from[dim_x] = p->pos[dim_x];
//			heap_decrease_key_no_replace(&h, path[p->pos[dim_y]    ]
//			[p->pos[dim_x] - 1].hn);
//		}
//		if ((path[p->pos[dim_y]    ][p->pos[dim_x] + 1].hn) &&
//			(path[p->pos[dim_y]    ][p->pos[dim_x] + 1].cost >
//			 p->cost + hardnesspair(p->pos))) {
//			path[p->pos[dim_y]    ][p->pos[dim_x] + 1].cost =
//					p->cost + hardnesspair(p->pos);
//			path[p->pos[dim_y]    ][p->pos[dim_x] + 1].from[dim_y] = p->pos[dim_y];
//			path[p->pos[dim_y]    ][p->pos[dim_x] + 1].from[dim_x] = p->pos[dim_x];
//			heap_decrease_key_no_replace(&h, path[p->pos[dim_y]    ]
//			[p->pos[dim_x] + 1].hn);
//		}
//		if ((path[p->pos[dim_y] + 1][p->pos[dim_x]    ].hn) &&
//			(path[p->pos[dim_y] + 1][p->pos[dim_x]    ].cost >
//			 p->cost + hardnesspair(p->pos))) {
//			path[p->pos[dim_y] + 1][p->pos[dim_x]    ].cost =
//					p->cost + hardnesspair(p->pos);
//			path[p->pos[dim_y] + 1][p->pos[dim_x]    ].from[dim_y] = p->pos[dim_y];
//			path[p->pos[dim_y] + 1][p->pos[dim_x]    ].from[dim_x] = p->pos[dim_x];
//			heap_decrease_key_no_replace(&h, path[p->pos[dim_y] + 1]
//			[p->pos[dim_x]    ].hn);
//		}
//	}
//
//
//}

void nonTunnelingDistance(){
	initNonTunnelArray();
	printArray(nonTunnelDistance);

}
