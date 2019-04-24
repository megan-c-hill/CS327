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

int Dice::getValue() {
	int sum = base;
	for(int i = 0; i < dice; i++) {
		sum += rand() % sides + 1;
	};
	return sum;
}
