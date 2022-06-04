#pragma once
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <chrono>
#include "ZbiornikPaliwa.h"

class Silnik {
public:
	Silnik(size_t time, size_t fuel);
	~Silnik();

	void connectFuelTank(std::shared_ptr<ZbiornikPaliwa>& tank_ptr);

private:
	size_t time;
	size_t fuel;
	std::thread th;
	std::queue<std::shared_ptr<ZbiornikPaliwa>> fuel_tanks;
	void start();
	std::condition_variable cv;
	std::mutex mx;
	//std::mutex mx2;
};