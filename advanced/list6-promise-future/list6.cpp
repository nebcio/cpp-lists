#include <iostream>
#include <vector>
#include <array>
#include <future>
#include <exception>
#include <stdexcept>

void ilocz_skalar(std::vector<double> &v1, std::vector<double> &v2, std::promise<double> pr) {
	if(v1.empty() || v2.empty()) {
		pr.set_exception(std::make_exception_ptr(std::runtime_error("Przynajmniej jeden wektor jest pusty")));
	}
	else if (v1.size() != v2.size()) {
		pr.set_exception(std::make_exception_ptr(std::runtime_error("Rozne wielkosci wektorow")));
	}
	else {
		double suma = 0.0;
		for (size_t i = 0; i < v1.size(); i++)
			suma += v1[i] * v2[i];

		pr.set_value(suma);
	}
}

int main() {
	std::vector<double> v1 = { 1.0, 2.0, 1.0 };	// przewidywany iloczyn 6 v1 i v2
	std::vector<double> v2 = { 1.0, 2.0, 1.0 };
	std::vector<double> v3 = { 1.0, 2.0 };		// v1.size != v2.size
	std::vector<double> v4;						// emty

	std::array<std::promise<double>, 10> pr;
	std::array<std::future<double>, 10> fut;
	std::vector<std::thread> threads;

	for (int i = 0; i < 10; ++i) {
		fut[i] = pr[i].get_future();
	}

	try {
		for (size_t i = 0; i < pr.size() - 2; ++i) {
			threads.push_back(std::thread(ilocz_skalar, std::ref(v1), std::ref(v2), std::move(pr[i])));	// iloczyn na konkretnym watku
		}
		threads.push_back(std::thread(ilocz_skalar, std::ref(v1), std::ref(v3), std::move(pr[8]))); // diffrent size
		threads.push_back(std::thread(ilocz_skalar, std::ref(v1), std::ref(v4), std::move(pr[9]))); // empty

		double suma_iloczynow = 0.0;
		for (size_t i = 0; i < fut.size(); ++i) {
			try {
				suma_iloczynow += fut[i].get();		// pobranie po kolei wynikow po synchronizacji
			}
			catch (std::future_error const& e) {
				std::cout << "Future error: " << e.what() << " / " << e.code() << std::endl;
			}
			catch (std::exception const& e) {
				std::cout << "Standard exception: " << e.what() << std::endl;	// when v1.size != v2.size or v1/v2 is empty
			}
		}

		for (size_t i = 0; i < threads.size(); i++) {
			threads[i].join();
		}
		std::cout << "\nSuma udanych policzonych iloczynow skalarnych v1 i v2: " << suma_iloczynow;
	}
	catch (std::future_error const &e) {
		std::cout << "Future error: " << e.what() << " / " << e.code() << std::endl;
	}
	catch (std::exception const &e) {
		std::cout << "Standard exception: " << e.what() << std::endl;	// when v1.size != v2.size or v1/v2 is empty
	}
	catch (...) {
		std::cout << "Inne bledy";
	}
}