#include "Object.h"
#include <string.h>
#include "../descriptions/itemDescription.h"
#include "../shared-components.h"
//#include <ncurses.h>
#include <string.h>

using namespace std;

static const char EMPTY_ROW_TEXT[81] = "                                                                                ";

Object *generateObject() {
	ItemDescription id;
	while (true) {
		int prob = rand() % 100 + 1;
		int randIndex = rand() % items.size();

		id = items.at(randIndex);

		if (prob < id.rarity) {
			if (strcmp(id.art, "TRUE") == 0) {
				items.erase(items.begin() + randIndex);
			}
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

		if (dungeon[y][x].hardness == 0 && objectMap[y][x] == NULL) {
			Object *object = generateObject();
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

void Object::showDetails() {
//	initscr();
//
//	for (int i = 0; i < TOTAL_HEIGHT + 3; i++) {
//		mvaddstr(i, 0, EMPTY_ROW_TEXT);
//	}
//
//	mvaddstr(0, 0, "Object Details");
//	mvaddstr(1, 0, "--------------");
//
//	mvprintw(2, 0, "NAME: %s", name);
//	mvprintw(3, 0, "DESC: ");
//	int index = 4;
//
//	for (int i = 0; i < 100 && strcmp(description[i], "NONE") != 0; i++) {
//		mvprintw(index, 0, description[i]);
//		index++;
//	}
//	mvprintw(index, 0, "TYPE: %s", type[0]);
//	index++;
//	mvprintw(index, 0, "SYMB: %c", symbol);
//	mvprintw(index + 1, 0, "COLOR: %d", color);
//	mvprintw(index + 2, 0, "HIT: %d", hit);
//	mvprintw(index + 3, 0, "DAMAGE: %s", damage.print().c_str());
//	mvprintw(index + 4, 0, "DODGE: %d", dodge);
//	mvprintw(index + 5, 0, "DEFENSE: %d", def);
//	mvprintw(index + 6, 0, "WEIGHT: %d", weight);
//	mvprintw(index + 7, 0, "SPEED: %d", speed);
//	mvprintw(index + 8, 0, "ATTRIBUTE: %d", attr);
//	mvprintw(index + 9, 0, "VALUE: %d", value);
//	mvprintw(index + 10, 0, "ARTIFACT: %s", art);
//	mvprintw(index + 11, 0, "RARITY: %d", rarity);
//	refresh();
}