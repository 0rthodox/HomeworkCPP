#pragma once
#include <random>
#include <chrono>

template <typename Int>
class RandomGenerator {
	std::uniform_int_distribution<Int> d;
	
public:
	RandomGenerator(Int min, Int max) : d(min, max) {}
	T rand() {
		static std::default_random_engine e(std::chrono::steady_clock::now().time_since_epoch().count());
		return d(e);
	}
};