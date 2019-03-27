//
// Created by Megan's ISU on 2019-03-27.
//

#include "dice.h"

Dice::Dice() {
	base = 0;
	dice = 0;
	sides = 1;
}

Dice::Dice(int base, int dice, int sides) {
	this->base = base;
	this->dice = dice;
	this->sides = sides;
}
