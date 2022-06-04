#include <iostream>
#include "listTask.h"

int main() {
	std::vector<double> v1 = { 1.0, 5.0 };
	std::vector<double> v2 = { 15.5, 1.0 };
	
	listTask lT(3);

	for (size_t i = 2; i <= 100000; ++i) {
		lT.add_task([i] { return i * i; });
	}
	
	lT.stop();
	std::cout << "Avg after stop(): " << lT.average() << "\n\n";
	return 0;
}