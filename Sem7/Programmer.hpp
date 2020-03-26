#pragma once
#include <boost/bimap.hpp>
#include <iostream>
#include "json.hpp"
#include <string>
#include <vector>
#include <unordered_map>

using nlohmann::json;

class Programmer {
	enum class Proficiency {
		BEGINNER,
		MEDIUM,
		ADVANCED,
		MASTER
	};
	Programmer() {
		initProficiencyMap();
	}
	Programmer(std::string name, int age,
		std::string language, Proficiency level) :
		name(name),
		age(age),
		language(language),
		level(level) {
		initProficiencyMap();
	}
	friend std::istream& operator>> (std::istream& input, Programmer& programmer);
	json toJson();

	boost::bimap<Proficiency, std::string> proficiencyMap;
	std::string name;
	int age;
	std::string language;
	Proficiency level;
private:
	void initProficiencyMap();
};

json Programmer::toJson() {
	json jsonedProgrammer;
	jsonedProgrammer["Name"] = name;
	jsonedProgrammer["Age"] = age;
	jsonedProgrammer["Language"] = language;
	jsonedProgrammer["Level"] = proficiencyMap.left.at(level);

	return jsonedProgrammer;
}

void Programmer::initProficiencyMap() {
	proficiencyMap.insert(boost::bimap<Proficiency, std::string>::value_type(Programmer::Proficiency::BEGINNER, "Beginner"));
	proficiencyMap.insert(boost::bimap<Proficiency, std::string>::value_type(Programmer::Proficiency::MEDIUM, "Medium"));
	proficiencyMap.insert(boost::bimap<Proficiency, std::string>::value_type(Programmer::Proficiency::ADVANCED, "Advanced"));
	proficiencyMap.insert(boost::bimap<Proficiency, std::string>::value_type(Programmer::Proficiency::MASTER, "Master"));
}

std::istream& operator>> (std::istream& input, Programmer& programmer) {
	std::string level;	
	input >> programmer.name >> programmer.age >> programmer.language >> level;
	programmer.level = programmer.proficiencyMap.right.at(level);
	return input;
}
