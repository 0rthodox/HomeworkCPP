#include <tuple>
#include <iostream>
#include "TupleIterate.h"


int main() {
	std::cout << "Testing task 3" << std::endl;
	{
		auto testedTuple = std::make_tuple(3, "0rthodox", 'c');
		iterateThrough(testedTuple, [](auto x) {
			std::cout << x << std::endl; });
		return 0;
	}
}