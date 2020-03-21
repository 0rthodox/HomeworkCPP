#pragma once
#include <string>
#include <bitset>
#include <sstream>
#include <fstream>
#include <set>
#include <iostream>
#include <iomanip>
#include "RandomGenerator.h"

unsigned int RSHash(const char* str, unsigned int length)
{
	unsigned int b = 378551;
	unsigned int a = 63689;
	unsigned int hash = 0;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash = hash * a + (*str);
		a = a * b;
	}

	return hash;
}

unsigned int JSHash(const char* str, unsigned int length)
{
	unsigned int hash = 1315423911;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash ^= ((hash << 5) + (*str) + (hash >> 2));
	}

	return hash;
}

unsigned int PJWHash(const char* str, unsigned int length)
{
	const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
	const unsigned int ThreeQuarters = (unsigned int)((BitsInUnsignedInt * 3) / 4);
	const unsigned int OneEighth = (unsigned int)(BitsInUnsignedInt / 8);
	const unsigned int HighBits =
		(unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
	unsigned int hash = 0;
	unsigned int test = 0;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash = (hash << OneEighth) + (*str);

		if ((test = hash & HighBits) != 0)
		{
			hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
		}
	}

	return hash;
}

unsigned int ELFHash(const char* str, unsigned int length)
{
	unsigned int hash = 0;
	unsigned int x = 0;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash = (hash << 4) + (*str);

		if ((x = hash & 0xF0000000L) != 0)
		{
			hash ^= (x >> 24);
		}

		hash &= ~x;
	}

	return hash;
}

unsigned int BKDRHash(const char* str, unsigned int length)
{
	unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
	unsigned int hash = 0;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash = (hash * seed) + (*str);
	}

	return hash;
}

unsigned int SDBMHash(const char* str, unsigned int length)
{
	unsigned int hash = 0;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash = (*str) + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}

unsigned int DJBHash(const char* str, unsigned int length)
{
	unsigned int hash = 5381;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash = ((hash << 5) + hash) + (*str);
	}

	return hash;
}

unsigned int DEKHash(const char* str, unsigned int length)
{
	unsigned int hash = length;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
	}

	return hash;
}

unsigned int APHash(const char* str, unsigned int length)
{
	unsigned int hash = 0xAAAAAAAA;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash ^= ((i & 1) == 0) ? ((hash << 7) ^ (*str) * (hash >> 3)) :
			(~((hash << 11) + ((*str) ^ (hash >> 5))));
	}

	return hash;
}

void testNumericStringHash(unsigned hasher (const char*, unsigned), size_t iterations, const std::string & path) {
	std::set<size_t> hashes;
	auto collisions = 0;
	std::ofstream data;
	data.open(path);
	for (auto i = 0; i < iterations; ++i) {
		auto string = std::to_string(i);
		auto hash = hasher(string.c_str(), string.size());
		//printf("%s %d %d\n", string.c_str(), string.size(), hash);
		if (!hashes.insert(hash).second) {
			collisions++;
			//data << i << ' ' << collisions << '\n';
		}
	}
	std::stringstream results;
	results << "\nTotally " << collisions << " collisions\n"
		<< "of " << iterations << " hash calculations\n"
		<< '(' << std::setprecision(3)
		<< static_cast<double>(collisions) / iterations * 100 << "%)";
	data << results.str() << std::endl;
	data.close();
	std::cout << results.str() << std::endl;
}

template <typename ForwardIt>
void testStringHash(unsigned hasher(const char*, unsigned), ForwardIt first, ForwardIt last, const std::string& path) {
	std::set<size_t> hashes;
	auto collisions = 0;
	std::ofstream data;
	data.open(path);
	auto i = 0u;
	for (auto it = first; it != last; ++it) {
		auto string = *it;
		auto hash = hasher(string.c_str(), string.size());
		printf("%s %d %d\n", string.c_str(), string.size(), hash);
		++i;
		if (!hashes.insert(hash).second) {
			collisions++;
			data << i << ' ' << collisions << '\n';
		}
	}
	std::stringstream results;
	results << "\nTotally " << collisions << " collisions\n"
		<< "of " << i << " hash calculations\n"
		<< '(' << std::setprecision(3)
		<< static_cast<double>(collisions) / i * 100 << "%)";
	data << results.str() << std::endl;
	data.close();
	std::cout << results.str() << std::endl;
}

auto permutatedStrings(std::string string) {
	std::sort(string.begin(), string.end());
	std::vector<std::string> strings;
	do {
		strings.push_back(string);
	} while (std::next_permutation(string.begin(), string.end()));
	return strings;
}

void testTask4() {
	//auto strings = permutatedStrings("stringHASH");
	///*testStringHash(RSHash, strings.begin(), strings.end(), "Sem4/S4T4_RS.txt");
	//testStringHash(JSHash, strings.begin(), strings.end(), "Sem4/S4T4_JS.txt");*/
	//testStringHash(PJWHash, strings.begin(), strings.end(), "Sem4/S4T4_PJW.txt");
	//testStringHash(ELFHash, strings.begin(), strings.end(), "Sem4/S4T4_ELF.txt");
	//testStringHash(BKDRHash, strings.begin(), strings.end(), "Sem4/S4T4_BKDR.txt");
	//testStringHash(SDBMHash, strings.begin(), strings.end(), "Sem4/S4T4_SDBM.txt");
	//testStringHash(DJBHash, strings.begin(), strings.end(), "Sem4/S4T4_DJB.txt");
	//testStringHash(DEKHash, strings.begin(), strings.end(), "Sem4/S4T4_DEK.txt");
	//testStringHash(APHash, strings.begin(), strings.end(), "Sem4/S4T4_AP.txt");
	constexpr auto ITERATIONS = 10100100;
	/*testNumericStringHash(RSHash, ITERATIONS, "Sem4/S4T4_RS.txt");
	testNumericStringHash(JSHash, ITERATIONS, "Sem4/S4T4_JS.txt");*/
	testNumericStringHash(PJWHash, ITERATIONS, "Sem4/S4T4_PJW.txt");
	/*testNumericStringHash(ELFHash, ITERATIONS, "Sem4/S4T4_ELF.txt");
	testNumericStringHash(BKDRHash, ITERATIONS, "Sem4/S4T4_BKDR.txt");
	testNumericStringHash(SDBMHash, ITERATIONS, "Sem4/S4T4_SDBM.txt");
	testNumericStringHash(DJBHash, ITERATIONS, "Sem4/S4T4_DJB.txt");
	testNumericStringHash(DEKHash, ITERATIONS, "Sem4/S4T4_DEK.txt");
	testNumericStringHash(APHash, ITERATIONS, "Sem4/S4T4_AP.txt");*/

}