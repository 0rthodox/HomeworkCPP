#pragma once
#include <algorithm>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

template < typename Iterator, typename Func >
struct forEach_block
{
	void operator()(Iterator first, Iterator last, Func result)
	{
		std::for_each(first, last, result); // !
	}
};

template < typename Iterator, typename Func >
void forEachUnsafe(Iterator first, Iterator last, Func f)
{
	const std::size_t length = std::distance(first, last);

	if (!length)
		return;

	const std::size_t min_per_thread = 25;
	const std::size_t max_threads =
		(length + min_per_thread - 1) / min_per_thread;

	const std::size_t hardware_threads =
		std::thread::hardware_concurrency();

	const std::size_t num_threads =
		std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads) / 2;

	const std::size_t block_size = length / num_threads;

	std::vector < std::thread > threads(num_threads - 1);

	Iterator block_start = first;

	for (std::size_t i = 0; i < (num_threads - 1); ++i)
	{
		Iterator block_end = block_start;
		std::advance(block_end, block_size);

		threads[i] = std::thread(
			forEach_block < Iterator, Func >(),
			block_start, block_end, f); // !

		block_start = block_end;
	}

	forEach_block < Iterator, Func >()(block_start, last, f);

	std::for_each(threads.begin(), threads.end(),
		std::mem_fn(&std::thread::join));
}