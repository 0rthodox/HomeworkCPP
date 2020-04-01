#include "ParForEach.hpp"
#include <vector>
#include <iostream>
#include <numeric>

int main() {
	std::vector<int> ints(100000);
	std::iota(ints.begin(), ints.end(), 1);
	parForEach(ints.begin(), ints.end(), [](auto& x) {
		std::cout << x << " ";
		x *= x;
		});
	for (const auto& x : ints) {
		std::cout << x << " ";
		if (!(x % 100)) {
			std::cout << std::endl;
		}
	}
}