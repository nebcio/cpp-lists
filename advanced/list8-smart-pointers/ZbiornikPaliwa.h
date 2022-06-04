#pragma once
#include <iostream>
#include <mutex>

class ZbiornikPaliwa {
public:
	ZbiornikPaliwa(size_t fuel_state);
	~ZbiornikPaliwa();
	size_t takeFuel(size_t fuel);

private:
	size_t fuel_state;
	std::mutex mx;
};