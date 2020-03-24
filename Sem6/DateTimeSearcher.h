#pragma once

#include <iostream>
#include <regex>
#include <string>
#include <sstream>

bool isDate(int y, int m, int d) {
	return (m > 0 && m <= 12 && d > 0 && d < 31);
}

bool isTime(int h, int m, int s) {
	return(s > 0 && s <= 60 && m > 0 && m <= 60);
}

bool isValid(std::string s) {
	std::stringstream ss;
	ss << s;
	int yearHour;
	ss >> yearHour;
	ss.ignore(1);
	int monthMin;
	ss >> monthMin;
	ss.ignore(1);
	int daySec;
	ss >> daySec;
	return isDate(yearHour, monthMin, daySec) || isTime(yearHour, monthMin, daySec);

}

std::vector<std::string> searchDatesAndTimes(std::string& text) {
	std::regex pattern(R"((\d{1,2})\.(\d{1,2})\.(\d{1,2}))");
	auto dBegin = std::sregex_iterator(text.begin(), text.end(), pattern);
	auto dEnd = std::sregex_iterator();
	std::vector<std::string> matches(std::distance(dBegin, dEnd));
	std::transform(dBegin, dEnd, std::back_inserter(matches), [](auto x) {
		auto s = x.str();
		if (isValid(s));
		return s;
		});
	return matches;
}