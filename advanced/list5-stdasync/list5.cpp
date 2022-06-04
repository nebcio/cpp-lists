#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <string>

int thread_id() {
	static int a = 0;
	thread_local int t_id = a++; // przy wykonywaniu kodu na tym samym watku nie deklaruje ponownie wartosci wiec jej nie zwieksza
	// ++a; lepiej przy przypisaniu, dlatego ze znikalyby niekture wartosci id, np przy wywolaniu 2 razy na tym samym watku
	return t_id;
}

void describe(std::string opis){
	static std::mutex mx;
	mx.lock();
	std::cout << opis << "Thread nr " << thread_id() << "\n";
	mx.unlock();
}

void async_test(std::launch type) {
	auto obj = std::async(type, &describe, "Async 1");
	obj.get();
}

void async_test2(std::launch type) {
	auto obj = std::async(type, &describe, "Async 2");
	async_test(type);
	obj.get();
}

void async_test3(std::launch type) {
	auto obj = std::async(type, &describe, "Async 3");
	async_test2(type);
	obj.get();
}

void async_test4(std::launch type) {
	auto obj = std::async(type, &describe, "Async 4");
	async_test3(type);
	obj.get();
}

int main() {

	std::thread th1(describe, "th1 ");
	std::thread th2(describe, "th2 ");
	std::thread th3(describe, "th3 ");


	th1.join();
	th2.join();
	th3.join();

	std::cout << "\n\nAsync: \n";
	async_test4(std::launch::async);
	std::cout << "\n\nDeferred: \n";
	async_test4(std::launch::deferred);

}