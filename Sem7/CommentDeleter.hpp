#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <vector>



class CommentDeleter {
public:
	void deleteComments(std::string& fileName) {
		enum class State {
			STARTING,
			INSIDE_SINGLE,
			INSIDE_MULTI,
			INSIDE_STRING,
			OUTSIDE,
			NOT_FINISHING_STRING,
			FINISHING_MULTI
		} state = State::OUTSIDE;
		auto contents = readFile(fileName);
		std::vector<char> results;
		size_t pos = 0;
		for (auto c : contents) {
			switch (state) {
			case State::OUTSIDE:
				if (c == '/') {
					state = State::STARTING;
				}
				else if (c == '"') {
					state = State::INSIDE_STRING;
				}
				results.push_back(c);
				break;
			case State::STARTING:
				if (c == '/') {
					state = State::INSIDE_SINGLE;
					results.erase(std::prev(results.end(), 1));
				} else if (c == '*') {
					state = State::INSIDE_MULTI;
					results.erase(std::prev(results.end(), 1));
				} else {
					state = State::OUTSIDE;
					results.push_back(c);
				}
				break;
			case State::INSIDE_MULTI:
				if (c == '*') {
					state = State::FINISHING_MULTI;
				}
				break;
			case State::INSIDE_SINGLE:
				if (c == '\r') {
					state = State::OUTSIDE;
					results.push_back(c);
				}
				break;
			case State::INSIDE_STRING:
				if (c == '\\') {
					state = State::NOT_FINISHING_STRING;
				} else if (c == '"') {
					state = State::OUTSIDE;
				}
				results.push_back(c);
				break;
			case State::NOT_FINISHING_STRING:
				if (c == '"') {
					state = State::INSIDE_STRING;
				}
				results.push_back(c);
				break;
			case State::FINISHING_MULTI:
				if (c == '/') {
					state = State::OUTSIDE;
				}
				else {
					state = State::INSIDE_MULTI;
				}
				break;
			}			
		}
		std::ofstream writer(fileName, std::ios::binary);
		for (auto c : results) {
			writer << c;
		}
		
	}

private:
	std::vector<char> readFile(std::string& fileName) {
		std::vector<char> result;
		std::ifstream reader(fileName, std::ios::binary);
		char c;
		while (reader.get(c)) {
			result.push_back(c);
		}
		return result;
	}	
};