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
	Timer() : ticking(true), start(clock_t::now()), time_periods() {
	}
	void pause() {
		updateIfTicking();
		ticking = false;
	}
	void resume() {
		start = clock_t::now();
		ticking = true;
	}
	auto getDuration() {
		updateIfTicking();
		return std::chrono::duration_cast<Accuracy>(time_periods).count();
	}
	~Timer() noexcept {
		updateIfTicking();
		std::cout << std::chrono::duration_cast<Accuracy>(time_periods).count() << std::endl;
	}

private:
	bool ticking;
	duration_t time_periods;
	timepoint_t start;
	void updateIfTicking() {
		if (ticking) {
			time_periods += (clock_t::now() - start);
		}
	}
};



template <typename Accuracy>
class MultiTimer {
	using clock_t = std::chrono::steady_clock;
	using timepoint_t = clock_t::time_point;
	using duration_t = clock_t::duration;

public:
	MultiTimer() : start(clock_t::now()) {
	}
	void pause() {
		time_periods.push_back(clock_t::now() - start);
	}
	void resume() {
		start = clock_t::now();
	}
	~MultiTimer() noexcept {
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