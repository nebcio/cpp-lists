#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <mutex>
#include <numeric>

class listTask {
public:
	listTask(size_t n = 1);
	~listTask();

	void add_task(std::function<double()> task);
	double average() const;
	void stop() noexcept;

protected:
	std::vector<std::thread> threads;
	std::queue<std::function<double()>> tasks;
	std::vector<double> results;

	size_t nr_threads;
	std::mutex mx;
	mutable std::mutex mx2;
	std::condition_variable cv;
	bool to_stop = false;
	bool run = true;
	
	void start(size_t n);
};