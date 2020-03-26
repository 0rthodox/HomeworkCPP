#include "FileStringReader.hpp"
#include "CommentDeleter.hpp"
#include "CommentsDeleter.hpp"
#include <string>
#include <iostream>

int main() {
	//second task
	/*String path = "Sem7/strings.txt";
	FileStringReader reader(path);
	std::cout << reader.readString(3);*/

	//first task
	/*std::string path = "Sem7/comments.txt";
	CommentsDeleter deleter(path);
	deleter();*/

	std::string path = "Sem7/comments.txt";
	CommentDeleter deleter;
	deleter.deleteComments(path);

}