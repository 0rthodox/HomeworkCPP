#pragma once
#include <set>
#include <fstream>
#include <array>
#include "RandomGenerator.h"
#include "timer.h"
#include <map>


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
	data << "\nTesting " << amount << " numbers:\n";
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

void testTask1() {
	std::ofstream data;
	data.open("Sem4/S4T1.txt");
	//ctIterator<1000, 100000, 10, std::string, std::ofstream&>::ctIterate(testSetVectorArray<std::chrono::milliseconds, 1000>, data);
	{
		data << "Testing big values (mSec)" << std::endl;
		std::vector<std::string> winners;
		winners.push_back(testSetVectorArray<std::chrono::milliseconds, 20000>(data));
		winners.push_back(testSetVectorArray<std::chrono::milliseconds, 30000>(data));
		winners.push_back(testSetVectorArray<std::chrono::milliseconds, 40000>(data));
		winners.push_back(testSetVectorArray<std::chrono::milliseconds, 50000>(data));
		winners.push_back(testSetVectorArray<std::chrono::milliseconds, 60000>(data));
		winners.push_back(testSetVectorArray<std::chrono::milliseconds, 70000>(data));
		winners.push_back(testSetVectorArray<std::chrono::milliseconds, 80000>(data));
		winners.push_back(testSetVectorArray<std::chrono::milliseconds, 90000>(data));
		winners.push_back(testSetVectorArray<std::chrono::milliseconds, 100000>(data));
		winners.push_back(testSetVectorArray<std::chrono::milliseconds, 110000>(data));
		winners.push_back(testSetVectorArray<std::chrono::milliseconds, 120000>(data));
		winners.push_back(testSetVectorArray<std::chrono::milliseconds, 130000>(data));
		winners.push_back(testSetVectorArray<std::chrono::milliseconds, 140000>(data));
		winners.push_back(testSetVectorArray<std::chrono::milliseconds, 150000>(data));
		winners.push_back(testSetVectorArray<std::chrono::milliseconds, 160000>(data));
		winners.push_back(testSetVectorArray<std::chrono::milliseconds, 170000>(data));
		winners.push_back(testSetVectorArray<std::chrono::milliseconds, 180000>(data));
		winners.push_back(testSetVectorArray<std::chrono::milliseconds, 190000>(data));
		winners.push_back(testSetVectorArray<std::chrono::milliseconds, 200000>(data));
		std::map<std::string, int> results;
		for (const auto& collection : winners) {
			results[collection]++;
		}
		for (const auto& [collection, wins] : results) {
			data << "\nWinners:\n";
			data << collection << ": " << wins << " times of " << winners.size() << "\n" << std::endl;
		}
	}
	{
		data << "Testing small values (muSec)" << std::endl;
		std::vector<std::string> winners;
		winners.push_back(testSetVectorArray<std::chrono::microseconds, 50>(data));
		winners.push_back(testSetVectorArray<std::chrono::microseconds, 100>(data));
		winners.push_back(testSetVectorArray<std::chrono::microseconds, 200>(data));
		winners.push_back(testSetVectorArray<std::chrono::microseconds, 300>(data));
		winners.push_back(testSetVectorArray<std::chrono::microseconds, 400>(data));
		winners.push_back(testSetVectorArray<std::chrono::microseconds, 500>(data));
		winners.push_back(testSetVectorArray<std::chrono::microseconds, 1000>(data));
		winners.push_back(testSetVectorArray<std::chrono::microseconds, 2000>(data));
		winners.push_back(testSetVectorArray<std::chrono::microseconds, 3000>(data));
		winners.push_back(testSetVectorArray<std::chrono::microseconds, 5000>(data));
		winners.push_back(testSetVectorArray<std::chrono::microseconds, 10000>(data));
		std::map<std::string, int> results;
		for (const auto& collection : winners) {
			results[collection]++;
		}
		for (const auto& [collection, wins] : results) {
			data << "\nWinners:\n";
			data << collection << ": " << wins << " times of " << winners.size() << "\n" << std::endl;
		}

	}
	data.close();
}
