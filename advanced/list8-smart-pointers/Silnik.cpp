#include "Silnik.h"

Silnik::Silnik(size_t time, size_t fuel) : time(time), fuel(fuel), th(&Silnik::start, this){
	//th = std::thread();
	std::cout << "Konstruktor silnika: " << fuel << "\n";
}

Silnik::~Silnik() {
	if (th.joinable()) th.join();
}

void Silnik::start() {
	auto t0 = std::chrono::high_resolution_clock::now();
	bool run = true;
	while (run) {

		std::unique_lock<std::mutex> lck(mx);
		cv.wait(lck, [&] {return !fuel_tanks.empty() || !run; });

		auto t1 = std::chrono::high_resolution_clock::now();
		//lck.unlock();

		if (std::chrono::duration<double>(t1 - t0).count() > time) {	// sprawdza czy minal odpowiedni okres

			//std::unique_lock<std::mutex> lck2(mx2);
			bool taken = false;
			while (!fuel_tanks.empty() && !taken) {	// jesli ma zbiorniki i jeszcze nie pobral paliwa w danym momencie
				if (fuel_tanks.front()->takeFuel(fuel) != fuel) {	// jesli nie uda sie pobrac to usuwa ze swojego zbioru zbiornik
					fuel_tanks.pop();
				}
				else {	// jesli sie uda wyswietla komunikat i zmienia zmienna by wyjsc z while
					std::cout << "\nSilnik " << fuel << " pobral paliwo po: " << std::chrono::duration<double>(t1 - t0).count() << " s\n";
					taken = true;
				}
			}
			if (fuel_tanks.empty()) {
				std::cout << "Silnik " << fuel << " nie ma zbiornikow do pobrania paliwa \n";
				run = false;
			}
			lck.unlock();
			t0 = std::chrono::high_resolution_clock::now();	// nadpisuje t0
		}
	}
}

void Silnik::connectFuelTank(std::shared_ptr<ZbiornikPaliwa>& tank_ptr) {
	std::unique_lock<std::mutex> lck(mx);
	fuel_tanks.push(tank_ptr);
	lck.unlock();
	cv.notify_one();
}