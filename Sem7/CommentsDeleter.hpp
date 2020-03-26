#pragma once
#include <fstream>
#include <iterator>
#include <filesystem>

class CommentsDeleter {
public:
	CommentsDeleter(std::string& fileName) {

	}
	void operator()() {
		std::string tempFile = copyFile();
		std::istreambuf_iterator<char> inputIt = std::istreambuf_iterator<char>(std::ifstream(tempFile));
		std::istreambuf_iterator<char> end;
		std::ostreambuf_iterator<char> outputIt(std::ofstream(tempFile));
		/*while (inputIt != end) {

		}*/
	}

private:
	std::string copyFile() {
		std::string copiedFileName = "_COPIED_TEMPORARY_" + fileName;
		std::experimental::filesystem::copy_file(fileName, copiedFileName);
		return copiedFileName;
	}
	std::string fileName;

};