#include <numeric>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <random>
#include <chrono>
#include "RandomGenerator.h"
#include <unordered_set>

#define RANGE(s) s.begin(), s.end()

#define PRINTC std::cout <<

#define EOL << std::endl

#define PRINTC_INT_RANGE(s) std::copy(RANGE(s), std::ostream_iterator<int>(std::cout, " "))

template <typename T>
std::ostream& operator<< (std::ostream& ostr, const std::vector<T>& collection) {
	ostr << "{ ";
	std::copy(RANGE(collection), std::ostream_iterator<int>(ostr, " "));
	ostr << '}';
	return ostr;
}

int main() {

	//TASK 1
	PRINTC 1 EOL;
	std::vector<int> sequence;
	sequence.resize(10);
	std::iota(RANGE(sequence), 1);
	PRINTC sequence EOL;

	//TASK 2
	PRINTC 2 EOL;
	PRINTC "Additional numbers:" EOL;
	std::copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), std::back_inserter(sequence));
	PRINTC sequence EOL;

	//TASK 3
	PRINTC 3 EOL;
	auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
	std::shuffle(RANGE(sequence),
		std::default_random_engine(seed));
	PRINTC sequence EOL;

	//TASK 4
	PRINTC 4 EOL;

	//1:
	//sequence.erase(std::unique(RANGE(sequence)), sequence.end());
	//can be used only to remove consecutive elements

	//2:
	//std::sort(RANGE(sequence));
	//sequence.erase(std::unique(RANGE(sequence)), sequence.end());
	//all duplicates are removed but the range is sorted

	//3:
	std::unordered_set<int> uniqueSequence(RANGE(sequence));
	sequence.resize(uniqueSequence.size());
	std::move(RANGE(uniqueSequence), sequence.begin());
	//all duplicates are removed
	
	PRINTC sequence EOL;

	//TASK 5
	PRINTC 5 EOL;
	auto oddCount = std::count_if(RANGE(sequence), [](auto x) {
		return (x % 2);
		});
	PRINTC "Odd numbers: " << std::move(oddCount) EOL;

	//TASK 6
	PRINTC 6 EOL;
	auto mmElements = std::minmax_element(RANGE(sequence));
	PRINTC "Min = " << *mmElements.first << ", max = " << *mmElements.second EOL;

	//TASK 7
	PRINTC 7 EOL;
	auto primeIter = std::find_if(RANGE(sequence), [](auto x) {
		for (auto i = 1; i <= sqrt(x); ++i) {
			if (!(x % i)) {
				return true;
			}
		}
		return false;
		});
	PRINTC "Prime number: " << (primeIter == sequence.end() ? std::to_string(*primeIter) : "Absent") EOL;

	//TASK 8
	PRINTC 8 EOL;
	std::transform(RANGE(sequence), sequence.begin(), [](auto x) {
		return x * x;
		});
	PRINTC sequence EOL;


	//TASK 9
	PRINTC 9 EOL;
	RandomGenerator<int> randomGenerator(*mmElements.first, *mmElements.second);
	std::vector<int> sSequence;
	std::generate_n(std::back_inserter(sSequence), sequence.size(), [&randomGenerator](){
		return randomGenerator.rand();
		});
	PRINTC sSequence EOL;

	//TASK 10
	PRINTC 10 EOL;
	PRINTC "Sum = " << std::accumulate(RANGE(sSequence), 0) EOL;

	//TASK 11
	PRINTC 11 EOL;
	auto amount = RandomGenerator(1llu, sSequence.size() - 1).rand();
	std::for_each_n(sSequence.begin(), amount, [](auto& x) {
		x = 1;
		});
	PRINTC sSequence EOL;

	//TASK 12
	PRINTC 12 EOL;
	std::vector<int> tSequence;
	std::transform(RANGE(sequence), sSequence.begin(), std::back_inserter(tSequence), [](auto x, auto y) {
		return x - y;
		});
	PRINTC tSequence EOL;
	
	//TASK 13
	PRINTC 13 EOL;
	std::replace_if(RANGE(tSequence), [](auto x) {
		return x < 0;
		}, 0);
	PRINTC tSequence EOL;

	//TASK 14
	PRINTC 14 EOL;
	tSequence.erase(std::remove_if(RANGE(tSequence), [](auto x) {
		return x == 0;
		}), tSequence.end());
	PRINTC tSequence EOL;


	//TASK 15
	PRINTC 15 EOL;
	std::reverse(RANGE(tSequence));
	PRINTC tSequence EOL;


	//TASK 16
	PRINTC 16 EOL;
	std::nth_element(tSequence.begin(), std::next(tSequence.begin(), 2), tSequence.end(), std::greater<int>());
	PRINTC "Three greatest elements: " << tSequence[0]
		<< ' ' << tSequence[1] << ' ' << tSequence[2] EOL;
	
	//TASK 17
	PRINTC 17 EOL;
	std::sort(RANGE(sequence));
	std::sort(RANGE(sSequence));
	PRINTC sequence EOL;
	PRINTC sSequence EOL;


	//TASK 18
	PRINTC 18 EOL;
	std::vector<int> fSequence;
	std::merge(RANGE(sequence), RANGE(sSequence), std::back_inserter(fSequence));
	PRINTC fSequence EOL;


	//TASK 19
	PRINTC 19 EOL;
	auto eRange = std::equal_range(RANGE(fSequence), 1);
	PRINTC "Should be inserted between values: " << *eRange.first << ' ' << *eRange.second EOL;

	//TASK 20
	PRINTC 20 EOL;
	PRINTC sequence EOL;
	PRINTC ' ' EOL;
	PRINTC sSequence EOL;
	PRINTC ' ' EOL;
	PRINTC tSequence EOL;
	PRINTC ' ' EOL;
	PRINTC fSequence EOL;
}