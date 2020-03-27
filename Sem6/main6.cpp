#include "Detective.hpp"
#include "Transliterator.h"

int main() {
	//Second task
	/*system("chcp 1251");
	std::string s;
	std::cin >> s;
	Transliterator transliterator;
	std::cout << transliterator(s);*/
	
	//Third-Fourth task
	std::string domains = "g@c.com.ru incorrectemail@email correct-email@ram.sg 1incorrectemail@e.r mememem popov.nv@phystech.edu";
	std::string dates = "2009.31.12 2009.12.31 3009.12.31 2009.12.32";
	std::string times = "23:55:55 24:00:01 23:60:01 23:01:60";

	Detective d;
	for (auto& date : d.searchDates(dates)) {
		std::cout << date << std::endl;
	}
	for (auto& time : d.searchTimes(times)) {
		std::cout << time << std::endl;
	}
	for (auto& domain : d.searchDomains(domains)) {
		std::cout << domain << std::endl;
	}
}