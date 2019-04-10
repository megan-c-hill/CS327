#include "Object.h"
#include "../descriptions/itemDescription.h"
#include "../shared-components.h"

Object *generateObject() {
	ItemDescription id;
	while (true) {
		int prob = rand() % 100 + 1;
		int randIndex = rand() % items.size();

		id = items.at(randIndex);
		if (prob < id.rarity) {
			return id.createObject();
		}
	}
};

void placeItems(int numItems) {
	int counter = 0;
	uint8_t x, y;
	int infiniteCounter = 0;
	while (counter < numItems) {
		x = rand() % (TOTAL_WIDTH - 2) + 1;
		y = rand() % (TOTAL_HEIGHT - 2) + 1;
		Object *object = generateObject();

		if (dungeon[y][x].hardness == 0 && objectMap[y][x] == NULL) {
			object->x = x;
			object->y = y;
			objectMap[y][x] = object;
			counter++;
			infiniteCounter = 0;
		} else if (infiniteCounter > 2000) {
			break;
		} else {
			infiniteCounter++;
		}
	}
}