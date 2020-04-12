#pragma once

#include <boost/lockfree/stack.hpp>
#include <boost/lockfree/queue.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

#include "threadsafe_stack.hpp"
#include "threadsafe_queue.hpp"
#include "Timer.hpp"

constexpr size_t M = 1'000'000;

template <template<class> class Stack, class T>
auto testStackOnce(size_t N = std::thread::hardware_concurrency() ?
				   std::thread::hardware_concurrency() / 2 :
				   2u) {

	//Preparing data
	std::atomic<bool> flag = false;
	Stack<T> stack/*(M * N)*/;
	/*RandomGenerator<T> Генератор(T(), static_cast<T>(M * N));*/
	for (auto i = 0u; i <= M; ++i) {
		stack.push(/*Генератор()*/T(65, 'N'));
	}
	T tempVal;

	//Launching threads
	std::vector<std::thread> threads;
	for (auto i = 0u; i < N; ++i) {
		threads.push_back(std::thread([&stack, &flag] () mutable {
			while (!flag.load()) {
				std::this_thread::yield();
			}
			for (auto i = 0u; i <= M; ++i) {
				try {

					stack.push(0);
				}
				catch (std::exception& ex) {
					std::cerr << ex.what();
				}
			}
			//std::cerr << "Finished writing" << std::endl;
			}));
		threads.push_back(std::thread([&stack, &tempVal, &flag] () mutable {
			while (!flag.load()) {
				std::this_thread::yield();
			}
			for (auto i = 0u; i <= M; ++i) {
				try {
					T tempStr;
					stack.pop(tempStr);
				}
				catch (std::exception& ex) {
					std::cerr << ex.what();
				}
			}
			//std::cerr << "Finished reading" << std::endl;
			}));
	}

	//Measuring time
	Timer<std::chrono::milliseconds> t;
	flag.store(true);
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
	auto elapsed = t.getDuration();
	std::stringstream output;
	output << N << ' ' << elapsed << std::endl;
	return output.str();
}

template <template<class> class Stack, class T>
auto testStack(size_t minN = 2, size_t maxN = 8,
	const std::filesystem::path path = std::string(typeid(Stack<T>).name()).substr(6, 5) + ".txt") {

	std::fstream output("Sem9" / path, std::ios_base::out);

	for (size_t i = minN; i <= maxN; ++i) {
		try {


			output << testStackOnce<Stack, T>(i);
		}
		catch (std::exception& ex) {
			std::cerr << ex.what();
		}
	}

}