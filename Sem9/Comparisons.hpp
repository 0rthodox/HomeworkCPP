#define INTERNAL_NESTED_DYNAMIC_ALLOCATOR(b, lineNum) b ## lineNum
#define INTERNAL_DYNAMIC_ALLOCATOR(b, lineNum) INTERNAL_NESTED_DYNAMIC_ALLOCATOR(b, lineNum)
#define dynamicVar INTERNAL_DYNAMIC_ALLOCATOR(var, __LINE__)

#define INDEPENDENT_CHAR static_cast<char>(__LINE__)
#define INDEPENDENT_DOUBLE static_cast<double>(__LINE__)
#define INDEPENDENT_WCHAR static_cast<wchar_t>(__LINE__)

#pragma once

#define USING_BOOST


#include <boost/lockfree/spsc_queue.hpp>
#include <boost/lockfree/queue.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

#include "threadsafe_queue.hpp"
#include "Timer.hpp"

constexpr size_t M = 1'000'000;

struct Z {
	char dynamicVar = INDEPENDENT_CHAR;
	wchar_t dynamicVar = INDEPENDENT_WCHAR;
	double dynamicVar = INDEPENDENT_DOUBLE;
};


struct S
{
	char data[100];

	S() = default;

	S(const struct S& other) {
		std::memcpy(&data, &(other.data), 100);
	}

};



template <template<class> class Stack, class T>
auto testStackOnce(size_t N = std::thread::hardware_concurrency() ?
				   std::thread::hardware_concurrency() / 2 :
				   2u) {

	//Preparing data
	std::atomic<bool> flag = false;
#ifdef USING_BOOST
	Stack<T> stack{ M * N };
#else
	Stack<T> stack{};
#endif
	/*RandomGenerator<T> Генератор(T(), static_cast<T>(M * N));*/
	for (auto i = 0u; i <= M * N; ++i) {
		S e;
		stack.push(/*Генератор()*/e);
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
					S e;
					 stack.push(e);
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
#ifdef USING_BOOST
					stack.pop(tempStr);
#else
					stack.wait_and_pop(tempStr);
#endif
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