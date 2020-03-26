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
	{U'�', U"j"},
	{U'�', U"cz"},
	{U'�', U"u"},
	{U'�', U"k"},
	{U'�', U"e"},
	{U'�', U"n"},
	{U'�', U"g"},
	{U'�', U"sh"},
	{U'�', U"shch"},
	{U'�', U"z"},
	{U'�', U"kh"},
	{U'�', U"''"},
	{U'�', U"ph"},
	{U'�', U"y'"},
	{U'�', U"v"},
	{U'�', U"a"},
	{U'�', U"p"},
	{U'�', U"r"},
	{U'�', U"o"},
	{U'�', U"l"},
	{U'�', U"d"},
	{U'�', U"zh"},
	{U'�', U"e'"},
	{U'�', U"ya"},
	{U'�', U"ch"},
	{U'�', U"s"},
	{U'�', U"m"},
	{U'�', U"i"},
	{U'�', U"t"},
	{U'�', U"'"},
	{U'�', U"b"},
	{U'�', U"yu"},
	{U'�', U"yo"},
	{U'�', U"Yo"},
	{U'�', U"J"},
	{U'�', U"Cz"},
	{U'�', U"Y"},
	{U'�', U"K"},
	{U'�', U"E"},
	{U'�', U"N"},
	{U'�', U"G"},
	{U'�', U"Sh"},
	{U'�', U"Shch"},
	{U'�', U"Z"},
	{U'�', U"Kh"},
	{U'�', U"''"},
	{U'�', U"Ph"},
	{U'�', U"Y'"},
	{U'�', U"V"},
	{U'�', U"A"},
	{U'�', U"P"},
	{U'�', U"R"},
	{U'�', U"O"},
	{U'�', U"L"},
	{U'�', U"D"},
	{U'�', U"Zh"},
	{U'�', U"E'"},
	{U'�', U"Ya"},
	{U'�', U"Ch"},
	{U'�', U"S"},
	{U'�', U"M"},
	{U'�', U"I"},
	{U'�', U"T"},
	{U'�', U"'"},
	{U'�', U"B"},
	{U'�', U"Yu"},
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