#pragma once

#include <boost/container_hash/hash.hpp>
#include <iostream>
#include <iomanip>

struct Structure {
	int integer;
	double floatingPoint;

	Structure operator+(const Structure& structure) {
		return { integer + structure.integer, floatingPoint + structure.floatingPoint };
	}

	Structure operator+=(const Structure& structure) {
		*this = *this + structure;
		return *this;
	}
};

std::ostream& operator << (std::ostream& ostream, const Structure& structure) {
	return ostream << '[' << structure.integer << ' ' << structure.floatingPoint << ']';
}

size_t hash_value(const Structure& structure) {
	size_t hash = 0;
	boost::hash_combine(hash, structure.integer);
	boost::hash_combine(hash, structure.floatingPoint);
	return hash;
}

void testTask3() {
	constexpr auto ITERATIONS = 10000000;
	Structure step{1000, 1000. / ITERATIONS };
	//std::cout << step << ' ' << Structure{ 0, 0 } + step << std::endl;
	boost::hash<Structure> hashFunc;
	Structure structure{ 0, 0 };
	std::set<size_t> hashes;
	auto collisions = 0;
	std::ofstream data;
	data.open("Sem4/S4T3.txt");
	for (auto i = 0; i < ITERATIONS; ++i) {
		auto hash = hashFunc(structure);
		if (!hashes.insert(hash).second) {
			collisions++;
			data << i << ' ' << collisions << '\n';
		}
		structure += step;
		
	}
	std::stringstream results;
	results << "\nTotally " << collisions << " collisions\n"
		<< "of " << ITERATIONS << " hash calculations\n"
		<< '(' << std::setprecision(3) 
		<< static_cast<double>(collisions) / ITERATIONS * 100 << "%)";
	data << results.str() << std::endl;
	data.close();
	std::cout << results.str() << std::endl;
}