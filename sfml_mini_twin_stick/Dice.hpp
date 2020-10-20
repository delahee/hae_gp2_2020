#pragma once

#include <cstdlib>

class Dice {
public:
	static int randSign() {
		return (rand() % 2) ? 1 : -1;
	}
};