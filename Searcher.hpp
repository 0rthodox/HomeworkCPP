#pragma once

#include <regex>
#include <string>
#include <vector>

class Detective {
public:
	std::vector<std::string> searchDomains(std::string& text);
	std::vector<std::string> searchTimes(std::string& text);
	std::vector<std::string> searchTimes(std::string& text);
private:
	std::vector<std::string> basicSearch(std::regex pattern, const std::string& text);
};

std::vector<std::string> Detective::searchDomains(std::string& text) {
	std::regex pattern(R"([_[:alpha:]](\.?\-?\_?\w+)*@\w+(\.\w+)+)");
	std::smatch matches;
	auto dBegin = std::sregex_iterator(text.begin(), text.end(), pattern);
	auto dEnd = std::sregex_iterator();
	std::vector<std::string> domains(std::distance(dBegin, dEnd));
	std::transform(dBegin, dEnd, std::back_inserter(domains), [](auto x) {
		auto address = x.str();
		return address.substr(address.find('@') + 1);
		});
	return domains;
}

std::vector<std::string> searchTimes(std::string& text) {
	std::regex timePattern(R"((([0-1][0-9])|(2[0-3]))(:[0-5][0-9]){2})");
	auto dBegin = std::sregex_iterator(text.begin(), text.end(), timePattern);
	auto dEnd = std::sregex_iterator();
	std::vector<std::string> matches(std::distance(dBegin, dEnd));
	std::transform(dBegin, dEnd, std::back_inserter(matches), [](auto x) {
		return x.str();
		});
	return matches;
}

std::vector<std::string> searchDates(std::string& text) {
	std::regex datePattern(R"((([0-1][0-9]{3})|20[0-9]{2})\.((0[0-9])|(1[0-2]))\.(([0-2][0-9])|(3[0-1])))");
	auto dBegin = std::sregex_iterator(text.begin(), text.end(), datePattern);
	auto dEnd = std::sregex_iterator();
	std::vector<std::string> matches(std::distance(dBegin, dEnd));
	std::transform(dBegin, dEnd, std::back_inserter(matches), [](auto x) {
		return x.str();
		});
	return matches;
}