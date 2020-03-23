#pragma once

#include <iostream>
#include <regex>
#include <string>

std::vector<std::string> searchDomains(std::string& text) {
	std::regex pattern(R"([a-zA-Z0-9]+@[a-zA-Z0-9]+\.[a-zA-Z]+)");
	std::smatch matches;
	auto dBegin = std::sregex_iterator(text.begin(), text.end(), pattern);
	auto dEnd = std::sregex_iterator();
	std::vector<std::string> domains(std::distance(dBegin, dEnd));
	std::transform(dBegin, dEnd, std::back_inserter(domains), [](auto x) {
		return x.str();
		});
	return domains;
}