#pragma once
#include <locale>
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <stdlib.h>

long double getEuroRate() {
	std::string tempFile = "Sem6/_TEMPFILE_rate.txt";
	std::string invokeCurrencyExtractor = "java -classpath Sem6 CurrencyExtractor ";
	system((invokeCurrencyExtractor + tempFile).c_str());
	std::ifstream rateStream(tempFile);
	long double rate;
	rateStream >> rate;
	std::remove(tempFile.c_str());
	std::cout << "Current exchange rate pulled successfully: " << rate << std::endl;
	return rate;
}

void convert() {
	std::cout.imbue(std::locale::locale("ru_RU.UTF8"));
	std::cin.imbue(std::locale::locale("de_DE.UTF8"));
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	long double value;
	auto euroRate = getEuroRate();
	while (std::cin >> std::get_money(value)) {
		value *= euroRate;
		std::cout << std::showbase << std::put_money(value, false) << std::endl;
	}
	
}

