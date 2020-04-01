#include "FileStringReader.hpp"
#include "CommentDeleter.hpp"
#include "DirectoryViewer.hpp"
#include "Programmer.hpp"
#include "JsonFileSaver.hpp"
#include <string>
#include <iostream>

int main() {
	//second task
	/*std::string path = "Sem7/strings.txt";
	FileStringReader reader(path);
	for (int i = 0; i < 5; ++i) {
		std::cout << reader.readString(i) << std::endl;
	}*/

	//first task
	/*std::string path = "Sem7/input.txt";
	CommentDeleter deleter;
	deleter.deleteComments(path);*/

	//third task
	auto path = std::experimental::filesystem::current_path();
	DirectoryViewer viewer(path, 16);
	viewer(std::cout);

	//fourth task
	/*Programmer john("Jonh", 23, "C++", Programmer::Proficiency::MASTER);
	Programmer alex;
	std::cin >> alex;
	JsonFileSaver jsonSaver(std::filesystem::current_path() / "Sem7", "JSONs");
	jsonSaver("John.txt", john.toJson());
	jsonSaver("Alex.txt", alex.toJson());*/
}
//#include <filesystem>
//#include <fstream>
//#include <iomanip>
//#include <iostream>
//void view_directory(const std::filesystem::path& path)
//{
//	if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
//	{
//		for (const auto& entry : std::filesystem::directory_iterator(path))
//		{
//			auto file_name = entry.path().filename().string();
//
//			std::cout << file_name << std::endl;
//		}
//	}
//}
//int main(int argc, char** argv)
//{
//	view_directory(std::filesystem::current_path());
//
//	system("pause");
//
//	return EXIT_SUCCESS;
//}