#pragma once
#include "Transliterator.h"
#include <Windows.h>
#include <locale>

#define PRINTOBJ(x) std::cout << #x << " = " << x << std::endl
#define WPRINTOBJ(x) std::wcout << #x << " = " << x << std::endl

void testTask2() {
	Transliterator t;
	std::string s = "����";
	std::wstring s = L"����";


	std::cout << newS.size() << " | " << newS << std::endl;
}