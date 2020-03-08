#pragma once
#include <string>
#include <bitset>
#include <sstream>
#include <fstream>
#include <set>
#include <iostream>
#include <iomanip>

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

void testStringHash(unsigned hasher (const char*, unsigned), size_t iterations, std::string path) {
	std::set<size_t> hashes;
	auto collisions = 0;
	std::ofstream data;
	data.open(path);
	for (auto i = 0; i < iterations; ++i) {
		auto string = std::to_string(i);
		auto hash = hasher(string.c_str(), string.size());
		if (!hashes.insert(hash).second) {
			collisions++;
			data << i << ' ' << collisions << '\n';
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

void testTask4() {
	constexpr auto ITERATIONS = 10000000;
	testStringHash(RSHash, ITERATIONS, "Sem4/S4T4_RS.txt");
	testStringHash(JSHash, ITERATIONS, "Sem4/S4T4_JS.txt");
	testStringHash(PJWHash, ITERATIONS, "Sem4/S4T4_PJW.txt");
	testStringHash(ELFHash, ITERATIONS, "Sem4/S4T4_ELF.txt");
	testStringHash(BKDRHash, ITERATIONS, "Sem4/S4T4_BKDR.txt");
	testStringHash(SDBMHash, ITERATIONS, "Sem4/S4T4_SDBM.txt");
	testStringHash(DJBHash, ITERATIONS, "Sem4/S4T4_DJB.txt");
	testStringHash(DEKHash, ITERATIONS, "Sem4/S4T4_DEK.txt");
	testStringHash(APHash, ITERATIONS, "Sem4/S4T4_AP.txt");
}