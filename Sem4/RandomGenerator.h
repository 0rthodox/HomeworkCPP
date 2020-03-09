#pragma once

#include <random>
#include <chrono>
#include <string>
#include <set>

template <typename Int>
class RandomGenerator {
	Int min;
	Int max;
	inline static unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	inline static std::default_random_engine e = std::default_random_engine(seed);
	std::uniform_int_distribution<Int> d;
public:
	RandomGenerator(Int min, Int max) : min(min), max(max), d(min, max) {}
	Int rand() {
		return d(e);
	}
};

class RandomStringGenerator {
protected:
	std::string chars;
	RandomGenerator<size_t> randomGenerator;
public:
	RandomStringGenerator(std::string chars) :
		chars(chars), randomGenerator(0, chars.size() - 1) {}
	virtual std::string generateString(size_t size) {
		std::string generatedString;
		generatedString.resize(size);
		for (auto & ch : generatedString) {
			ch = chars[randomGenerator.rand()];
		}
		return generatedString;
	}
	virtual std::vector<std::string> generateStrings(size_t amount, size_t size) {
		std::vector<std::string> generatedStrings;
		generatedStrings.reserve(amount);
		for (auto i = 0u; i < amount; ++i) {
			generatedStrings.push_back(std::move(generateString(size)));
		}
		return generatedStrings;
	}
};

class RandomUniqueStringGenerator : public RandomStringGenerator {
	std::set<std::string> cache;
public:
	RandomUniqueStringGenerator(std::string chars) : RandomStringGenerator(chars) {}
	std::string generateString(size_t size) override {
		std::string generatedString;
		generatedString.resize(size);
		do {
			for (auto& ch : generatedString) {
				ch = chars[randomGenerator.rand()];
			}
		} while (!cache.insert(generatedString).second);
		return generatedString;
	}
};