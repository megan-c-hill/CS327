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

string Dice::print() {
	string result = std::string();
	result += std::to_string(base);
	result += "+";
	result += std::to_string(dice);
	result += "d";
	result += std::to_string(sides);
	return result;
}
