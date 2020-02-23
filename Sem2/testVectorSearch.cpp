#include <vector>
#include <iostream>
#include <numeric>
#include <cassert>
#include "vectorBinarySearch.h"

int main() {
	std::vector<int> testVector(7);
	std::iota(testVector.begin(), testVector.end(), 1);

	{
		for (auto element : testVector) {
			assert(*vectorBinarySearch(testVector, element) == element);
		}
		std::cout << "Existing elements OK" << std::endl;
	}

	{
		assert(*vectorBinarySearch(testVector, 10) == 7);
		std::cout << "Out of bounds OK" << std::endl;
	}

	{
		testVector[3] = 3;
		assert(*vectorBinarySearch(testVector, 4) == 3);
		std::cout << "Non-existing element OK" << std::endl;
	}	   	
}