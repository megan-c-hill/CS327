#ifndef CS327_PLAYER_H
#define CS327_PLAYER_H

#include "Character.h"

class Player : public Character {
public:
	Object* equipment[12];
	Object* inventory[10];
};

Player *generatePlayerCharacter();

void placePlayer();

void placePlayerWithCoords(int x, int y);


#endif //CS327_PLAYER_H
