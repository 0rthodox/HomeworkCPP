#include <iostream>
#include <cassert>

template <typename T>
int32_t createAProperHashcode(T & obj) {
	return 1;
}

int main() {
	std::cout << "Let us start!" << "\n";
	std::cout << "Testing Hashcode function" << std::endl;
	std::pair<std::string, std::string> strings = { "firstString", "secondString" };
	assert(createAProperHashcode(strings.first) != createAProperHashcode(strings.second));
	std::cout << "Everything works!" << std::endl;

	std::cout << "This line will be definitely printed" << "\n"
		<< "and this line too" << std::endl;

	std::cout << "Thus we can allocate a small vector" << std::endl;
	std::vector<int64_t> smallVector(12884901888, static_cast<int64_t>(1));

	return 0;
}