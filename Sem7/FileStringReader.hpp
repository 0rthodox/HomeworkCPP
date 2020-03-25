#pragma once
#include <string>
#include <fstream>
#include <iostream>

class FileStringReader {
public:

	FileStringReader(std::string& path) : currentPath(path) {

	}

private:

	auto determineSize(std::istream& fileReader) {
		std::string testString;
		fileReader >> testString;
		fileReader.seekg(0);
		return testString.size() - 1;
	}

public:

	std::string readString(size_t i) {
		std::ifstream fileReader(currentPath);
		auto size = determineSize(fileReader);
		fileReader.seekg(size * i, std::ios::beg);
		std::string readString;
		fileReader >> readString;
		return readString;
	}
private:

	std::string currentPath;
};


