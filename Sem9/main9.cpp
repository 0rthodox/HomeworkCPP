#include "Pi.hpp"
#include "SafePQueue.hpp"
#include "Comparisons.hpp"
#include "DNASearcher.hpp"
#include <iostream>
#include <string>
#include <thread>

int main() {
	////Test 1
	//std::cout << PiParallel()() << std::endl;

	////Test 3
	//SafePriorityQueue<int, std::deque<int>, std::greater<int>> queue0;
	//SafePriorityQueue<int, std::deque<int>, std::greater<int>> queue2;

	//for (int n : {1, 8, 5, 6, 3, 4, 0, 9, 7, 2})
	//	queue0.push(n);

	//SafePriorityQueue queue{ queue0 };
	//for (int n : {21, 28, 25, 26, 23, 24, 20, 29, 27, 22})
	//	queue2.push(n);
	//queue.swap(queue2);
	//while (!queue.empty()) {
	//	std::cout << *queue.wait_and_pop() << std::endl;
	//	std::cout << *queue2.wait_and_pop() << std::endl;
	//}

	////Test 2
	//auto x = DNASearcher("agtccgatcgatgctcgatcgtcgctaatcgctagccatcgatgcatcgatcatcgactgcagccagtcgacttcagtagcatg")("gca");
	//std::for_each(x.begin(), x.end(), [](auto x) {
	//	std::cout << x << std::endl;
	//	});

	//Test 4
	//testStack<boost::lockfree::queue, int>(1, 13);
	testStack<Threadsafe_Queue, int>(1, 13);

}