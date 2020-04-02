#pragma once

#include "RandomGenerator.h"
#include <future>

//Sequential pi computation
class Pi {
public:
	Pi(long long iterations);
	[[nodiscard]] long double operator()();
private:
	const long long m_iterations;
	const long long m_size = static_cast<long long>(floor(sqrt(INT_MAX))); // side of the cube
	RandomGenerator<long long> randomGenerator{ 0LL, m_size };
};

// Ctor
Pi::Pi(long long iterations = INT_MAX / 1000) :
	m_iterations(iterations) {}

// Computing pi
[[nodiscard]] long double Pi::operator()() {
	auto inCircle = 0LL;
	for (long i = 0; i < m_iterations; ++i) {
		auto x = randomGenerator();
		auto y = randomGenerator();
		if (x * x + y * y <= m_size * m_size) {
			++inCircle;
		}
	}
	return static_cast<long double>(inCircle) / (m_iterations) * 4;
}

class PiParallel {
public:
	PiParallel(long long);
	[[nodiscard]] long double operator()();
private:
	const long long m_iterations;
	size_t threads;
	long long blockSize;
};

// Ctor
PiParallel::PiParallel(long long iterations = INT_MAX / 1000) :
	m_iterations(iterations) {
	threads = std::thread::hardware_concurrency();
	threads = threads ? threads : 4;
	blockSize = (m_iterations + threads - 1) / threads;
}

//Computing pi launching threads
[[nodiscard]] long double PiParallel::operator()() {
	std::vector<std::future<long double>> futures;
	for (size_t i = 1; i < threads; ++i) {
		futures.push_back(std::async(&Pi::operator(), &Pi(blockSize)));
	}
	auto lastResult = Pi(blockSize)();
	std::for_each(futures.begin(), futures.end(), [&lastResult](auto& x) {
		lastResult += x.get();
		});
	return lastResult / threads;
}