#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

template < typename Iterator, typename T >
T parallel_accumulate(Iterator first, Iterator last, T init, size_t threads)
{
	const std::size_t length = std::distance(first, last);

	std::size_t blockLength = (length + threads - 1) / threads;

	auto currentIterator = first;

	std::vector<future<T>> futures(threads - 1);

	for (size_t i = 1; i < threads; ++i) {
		auto nextIterator = std::next(currentIterator, blockLength);
		futures.push_back(std::async(std::accumulate(currentIterator, nextIterator, T())));
		currentIterator = nextIterator;
	}

	T result = std::accumulate(currentIterator, last, init);

	std::for_each(futures.begin(), futures.end(), [&result](auto& f) {
		result += f.get();
		});

	return result;

}
