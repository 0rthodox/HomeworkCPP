#include "FileStringReader.hpp"
#include <string>
#include <iostream>

int main() {
	std::string path = "Sem7/strings.txt";
	FileStringReader reader(path);
	std::cout << reader.readString(3);

}