#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include "DomainSearcher.h"
#include "DateTimeSearcher.h"
#include "Transliterator.h"

int main(int argc, char** argv)
{
	std::string string = "np@3ka.dorm incorrectEmail@emailHost.3 ";
	auto domains = searchDomains(string);
	for (auto domain : domains) {
		std::cout << domain << std::endl;
	}
	string = "25.12.99dfgeg34.34.35";
	auto dates = searchDatesAndTimes(string);
	for (auto date : dates) {
		std::cout << date << std::endl;
	}

	Transliterator t;
	std::string s;
	std::cin >> s;
	std::cout << t.transliterate(s);

	return EXIT_SUCCESS;
}