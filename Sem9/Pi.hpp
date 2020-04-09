#pragma once

#include "RandomGenerator.h"
#include <future>
#include <mutex>
#include <iostream>

//parallel Pi computation
class PiParallel {
public:
	PiParallel(long long);
	[[nodiscard]] long double operator()();
private:
	[[nodiscard]] void computeDots(long long, long long&);
	const long long m_iterations;
	size_t numThreads;
	long long blockSize;
	const long long m_size = static_cast<long long>(floor(sqrt(INT_MAX))); // side of the cube
	RandomGenerator<long long> randomGenerator{ 0LL, m_size };
	std::mutex m_mutex;
};

// Ctor
PiParallel::PiParallel(long long iterations = INT_MAX / 1000) :
	m_iterations(iterations) {
	numThreads = std::thread::hardware_concurrency();
	numThreads = numThreads ? numThreads : 4;
	blockSize = (m_iterations + numThreads - 1) / numThreads;
}

//Computing pi launching threads
[[nodiscard]] long double PiParallel::operator()() {
	long long inCircle = 0;
	std::vector<std::thread> threads;
	for (size_t i = 1; i < numThreads; ++i) {
		threads.push_back(std::thread{&PiParallel::computeDots, this, blockSize, std::ref(inCircle)});
	}
	computeDots(m_iterations - (numThreads - 1) * blockSize, std::ref(inCircle));
	for (auto& thr : threads) {
		thr.join();
	}
	return 4 * static_cast<long double>(inCircle) / m_iterations;
}

//Computing amount of dots inside
[[nodiscard]] inline void PiParallel::computeDots(long long iterations, long long& inCircle)
{
	long j = 0;
	for (long i = 0; i < iterations; ++i) {
		auto x = randomGenerator();
		auto y = randomGenerator();
		if (x * x + y * y <= m_size * m_size) {
			++j;
			std::lock_guard guard{m_mutex};
			++inCircle;
		}
	}
}
