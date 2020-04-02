#include "ParForEach.hpp"
#include "ForEachUnsafe.hpp"
#include <vector>
#include <iostream>
#include <numeric>
#include <mutex>
#include "Pi.hpp"
#include "AccumulateNThreads.hpp"
#include <fstream>
#include "Timer.h"

std::mutex m;

template <typename T>
T abs(T x) {
	auto result = (x < 0) ? -x : x;
	return result;
}

int main() {

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
	
	////Test #4
	//std::cout << Pi()() << std::endl;
	//std::cout << PiParallel()() << std::endl;

	//Test #2
	std::vector < int > v(5000000);

	std::iota(v.begin(), v.end(), 1);

	std::fstream output("Sem8/task2data.txt", std::ios_base::out);

	for (auto i = 1; i <= 24; ++i) {
		Timer<std::chrono::microseconds> t;
		parallel_accumulate(v.begin(), v.end(), 0, i);
		output << t.getDuration() << ' ' << i << std::endl;
	}

}