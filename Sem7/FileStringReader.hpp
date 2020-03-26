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
		std::getline(fileReader, testString);
		fileReader.seekg(0);
		return testString.size();
	}


public:
	std::string readString(size_t i) {
		std::ifstream fileReader(currentPath);
		auto size = determineSize(fileReader);
		fileReader.seekg((size + 2) * i, std::ios::beg);
		std::string readString;
		std::getline(fileReader, readString);
		return readString;
	}

private:
	std::string currentPath;
};


