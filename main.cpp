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
	return 0;
}