#include "AccumulateNThreads.hpp"
#include "ForEachUnsafe.hpp"
#include "ParForEach.hpp"
#include "Pi.hpp"
#include "Timer.h"

#include <cmath>
#include <execution>
#include <fstream>
#include <iostream>
#include <mutex>
#include <numeric>
#include <vector>

//std::mutex m;

int main() {
	//Test #4
	std::fstream output1("Sem8/data41.txt", std::ios_base::out);
	for (size_t i = 10; i < 1000000000; i *= 2) {
		std::vector<int> ints(i);
		std::iota(ints.begin(), ints.end(), 1);
		output1 << log(i) << ' ';
		{
			Timer<std::chrono::microseconds> t;
			std::for_each(ints.begin(), ints.end(), [](auto x) {
				auto a = cos(x);
				});
			auto time = t.getDuration();
			output1 << time << ' ';
		}
		{
			Timer<std::chrono::microseconds> t;
			std::for_each(std::execution::par, ints.begin(), ints.end(), [](auto x) {
				auto a = cos(x);
				});
			auto time = t.getDuration();
			output1 << time << '\n';
		}

	}
	std::fstream output1("Sem8/data42.txt", std::ios_base::out);
	for (size_t i = 10; i < 50000000; i *= 2) {
		std::vector<int> ints(i);
		std::iota(ints.begin(), ints.end(), 1);
		output1 << log(i) << ' ';
		{
			std::vector<int> dest(ints.size());
			Timer<std::chrono::microseconds> t;
			std::partial_sum(ints.begin(), ints.end(), dest.begin());
			auto time = t.getDuration();
			output1 << time << ' ';
		}
		{
			std::vector<int> dest(ints.size());
			Timer<std::chrono::microseconds> t;
			std::inclusive_scan(std::execution::par, ints.begin(), ints.end(), dest.begin());
			auto time = t.getDuration();
			output1 << time << '\n';
		}

	}
	std::fstream output1("Sem8/data43.txt", std::ios_base::out);
	for (size_t i = 10; i < 50000000; i *= 2) {
		std::vector<int> ints(i);
		std::iota(ints.begin(), ints.end(), 1);
		std::vector<int> sInts(ints);
		output1 << log(i) << ' ';
		{
			Timer<std::chrono::microseconds> t;
			std::inner_product(ints.begin(), ints.end(), sInts.begin(), 0);
			auto time = t.getDuration();
			output1 << time << ' ';
		}
		{
			std::vector<int> dest(ints.size());
			Timer<std::chrono::microseconds> t;
			std::transform_reduce(std::execution::par, ints.begin(), ints.end(), sInts.begin(), 0);
			auto time = t.getDuration();
			output1 << time << '\n';
		}

	}

	////Test #3
	//std::vector<int> ints(100000);
	//std::iota(ints.begin(), ints.end(), 1);
	//parForEach(ints.begin(), ints.end(), [](auto& x) {
	//	m.lock();
	//	std::cout << x << " ";
	//	std::cout.flush();
	//	m.unlock();
	//	x *= x;
	//	});
	//for (const auto& x : ints) {
	//	std::cout << x << " ";
	//	if (!(x % 100)) {
	//		std::cout << std::endl;
	//	}
	//}
	
	////Test #1
	//std::cout << Pi()() << std::endl;
	//std::cout << PiParallel()() << std::endl;

	////Test #2
	//std::vector < int > v(5000000);

	//std::iota(v.begin(), v.end(), 1);

	//std::fstream output("Sem8/task2data.txt", std::ios_base::out);

	//for (auto i = 1; i <= 24; ++i) {
	//	Timer<std::chrono::microseconds> t;
	//	parallel_accumulate(v.begin(), v.end(), 0, i);
	//	output << t.getDuration() << ' ' << i << std::endl;
	//}

}