#pragma once
#include <set>
#include <fstream>
#include <array>
#include "RandomGenerator.h"
#include "timer.h"
#include <map>


namespace s4 {
	template<size_t InitAmount, size_t MaxAmount, size_t Step, typename Func, typename Arg>
	class ctIterator {
	public:
		static void ctIterate(Func* func(Arg), Arg arg) {
			func(arg);
			ctIterator<InitAmount + Step, MaxAmount, Step, Func, Arg>::ctIterate(func, arg);
		}
	};
	template<size_t MaxAmount, size_t Step, typename Func, typename Arg>
	class ctIterator<MaxAmount, MaxAmount, Step, Func, Arg> {
	public:
		static void ctIterate(Func* func(Arg), Arg arg) {
			func(arg);
		}
	};


	template< typename Accuracy, size_t amount>
	std::string testSetVectorArray(std::ofstream& data) {
		data << "Testing " << amount << " numbers:\n";
		RandomGenerator randomGenerator(static_cast<short>(0), static_cast<short>(32767));
		std::vector<short> numbers;
		numbers.resize(amount);
		for (auto& number : numbers) {
			number = randomGenerator.rand();
		}
		std::map<long long, std::string> times;
		{
			std::set<short> set;
			Timer<Accuracy> timer;
			for (size_t i = 0; i < numbers.size(); ++i) {
				set.insert(numbers[i]);
			}
			auto setTime = timer.getDuration();
			data << "Set's time: " << setTime << std::endl;
			times.insert({ setTime, "set" });
		}
		{
			std::vector<short> vector;
			vector.reserve(amount);
			Timer<Accuracy> timer;
			for (size_t i = 0; i < numbers.size(); ++i) {
				vector.push_back(numbers[i]);
			}
			std::sort(vector.begin(), vector.end());
			auto vectorTime = timer.getDuration();
			data << "Vector's time: " << vectorTime << std::endl;
			times.insert({ vectorTime, "vector" });
		}
		{
			std::array<short, amount> array;
			Timer<Accuracy> timer;
			for (size_t i = 0; i < numbers.size(); ++i) {
				array[i] = numbers[i];			
			}
			std::sort(array.begin(), array.end());
			auto arrayTime = timer.getDuration();
			data << "Array's time: " << arrayTime << std::endl;
			times.insert({ arrayTime, "array" });
		}	
		return times.begin()->second;
	}

}
