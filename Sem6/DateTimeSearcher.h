#pragma once

#include <iostream>
#include <regex>
#include <string>

std::vector<std::string> searchDatesAndTimes(std::string& text) {
	std::regex pattern(R"((\d{1,2})\.(\d{1,2})\.(\d{1,2}))");
	auto dBegin = std::sregex_iterator(text.begin(), text.end(), pattern);
	auto dEnd = std::sregex_iterator();
	std::vector<std::string> matches(std::distance(dBegin, dEnd));
	std::transform(dBegin, dEnd, std::back_inserter(matches), [](auto x) {
		return x.str();
		});
	return matches;
}