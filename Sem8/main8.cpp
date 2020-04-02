#include "ParForEach.hpp"
#include "ForEachUnsafe.hpp"
#include <vector>
#include <iostream>
#include <numeric>
#include <mutex>
#include "Pi.hpp"

std::mutex m;

int main() {

	////Test #3
	//std::vector<int> ints(100000);
	//std::iota(ints.begin(), ints.end(), 1);
	//forEachUnsafe(ints.begin(), ints.end(), [](auto& x) {
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

	//Test #4
	std::cout << Pi()();
}