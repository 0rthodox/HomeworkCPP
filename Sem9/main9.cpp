#include "Pi.hpp"
#include "SafePQueue.hpp"
#include <iostream>
#include <string>
#include <thread>

int main() {
	//Test 1
	std::cout << PiParallel()() << std::endl;

	//Test 2
	SafePriorityQueue<int, std::greater<int>> queue;

	for (int n : {1, 8, 5, 6, 3, 4, 0, 9, 7, 2})
		queue.push(n);
	while (!queue.empty())
		std::cout << *queue.wait_and_pop() << std::endl;

}