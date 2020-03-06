#pragma once

#include <cassert>
#include <map>
#include "hashFloating.h"

void testTask2() {
	hashFloating<double> myHash;
	fastHashFloating<double> myFastHash;
	std::hash<double> stdHash;
	std::ofstream data;
	data.open("Sem4/S4T2.txt");
	long long myTime, stdTime, myFastTime;
	{
		Timer<std::chrono::milliseconds> t;
		for (double iteratingValue = 0.98745681; iteratingValue < 1; iteratingValue += 0.00000100) {
			auto equalIteratingValue = iteratingValue;
			assert(myHash(iteratingValue) == myHash(equalIteratingValue));
		}
		myTime = t.getDuration();
	}
	{
		Timer<std::chrono::milliseconds> t;
		for (double iteratingValue = 0.98745681; iteratingValue < 1; iteratingValue += 0.00000100) {
			auto equalIteratingValue = iteratingValue;
			assert(myFastHash(iteratingValue) == myFastHash(equalIteratingValue));
		}
		myFastTime = t.getDuration();
	}
	{
		Timer<std::chrono::milliseconds> t;
		for (double iteratingValue = 0.98745681; iteratingValue < 1; iteratingValue += 0.00000100) {
			auto equalIteratingValue = iteratingValue;
			assert(stdHash(iteratingValue) == stdHash(equalIteratingValue));
		}
		stdTime = t.getDuration();
	}

	{
		std::map<size_t, int> map;
		for (double iteratingValue = 0.98745681; iteratingValue < 1; iteratingValue += 0.00000100) {
			map[myHash(iteratingValue)]++;
		}
		auto collisions = 0;
		for (const auto& [hash, amount] : map) {
			if (amount > 1) {
				collisions++;
			}
		}
		data << "Collisions in my hash function: " << collisions << '\n';
	}
	{
		std::map<size_t, int> map;
		for (double iteratingValue = 0.98745681; iteratingValue < 1; iteratingValue += 0.00000100) {
			map[stdHash(iteratingValue)]++;
		}
		auto collisions = 0;
		for (const auto& [hash, amount] : map) {
			if (amount > 1) {
				collisions++;
			}
		}
		data << "Collisions in standard hash function: " << collisions << '\n';
	}
	{
		std::map<size_t, int> map;
		for (double iteratingValue = 0.98745681; iteratingValue < 1; iteratingValue += 0.00000100) {
			map[myFastHash(iteratingValue)]++;
		}
		auto collisions = 0;
		for (const auto& [hash, amount] : map) {
			if (amount > 1) {
				collisions++;
			}
		}
		data << "Collisions in my fast hash function: " << collisions << '\n';
	}
	data << "Assertion successful\n" <<
		"My hash function's time: " << myTime << "\n" <<
		"Standard hash function's time: " << stdTime << "\n" <<
		"My fast hash function's time: " << myFastTime << "\n";
	data.close();
}