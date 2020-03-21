#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <locale>
#include <sstream>

#include <Windows.h> 
#include "../CurrencyConverter.h"

void show_currency_symbol(const std::string& locale_name)
{
	std::cout << locale_name << " : " <<
		std::use_facet < std::moneypunct < char, false > >(
			std::locale(locale_name)).curr_symbol() << std::endl;
}

int main()
{
	convert();
	return EXIT_SUCCESS;
}