#include "listTask.h"

listTask::listTask(size_t n) : nr_threads(n) {
	std::cout << "// Started with: " << nr_threads << " threads.\n\n";
	start(nr_threads);
}

listTask::~listTask() {
	std::cout << "// Destructor called. ";
	stop();
}

void listTask::add_task(std::function<double()> task) {
	std::unique_lock<std::mutex> lck(mx);
	tasks.emplace(std::move(task));
	std::cout << "// Task on the list. \n";
	lck.unlock();

	cv.notify_one();
}

double listTask::average() const {
	std::unique_lock<std::mutex> lck(mx2);
	if (results.empty()) {
		return 0.0;
	}

	double const count = static_cast<double>(results.size());
	double sum = static_cast<double>(std::reduce(results.begin(), results.end()));
	auto avg = sum / count;
	std::cout << "// Task done. Returned: " << results.back() << ". Average now: " << avg << "\n";
	lck.unlock();
	return avg;
}

void listTask::start(size_t n) {
	for (size_t i = 0; i < n; ++i) {
		threads.emplace_back([&] {
			while (run) {
				std::function<double()> task;

				std::unique_lock<std::mutex> lck(mx);

				cv.wait(lck, [=] { return !tasks.empty() || to_stop; });

				task = std::move(tasks.front());
				tasks.pop();

				lck.unlock();

				auto result = task();
				std::unique_lock<std::mutex> lck2(mx2);
				results.push_back(result);
				lck2.unlock();

				average();

				if (to_stop && tasks.empty()) run = false;
			}
		});
	}
}

void listTask::stop() noexcept {
	// joins of threads
	std::unique_lock<std::mutex> lck(mx);
	to_stop = true;

	lck.unlock();
	cv.notify_all();

	for (auto& th : threads) {
		if(th.joinable())
			th.join();
	}
	std::unique_lock<std::mutex> lck3(mx);
	std::cout << "// Stopped. \n\n";
	std::cout << "Last average: " << average() << "\n\n";
	lck3.unlock();
}