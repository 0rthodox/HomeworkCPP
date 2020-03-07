#pragma once

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/member.hpp>
#include <sstream>
#include "RandomGenerator.h"

//class PhoneNumber {
//	int countryCode;
//	int cityCode;
//	int ownerDigits;
//public:
//	PhoneNumber(const std::string& number) {
//		std::stringstream stringStream;
//		stringStream << number;
//		assert(stringStream.peek() == '+');
//		stringStream.ignore();
//		stringStream >> countryCode;
//		assert(stringStream.peek() == '-');
//		stringStream.ignore();
//		stringStream >> cityCode;
//		assert(stringStream.peek() == '-');
//		stringStream.ignore();
//		stringStream >> ownerDigits;
//	}
//	std::string get() {
//		std::stringstream stringStream;
//		stringStream << '+' << countryCode << '-' << cityCode <<
//			'-' << ownerDigits;
//		return stringStream.str();
//	}
//	~PhoneNumber() = default;
//};


struct Record {
	std::string phoneNumber;
	std::string owner;
public:
	struct Hashed {};
	struct Sorted {};
	struct RA {};
	Record(const std::string& number, const std::string& owner) :
		phoneNumber(number), owner(owner) {}
	~Record() = default;
	auto get() {
		return std::make_pair(owner, phoneNumber);
	}
};

class Catalogue {	
	boost::multi_index::multi_index_container
		<Record, boost::multi_index::indexed_by<
		boost::multi_index::ordered_non_unique<boost::multi_index::tag<Record::Sorted>,
						boost::multi_index::member<Record, std::string, &Record::owner>>,
		boost::multi_index::hashed_unique<boost::multi_index::tag<Record::Hashed>,
						boost::multi_index::member<Record, std::string, &Record::phoneNumber>>,
		boost::multi_index::random_access<boost::multi_index::tag<Record::RA>>
		>> data;
public:
	auto randomPhoneNumber() const {
		RandomGenerator<size_t> randomGenerator(0, data.size());
		return &data.get<Record::RA>()[0 + randomGenerator.rand()];
	}
	auto getOrderedData() const {
		return std::make_pair(data.get<Record::Sorted>().begin(), data.get<Record::Sorted>().end());
	}
	auto find(const std::string& number) const  {
		return data.get<Record::Hashed>().find(number);
	}
	void insert(Record record) {
		data.insert(record);
	}
};
