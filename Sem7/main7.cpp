#include "FileStringReader.hpp"
#include "CommentDeleter.hpp"
#include "CommentsDeleter.hpp"
#include "DirectoryViewer.hpp"
#include <string>
#include <iostream>

int main() {
	//second task
	/*String path = "Sem7/strings.txt";
	FileStringReader reader(path);
	std::cout << reader.readString(3);*/

	//first task
	/*std::string path = "Sem7/comments.txt";
	CommentDeleter deleter;
	deleter.deleteComments(path);*/

	//third task
	auto path = std::experimental::filesystem::current_path();
	DirectoryViewer viewer(path);
	viewer(std::cout);
}