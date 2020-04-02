#pragma once

#include "RandomGenerator.h"
class Pi {
public:
	[[nodiscard]] long double operator()();
private:
	const long long mainConstant = INT_MAX / 1000;
	RandomGenerator<long long> randomGenerator{ 0, mainConstant };
};

[[nodiscard]] long double Pi::operator()() {
	auto inCircle = 0LL;
	for (long i = 0; i < mainConstant; ++i) {
		auto x = randomGenerator();
		auto y = randomGenerator();
		if (x * x + y * y <= mainConstant * mainConstant) {
			++inCircle;
		}
	}
	return static_cast<long double>(inCircle) / mainConstant * 4;
}