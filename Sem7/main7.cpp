#include "FileStringReader.hpp"
#include "CommentDeleter.hpp"
#include "CommentsDeleter.hpp"
#include "DirectoryViewer.hpp"
#include "Programmer.hpp"
#include "JsonFileSaver.hpp"
#include <string>
#include <iostream>

int main() {
	//second task
	/*String path = "Sem7/strings.txt";
	FileStringReader reader(path);
	std::cout << reader.readString(3);*/

	//first task
	std::string path = "Sem7/input.txt";
	CommentDeleter deleter;
	deleter.deleteComments(path);

	//third task
	/*auto path = std::experimental::filesystem::current_path();
	DirectoryViewer viewer(path);
	viewer(std::cout);*/

	//fourth task
	/*Programmer john("Jonh", 23, "C++", Programmer::Proficiency::MASTER);
	Programmer alex;
	std::cin >> alex;
	JsonFileSaver jsonSaver(std::filesystem::current_path() / "Sem7", "JSONs");
	jsonSaver("John.txt", john.toJson());
	jsonSaver("Alex.txt", alex.toJson());*/
}