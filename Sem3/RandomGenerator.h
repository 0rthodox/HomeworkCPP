#pragma once

#include <random>
#include <chrono>

int rand_uns(int min, int max) {
	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	static std::default_random_engine e(seed);
	std::uniform_int_distribution<int> d(min, max);
	return d(e);
}

template <typename Int>
class RandomGenerator {
	Int min;
	Int max;
	inline static unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	inline static std::default_random_engine e = std::default_random_engine(seed);
public:
	RandomGenerator(Int min, Int max) : min(min), max(max) {}
	Int rand() {
		std::uniform_int_distribution d(min, max);
		return d(e);
	}
};