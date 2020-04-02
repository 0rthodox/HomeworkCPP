#pragma once

#include <random>
#include <chrono>
#include <string>
#include <set>

template <typename Int>
class RandomGenerator {
	Int min;
	Int max;
	inline static unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	inline static std::default_random_engine e = std::default_random_engine(seed);
	std::uniform_int_distribution<Int> d;
public:
	RandomGenerator(Int min, Int max) : min(min), max(max), d(min, max) {}
	Int operator()() {
		return d(e);
	}
};