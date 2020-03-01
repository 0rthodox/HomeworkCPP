#pragma once
#include <vector>
#include <iostream>
#include "timer.h"
#include "RandomGenerator.h"
#include <fstream>
#include <array>
#include <deque>
#include <list>
#include <forward_list>
#include <iomanip>
#include <map>
#include <set>

void test2() {
	std::cout << "Testing task 2" << std::endl;
	std::array<unsigned short, 250000> holder;
	RandomGenerator rg(static_cast<unsigned short>(0), static_cast<unsigned short>(65535));
	std::cout << "Stack is not able to hold much more than " << holder.size() << " short ints" << std::endl;

	std::ofstream dataSort;
	dataSort.open("dataSort.txt");
	std::set<std::string> set;
	std::multiset<std::string> multiset;
	for (int i = 0; i < 10; ++i) {
		dataSort << "Attempt " << i << std::endl;
		{
			std::cout << "Filling array. Time needed[ms]: ";
			Timer<std::chrono::milliseconds> t;
			for (auto& i : holder) {
				i = rg.rand();
			}
		}
		std::map<long long, std::string> count;
		{
			std::cout << "Sorting vector" << std::endl;
			auto vector = std::vector(holder.begin(), holder.end());
			Timer<std::chrono::milliseconds> t;
			std::sort(vector.begin(), vector.end());
			auto dur = t.getDuration();
			count[dur] = "vector";
			dataSort << std::setw(12) << "vector: " << std::setw(10) << dur << std::endl;
		}
		{
			std::cout << "Sorting deque" << std::endl;
			auto deque = std::deque(holder.begin(), holder.end());
			Timer<std::chrono::milliseconds> t;
			std::sort(deque.begin(), deque.end());
			auto dur = t.getDuration();
			count[dur] = "deque";
			dataSort << std::setw(12) << "deque: " << std::setw(10) << dur << std::endl;
		}
		{
			std::cout << "Sorting list (method)" << std::endl;
			auto list = std::list(holder.begin(), holder.end());
			Timer<std::chrono::milliseconds> t;
			list.sort();
			auto dur = t.getDuration();
			count[dur] = "list";
			dataSort << std::setw(12) << "list (m): " << std::setw(10) << dur << std::endl;
		}
		{
			std::cout << "Sorting forward list(method)" << std::endl;
			auto forward_list = std::forward_list(holder.begin(), holder.end());
			Timer<std::chrono::milliseconds> t;
			forward_list.sort();
			auto dur = t.getDuration();
			count[dur] = "forwardlist";
			dataSort << std::setw(12) << "flist (m): " << std::setw(10) << dur << std::endl;
		}
		{
			std::cout << "Sorting array" << std::endl;
			Timer<std::chrono::milliseconds> t;
			std::sort(holder.begin(), holder.end());
			auto dur = t.getDuration();
			count[dur] = "array";
			dataSort << std::setw(12) << "array: " << std::setw(10) << dur << std::endl;
		}
		set.insert(count.begin()->second);
		multiset.insert(count.begin()->second);
		dataSort << std::endl;
	}
	std::map<int, std::string> finalMap;
	for (const auto& container : set) {
		finalMap[multiset.count(container)] = container;
	}
	dataSort << "Final Score:" << std::endl;
	for (const auto& [score, container] : finalMap) {
		dataSort << std::setw(10) << container << ": " << std::setw(10) << score << std::endl;
	}
	dataSort << "Winner:" << std::endl;
	dataSort << finalMap.rbegin()->second << std::endl;
	dataSort.close();
}