#pragma once
#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <boost\locale\util.hpp>
#include <boost\locale\encoding.hpp>
#include <boost\locale\generator.hpp>

#define RANGE(s) begin(s), end(s)

std::wstring convert_string_to_wstring(
	const std::string& string,
	const std::locale& locale = std::locale())
{
	std::vector < wchar_t > buffer(string.size());

	std::use_facet < std::ctype < wchar_t > >(locale).widen(
		string.data(),
		string.data() + string.size(),
		buffer.data());

	return std::wstring(buffer.data(), buffer.size());
}

std::string convert_wstring_to_string(
	const std::wstring& wstring,
	const std::locale& locale = std::locale())
{
	std::vector < char > buffer(wstring.size());

	std::use_facet < std::ctype < wchar_t > >(locale).narrow(
		wstring.data(),
		wstring.data() + wstring.size(),
		'?', buffer.data()); // default character

	return std::string(buffer.data(), buffer.size());
}


std::string convert_locale_to_utf(const std::string& string)
{
	boost::locale::generator generator;
	generator.locale_cache_enabled(true);

	std::locale locale =
		generator(boost::locale::util::get_system_locale());

	return boost::locale::conv::to_utf < char >(string, locale);
}

std::string convert_utf_to_locale(const std::string& string)
{
	boost::locale::generator generator;
	generator.locale_cache_enabled(true);

	std::locale locale =
		generator(boost::locale::util::get_system_locale());

	return boost::locale::conv::from_utf < char >(string, locale);
}

class Transliterator {

public:
	Transliterator() {
		initSymbols();
	}

	std::string transliterate(const std::string& strToTransliterate) {
		return wtransliterate(convert_string_to_wstring(convert_locale_to_utf(strToTransliterate)), strToTransliterate.size());
	}

	std::string wtransliterate(const std::wstring& strToTransliterate, size_t size) {
		int32_t* ptr = reinterpret_cast<int32_t*>(&const_cast<std::wstring&>(strToTransliterate));
		std::string transliterated;
		for (size_t i = 0; i < size; ++i) {
			std::copy(RANGE(symbols[ptr[i]]), std::back_inserter(transliterated));
		}
		return transliterated;
	}

private:

	void initSymbols() {
		std::ifstream inputStream("Sem6/translitGOST779-2000.txt");
		std::string latinLetters;
		std::string cyrillicLetters = u8"àáâãäå¸æçèéêëìíîïðñòóôõö÷øùúûüýþÿ";
		std::wstring wcyrillicLetters =
			convert_string_to_wstring(cyrillicLetters, std::locale("ru_RU.utf8"));
		int32_t* cyrillicPointer = reinterpret_cast<int32_t*>(wcyrillicLetters.data());
		for (size_t i = 0; i < 33; ++i) {
			inputStream >> latinLetters;
			symbols[cyrillicPointer[i]] = latinLetters;
		}
	}

	std::unordered_map<wchar_t, std::string> symbols;
};