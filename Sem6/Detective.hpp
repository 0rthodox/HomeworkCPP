#pragma once

#include <algorithm>
#include <regex>
#include <string>
#include <vector>

class Detective {
public:
	std::vector<std::string> searchDomains(const std::string& text);
	std::vector<std::string> searchDates(const std::string& text);
	std::vector<std::string> searchTimes(const std::string& text);
private:
	std::vector<std::string> basicSearch(std::regex pattern, const std::string& text);
	std::vector<std::string> extractDomains(std::vector<std::string>&& domains);
};

//Detective public:

std::vector<std::string> Detective::searchDates(const std::string& text) {
	std::regex pattern(R"((([0-1][0-9]{3})|20[0-9]{2})\.((0[0-9])|(1[0-2]))\.(([0-2][0-9])|(3[0-1])))");
	return basicSearch(pattern, text);
}

std::vector<std::string> Detective::searchDomains(const std::string& text) {
	std::regex pattern(R"((\s|\b)[a-zA-Z](\.?\-?\_?\w+)*@\w+(\.\w+)+)");
	return extractDomains(basicSearch(pattern, text));
}

std::vector<std::string> Detective::searchTimes(const std::string& text) {
	std::regex pattern(R"((([0-1][0-9])|(2[0-3]))(:[0-5][0-9]){2})");
	return basicSearch(pattern, text);
}

//Detective private:

std::vector<std::string> Detective::basicSearch(std::regex pattern, const std::string& text) {
	std::smatch matches;
	auto dBegin = std::sregex_iterator(text.begin(), text.end(), pattern);
	auto dEnd = std::sregex_iterator();
	std::vector<std::string> domains(std::distance(dBegin, dEnd));
	std::transform(dBegin, dEnd, std::back_inserter(domains), [](auto x) {
		return x.str();
		});
	return domains;
}


std::vector<std::string> Detective::extractDomains(std::vector<std::string>&& domains) {
	std::for_each(domains.begin(), domains.end(), [](auto& x) {
		x = x.substr(x.find('@') + 1);
		});
	return domains;
}


