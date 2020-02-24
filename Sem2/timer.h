#pragma once

#ifndef _TIMER_H_
#define _TIMER_H_

#include <numeric>
#include <chrono>
#include <vector>

template <typename Accuracy>
class Timer {
	using clock_t = std::chrono::steady_clock;
	using timepoint_t = clock_t::time_point;
	using duration_t = clock_t::duration;

public:
	Timer() : start(clock_t::now()) {
	}
	void pause() {
		time_periods.push_back(clock_t::now() - start);
	}
	void resume() {
		start = clock_t::now();
	}
	~Timer() noexcept {
		pause();
		std::cout << std::chrono::duration_cast<Accuracy>(
			std::accumulate(time_periods.begin(), time_periods.end(),
				duration_t())).count() << std::endl;
	}

private:
	std::vector<duration_t> time_periods;
	timepoint_t start;
};

#endif