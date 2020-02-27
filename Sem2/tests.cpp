#include <vector>
#include <iostream>
#include <numeric>
#include <cassert>
#include "vectorBinarySearch.h"
#include <chrono>
#include <memory>
#include "timer.h"
#include "uniqueCasts.h"
#include "SmartTree.h"

using ms = std::chrono::milliseconds;

struct Base
{
	virtual std::string f() const { return "Base"; }
	virtual ~Base() {}
};

struct Derived : Base
{
	std::string f() const override
	{
		return "Derived";
	}
	~Derived() {}
};

int main() {
	
	std::cout << "\nTesting task 1\n" << std::endl;

	{
		auto basePtr = std::make_unique<Base>();

		auto derivedPtr = std::make_unique<Derived>();

		assert(basePtr->f() == "Base" && derivedPtr->f() == "Derived");
		std::cout << "Initialization OK" << std::endl;
		
		basePtr = static_pointer_cast<Base>(derivedPtr);
		assert(basePtr->f() == "Derived");
		std::cout << "Upcast OK" << std::endl;

		auto downcastedPtr = dynamic_pointer_cast<Derived>(basePtr);
		if (downcastedPtr)
		{
			assert(downcastedPtr->f() == "Derived");
			std::cout << "Downcast OK" << std::endl;
		}
		else {
			std::cout << "Downcast failed: empty pointer" << std::endl;
		}
	}

	std::cout << "\nTesting task 2\n" << std::endl;
	{
		SmartTree<int> tree;
		tree.add(231);
		tree.add(-46);
		tree.add(1);
		tree.read();
	}
	std::cout << "Tree deleted successfully" << std::endl;
		
	std::cout << "\nTesting task 3\n" << std::endl;

	{
		std::vector<int> testVector(7);
		std::iota(testVector.begin(), testVector.end(), 1);

		{
			for (auto element : testVector) {
				assert(vectorBinarySearch(testVector, element) == true);
			}
			std::cout << "Existing elements OK" << std::endl;
		}

		{
			assert(vectorBinarySearch(testVector, 10) == false);
			std::cout << "Out of bounds OK" << std::endl;
		}

		{
			testVector[3] = 3;
			assert(vectorBinarySearch(testVector, 4) == false);
			std::cout << "Non-existing element OK" << std::endl;
		}

	}	

	std::cout << "\nTesting task 4\n" << std::endl;

	{
		std::cout << "One of these numbers should approximately be a sum of other two" << std::endl;
		MultiTimer<ms> wrappingTimer, mainTimer;
		std::string s(100000000, 's');
		{
			mainTimer.pause();
			MultiTimer<ms> wrappedTimer;
			std::string f(100000000, 'f');
			mainTimer.resume();
		}
		std::string f(100000000, 'f');
	}

	std::cout << "\nTesting task 3*\n" << std::endl;

	{
		std::vector<int> testVector(7);
		std::iota(testVector.begin(), testVector.end(), 1);

		{
			for (auto element : testVector) {
				assert(recursiveSearch(testVector, element) == true);
			}
			std::cout << "Existing elements OK" << std::endl;
		}

		{
			assert(recursiveSearch(testVector, 10) == false);
			std::cout << "Out of bounds OK" << std::endl;
		}

		{
			testVector[3] = 3;
			assert(recursiveSearch(testVector, 4) == false);
			std::cout << "Non-existing element OK" << std::endl;
		}

	}

}


