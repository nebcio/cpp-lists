#include <iostream>
#include <vector>
#include "Silnik.h"
#include "ZbiornikPaliwa.h"

int main() {
	Silnik one(1, 1);
	Silnik two(3, 2);
	Silnik five(2, 5);
	std::vector<std::shared_ptr<ZbiornikPaliwa>> tanks;

	for (int i = 0; i < 10; ++i) {
		tanks.push_back(std::make_shared<ZbiornikPaliwa>(10 + i));
	}

	for (int i = 0; i < 10; ++i) {
		one.connectFuelTank(tanks[i]);
		two.connectFuelTank(tanks[i]);
		five.connectFuelTank(tanks[i]);
	}

	return 0;
}