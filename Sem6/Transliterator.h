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
	Transliterator();
	std::string operator()(const std::string& inputString) {
		std::string u8InputString = convert_locale_to_utf(inputString);
		std::u32string u32InputString = boost::locale::conv::utf_to_utf<char32_t>(u8InputString);

	}

private:
	std::unordered_map<char32_t, std::u32string> m_transliterates;
};

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
	{U'�', U"C"},
	{U'�', U"M"},
	{U'�', U"I"},
	{U'�', U"T"},
	{U'�', U"'"},
	{U'�', U"B"},
	{U'�', U"Yu"},
	}) {}