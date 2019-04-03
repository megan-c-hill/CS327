//
// Created by Megan's ISU on 2019-03-27.
//

#ifndef CS327_DICE_H
#define CS327_DICE_H

#include <string>
using namespace std;


class Dice {
public:
	int base;
	int dice;
	int sides;

	Dice();
	Dice(int base, int dice, int sides);
	string print();
	friend ostream &operator<<(ostream &o, const Dice d);
};


#endif //CS327_DICE_H
