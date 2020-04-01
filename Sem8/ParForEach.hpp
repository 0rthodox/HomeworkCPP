#pragma once
#include <future>
#include <algorithm>


template <typename It, typename uFunc>
void parForEach(It first, It last, uFunc f) {
	const std::size_t len = std::distance(first, last);
	constexpr std::size_t max_size = 127;
	if (len <= max_size) {
		std::for_each(first, last, f);
	} else {
		It middle = next(first, (len + 1) / 2);
		std::future<void> lHalf = std::async(parForEach<It, uFunc>, first, middle, f);
		parForEach(middle, last, f);
	}
}