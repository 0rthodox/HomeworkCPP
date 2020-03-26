#pragma once
#include <filesystem>
#include <iostream>
#include <chrono>


class DirectoryViewer {
public:
	DirectoryViewer(const std::string& path, unsigned width = 32) : path(path), width(width) {}
	DirectoryViewer(const std::experimental::filesystem::path& path, unsigned width = 32) : path(path), width(width) {}
	bool operator()(std::ostream& viewer) {
		if (std::experimental::filesystem::exists(path) && std::experimental::filesystem::is_directory(path)) {
			viewer << std::setw(width) << "NAME" << std::setw(width) << "EXTENSION"
				<< std::setw(width) << "LAST MODIFY TIME" << std::endl;
			for (const auto& file : std::experimental::filesystem::directory_iterator(path)) {
				auto stem = file.path().stem().string();
				std::string extension;
				if (std::experimental::filesystem::is_directory(file)) {
					extension = "DIR";
				}
				else {
					extension = file.path().extension().string();
				}
				auto lastModifyTime = std::experimental::filesystem::last_write_time(file);
				std::time_t convertedlastModifyTime = decltype(lastModifyTime)::clock::to_time_t(lastModifyTime);
				viewer << std::setw(width) << stem << std::setw(width) << extension
					<< std::setw(width) << std::asctime(std::localtime(&convertedlastModifyTime)) << std::endl;
			}
			return true;
		}		else {
			return false;
		}
	}
private:
	std::experimental::filesystem::path path;
	unsigned width;
};