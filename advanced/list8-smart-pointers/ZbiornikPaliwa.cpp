#include "ZbiornikPaliwa.h"

ZbiornikPaliwa::ZbiornikPaliwa(size_t fuel_state) : fuel_state(fuel_state) {}

ZbiornikPaliwa::~ZbiornikPaliwa() {}

size_t ZbiornikPaliwa::takeFuel(size_t fuel) {
	std::unique_lock<std::mutex> lck(mx);
	if (fuel_state >= fuel) {
		fuel_state -= fuel;
		return fuel;
	}
	else return 0;
}