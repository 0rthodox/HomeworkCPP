#pragma once
#include "json.hpp"
#include <filesystem>
#include <fstream>
#include <iomanip>

using nlohmann::json;

class JsonFileSaver {
public:
	JsonFileSaver(const std::filesystem::path& path, const std::string& new_dir) : path(canonical(path) / new_dir) {
		std::filesystem::create_directory(this->path);
	}
	void operator()(const std::string& name, const json& toSave) {
		std::filesystem::path currentPath = path / name;
		std::fstream output(currentPath.string(), std::ios::out);
		output << std::setw(4) << toSave;	//	???Does not work???
//		output << std::setw(4) << operator<<(output, toSave);  //???Does not work either???
	}
private:
	std::filesystem::path path;
};