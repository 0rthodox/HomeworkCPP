#include "ParForEach.hpp"
#include "ForEachUnsafe.hpp"
#include <vector>
#include <iostream>
#include <numeric>
#include <mutex>

std::mutex m;

int main() {
	std::vector<int> ints(100000);
	std::iota(ints.begin(), ints.end(), 1);
	forEachUnsafe(ints.begin(), ints.end(), [](auto& x) {
		m.lock();
		std::cout << x << " ";
		std::cout.flush();
		m.unlock();
		x *= x;
		});
	for (const auto& x : ints) {
		std::cout << x << " ";
		if (!(x % 100)) {
			std::cout << std::endl;
		}
	}
}