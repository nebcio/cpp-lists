#include "a.h"
#include <string>

a::a(const std::string& val) {
	std::cout << "P\n";
	pole = new char[val.length()+1];
	memcpy(pole, val.c_str(), val.length() + 1);
}

a::a(const a& rhs) { // copy constructor
	std::cout << "D\n";
	pole = new char[strlen(rhs.pole) + 1];
	memcpy(pole, rhs.pole, strlen(rhs.pole) + 1);
}

a::a(a&& rhs) { // move constructor
	std::cout << "T\n";
	pole = rhs.pole;
	rhs.pole = nullptr;
}

a::~a() {
	std::cout << "Destuction " << pole;
	delete[] pole;
}

char* a::get() const {
	return pole;
}