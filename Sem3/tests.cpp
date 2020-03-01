#include <tuple>
#include <vector>
#include <iostream>
#include "TupleIterate.h"
#include "timer.h"
#include "RandomGenerator.h"
#include "task2.h"
#include "task1.h"



void test3() {
	std::cout << "Testing task 3" << std::endl;
	{
		auto testedTuple = std::make_tuple(3, "0rthodox", 'c');
		iterateThrough(testedTuple, [](auto x) {
			std::cout << x << std::endl; });
	}
}

int main() {

	test3();
	test2();
	test1();	
	system("pause");
	return 0;
}