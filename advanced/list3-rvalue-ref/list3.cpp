#include <iostream>
#include "a.h"
#include <string>

a copy(const a& arg) {
	return a(arg);
}

a copy(a&& arg) {
	return a(std::move(arg));
}

template<typename T>
a copy_t(T&& arg) {
	return std::forward<T>(arg);
}

int main() {
	// 8
	std::cout << "Zadanie 8\n";
	a p("Pierwszy");	// first

	a d("Drugi");
	a dd(d);			// copy constructor with arg const l-value ref

	a t("Trzeci");
	a tt(std::move(t));	// move constructor with arg r-value ref


	// 9
	std::cout << "\n\nZadanie 9:\n";
	a f("First");					// first
	std::cout << "(1) " << f.get() << "\n\n";

	a s = copy(f);					// second
	std::cout << "(2) " << s.get() << "\n\n";

	a th = copy(std::move(f));		// third
	std::cout << "(3) " << th.get();

	// 10
	std::cout << "\n\nZadanie 10:\n";
	a f_t("First");
	std::cout << "(1) " << f_t.get() << "\n\n";
	
	a s_t = copy_t(f_t);				// call copy constructor
	std::cout << "\n(2) " << s_t.get() << "\n\n";

	a th_t = copy_t(std::move(f_t));	// call move constructor

	std::cout << "\n(3) " << th_t.get() << "\n";
	std::cin.get();
}