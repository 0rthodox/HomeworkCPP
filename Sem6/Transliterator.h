#pragma once

#include <boost\locale\generator.hpp>
#include <boost\locale\encoding.hpp>
#include <boost\locale\util.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

namespace borrowed {
	std::string convert_utf_to_locale(const std::string& string);
	std::string convert_locale_to_utf(const std::string& string);
}



class Transliterator {
public:
	Transliterator();
	std::string operator()(const std::string&);

private:
	std::u32string transliterateU32(const std::u32string&);
	std::unordered_map<char32_t, std::u32string> m_transliterates;
};

//Methods & Constructor implementation:

std::string Transliterator::operator()(const std::string& input) {
	return borrowed::convert_utf_to_locale(
		boost::locale::conv::utf_to_utf<char>(
			transliterateU32(
				boost::locale::conv::utf_to_utf<char32_t>(
					borrowed::convert_locale_to_utf(input)))));
}

std::u32string Transliterator::transliterateU32(const std::u32string& input) {
	std::u32string output;
	for (auto letter : input) {
		auto letterIterator = m_transliterates.find(letter);
		if (m_transliterates.end() != letterIterator) {
			auto replacingString = letterIterator->second;
			std::copy(replacingString.begin(), replacingString.end(), std::back_inserter(output));
		}
		else {
			output.push_back(letter);
		}
	}
	return output;
}

Transliterator::Transliterator() : m_transliterates({
	{U'é', U"j"},
	{U'ö', U"cz"},
	{U'ó', U"u"},
	{U'ê', U"k"},
	{U'å', U"e"},
	{U'í', U"n"},
	{U'ã', U"g"},
	{U'ø', U"sh"},
	{U'ù', U"shch"},
	{U'ç', U"z"},
	{U'õ', U"kh"},
	{U'ú', U"''"},
	{U'ô', U"ph"},
	{U'û', U"y'"},
	{U'â', U"v"},
	{U'à', U"a"},
	{U'ï', U"p"},
	{U'ð', U"r"},
	{U'î', U"o"},
	{U'ë', U"l"},
	{U'ä', U"d"},
	{U'æ', U"zh"},
	{U'ý', U"e'"},
	{U'ÿ', U"ya"},
	{U'÷', U"ch"},
	{U'ñ', U"s"},
	{U'ì', U"m"},
	{U'è', U"i"},
	{U'ò', U"t"},
	{U'ü', U"'"},
	{U'á', U"b"},
	{U'þ', U"yu"},
	{U'¸', U"yo"},
	{U'¨', U"Yo"},
	{U'É', U"J"},
	{U'Ö', U"Cz"},
	{U'Ó', U"Y"},
	{U'Ê', U"K"},
	{U'Å', U"E"},
	{U'Í', U"N"},
	{U'Ã', U"G"},
	{U'Ø', U"Sh"},
	{U'Ù', U"Shch"},
	{U'Ç', U"Z"},
	{U'Õ', U"Kh"},
	{U'Ú', U"''"},
	{U'Ô', U"Ph"},
	{U'Û', U"Y'"},
	{U'Â', U"V"},
	{U'À', U"A"},
	{U'Ï', U"P"},
	{U'Ð', U"R"},
	{U'Î', U"O"},
	{U'Ë', U"L"},
	{U'Ä', U"D"},
	{U'Æ', U"Zh"},
	{U'Ý', U"E'"},
	{U'ß', U"Ya"},
	{U'×', U"Ch"},
	{U'Ñ', U"S"},
	{U'Ì', U"M"},
	{U'È', U"I"},
	{U'Ò', U"T"},
	{U'Ü', U"'"},
	{U'Á', U"B"},
	{U'Þ', U"Yu"},
	}) {}

//Borrowed functions

std::string borrowed::convert_locale_to_utf(const std::string& string)
{
	boost::locale::generator generator;
	generator.locale_cache_enabled(true);

	std::locale locale =
		generator(boost::locale::util::get_system_locale());

	return boost::locale::conv::to_utf < char >(string, locale);
}

std::string borrowed::convert_utf_to_locale(const std::string& string)
{
	boost::locale::generator generator;
	generator.locale_cache_enabled(true);

	std::locale locale =
		generator(boost::locale::util::get_system_locale());

	return boost::locale::conv::from_utf < char >(string, locale);
}