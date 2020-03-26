#pragma once
#include <filesystem>
#include <iostream>
#include <chrono>


class DirectoryViewer {
public:
	DirectoryViewer(const std::experimental::filesystem::path& path, size_t width = 32) : m_path(path), m_width(width) {}
	bool operator()(std::ostream& viewer) {
		if (std::experimental::filesystem::exists(m_path) && std::experimental::filesystem::is_directory(m_path)) {
			viewer.width(m_width);
			viewer  << "NAME"  << "EXTENSION" << "LAST MODIFY TIME" << std::endl;
			for (const auto& file : std::experimental::filesystem::directory_iterator(m_path)) {
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
				viewer << stem  << extension
					<< std::asctime(std::localtime(&convertedlastModifyTime)) << std::endl;
			}
			return true;
		}		else {
			return false;
		}
	}
private:
	std::experimental::filesystem::path m_path;
	size_t m_width;
};