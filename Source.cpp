#define _CRT_SECURE_NO_WARNINGS

#ifndef _HAS_AUTO_PTR_ETC
#define _HAS_AUTO_PTR_ETC 1
#endif

#include <chrono>
#include <codecvt>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <locale>

#include <boost/locale.hpp>

#include <Windows.h> // Windows OS

#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING 1

std::string convert_locale_to_utf(const std::string & string)
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

std::wstring convert_utf8_to_wstring(const std::string& string)
{
	std::wstring_convert < std::codecvt_utf8 < wchar_t > > converter;
	return converter.from_bytes(string);
}

std::string convert_wstring_to_utf8(const std::wstring& wstring)
{
	std::wstring_convert < std::codecvt_utf8 < wchar_t > > converter;
	return converter.to_bytes(wstring);
}

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

//bool is_little_endian_system() 
//{
//	char16_t test = 0x0102;
//	return (reinterpret_cast < char * > (&test))[0] == 0x02;
//}

//std::u16string convert_utf8_to_utf16(const std::string & string) 
//{
//	static bool little_endian_system = is_little_endian_system();
//
//	if (little_endian_system) 
//	{
//		std::wstring_convert < std::codecvt_utf8_utf16 < 
//			char16_t, 0x10ffffU, std::codecvt_mode::little_endian > , char16_t > converter;
//		return converter.from_bytes(string);
//	}
//	else 
//	{
//		std::wstring_convert < std::codecvt_utf8_utf16 < char16_t > , char16_t > converter;
//		return converter.from_bytes(string);
//	}
//}

//std::string convert_utf16_to_utf8(const std::u16string & string) 
//{
//	std::wstring_convert < std::codecvt_utf8_utf16 < char16_t > , char16_t > converter;
//	return converter.to_bytes(string);
//}

int main(int argc, char** argv)
{
	//std::cin.imbue(std::locale::classic());
	////std::cin.imbue(std::locale("C"));
	//std::cout.imbue(std::locale(""));

	//double value = 0.0;

	//while (std::cin >> value)
	//{
	//	std::cout << value;
	//}
	//
	//std::locale locale("C"); // deu_deu.1252, rus_rus.1252

	//std::cout.imbue(locale);

	//std::cout << 100000000000 << std::endl;

	//std::cout << std::use_facet < std::numpunct < char > > (
	//	locale).thousands_sep() << std::endl;

	// ============================================================================

	//auto now = std::chrono::system_clock::now();
	//std::time_t t = std::chrono::system_clock::to_time_t(now);
	//tm * now_tm = std::localtime(&t);

	//std::locale locale_C;

	//const std::time_put < char > & time_put_C = std::use_facet < std::time_put < char > > (locale_C);

	//time_put_C.put(std::cout, std::cout, ' ', now_tm, 'x'); // strftime

	//std::cout << std::endl;

	//std::string format = "%A %x %I%p\n";
	//time_put_C.put(std::cout, std::cout, ' ', now_tm, format.c_str(), format.c_str() + format.size());

	//std::locale locale_R("");

	//const std::time_put < char > & time_put_R = std::use_facet < std::time_put < char > > (locale_R);

	//time_put_R.put(std::cout, std::cout, ' ', now_tm, 'x'); // strftime
	//std::cout << std::endl;

	//time_put_R.put(std::cout, std::cout, ' ', now_tm, format.c_str(), format.c_str() + format.size());

	////std::string ts = std::asctime(std::localtime(&t));
	////std::cout << ts << std::endl;

	// ============================================================================

	//std::locale locale_R("");

	//const std::time_get < char > & time_get_R = std::use_facet < std::time_get < char > > (locale_R);

	//using TB = std::time_base;

	//std::time_get < char >::dateorder d = time_get_R.date_order();

	//std::cout << "dateorder: "
	//	<< (d == TB::no_order || d == TB::mdy ? "mdy" :
	//		d == TB::dmy ? "dmy" :
	//		d == TB::ymd ? "ymd" :
	//		d == TB::ydm ? "ydm" : "unknown") << std::endl;

	//std::cout << "<day> <hh>:<mm>: ";
	//std::string format = "%A %H:%M";

	//tm val;

	//std::ios_base::iostate error = std::ios_base::goodbit;

	//time_get_R.get(
	//	std::istreambuf_iterator < char >(std::cin),
	//	std::istreambuf_iterator < char >(),
	//	std::cin, error, &val, format.c_str(), format.c_str() + format.size());

	//if (error != std::ios_base::goodbit)
	//{
	//	std::cerr << "invalid format" << std::endl;
	//}

	// ============================================================================

	system("chcp 1251");

	std::string s;
	std::cin >> s;

	// std::cout << std::hex << int(s[0]) << ' ' << int(s[1]) << std::endl;

	std::locale locale_R("");
	std::wcout.imbue(locale_R);
	std::wstring ws = convert_string_to_wstring(s, locale_R);
	std::wcout << ws << ' ' << ws.length() << std::endl;

	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	std::string result = convert_wstring_to_utf8(ws);
	std::cout << result << ' ' << result.length() << std::endl;

	for (auto i : result)
		std::cout << i << ' ';
	std::cout << std::endl;

	result = convert_locale_to_utf(s); // good
	std::cout << result << ' ' << result.length() << std::endl;

	s = convert_utf_to_locale(result); // good
	system("chcp 1251");
	std::cout << s << std::endl;
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	std::u16string u16s = boost::locale::conv::utf_to_utf < char16_t, char >(result);
	for (auto i : u16s)
		std::cout << i << ' ';
	std::cout << std::endl;

	std::u32string u32s = boost::locale::conv::utf_to_utf < char32_t, char >(result);
	for (auto i : u32s)
		std::cout << i << ' ';
	std::cout << std::endl;

	std::u16string u16s_cmp = u"ïðèâåò";
	for (auto i : u16s_cmp)
		std::cout << i << ' ';
	std::cout << std::endl;
	std::cout << std::boolalpha << (u16s == u16s_cmp) << std::endl;

	s = u8"ÝÒÎ ÊÎÄÈÐÎÂÊÀ UNICODE UTF-8! \xAA \xBB \xCC \xDD \xEE \xFF";

	std::cout << s << ' ' << s.length() << std::endl;

	ws = convert_utf8_to_wstring(s);

	system("chcp 1251");

	std::wcout << ws << ' ' << ws.length() << '\n'; // WTF

	std::cout << std::endl;

	result = convert_wstring_to_string(ws, locale_R);

	std::cout << result << ' ' << result.length() << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}