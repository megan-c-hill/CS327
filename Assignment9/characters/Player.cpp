#include "Player.h"
#include <ncurses.h>
#include "../shared-components.h"

Player *generatePlayerCharacter() {
	Player *pc = (Player *) malloc(sizeof(Player));

	pc->speed = 10;
	pc->HP = 100;
	pc->damage = Dice(0, 1, 4);
	pc->symbol = '@';
	strcpy(pc->name, "You");
	pc->color = COLOR_BLUE;

	return pc;
}

void placePlayer() {
	bool isDone = false;
	uint8_t x, y;
	while (!isDone) {
		x = rand() % (TOTAL_WIDTH - 5) + 1;
		y = rand() % (TOTAL_HEIGHT - 4) + 1;
		Character *pc = generatePlayerCharacter();

		if (dungeon[y][x].symbol == '#' || dungeon[y][x].symbol == '.') {
			pc->x = x;
			pc->y = y;
			characterMap[y][x] = pc;
			isDone = true;
			CharacterNode *head = newCharacterNode(pc, 0);
			playerQueue = newCharacterHeap(head);
			playerCharacter = pc;
		}
	}
}

void placePlayerWithCoords(int x, int y) {
	Player *pc = generatePlayerCharacter();
	pc->x = x;
	pc->y = y;
	characterMap[y][x] = pc;
	CharacterNode *head = newCharacterNode(pc, 0);
	playerCharacter = pc;
	playerQueue = newCharacterHeap(head);
}
