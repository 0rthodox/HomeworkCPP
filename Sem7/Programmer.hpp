#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "json.hpp"
#include <boost/bimap.hpp>

using nlohmann::json;

struct Programmer {
	enum Proficiency {
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
	json toJson() {
		json jsonedProgrammer;
		jsonedProgrammer["Name"] = name;
		jsonedProgrammer["Age"] = age;
		jsonedProgrammer["Language"] = language;
		jsonedProgrammer["Level"] = proficiencyMap.left.at(level);

		return jsonedProgrammer;
	}

	boost::bimap<Proficiency, std::string> proficiencyMap;
	std::string name;
	int age;
	std::string language;
	Proficiency level;
private:
	void initProficiencyMap() {
		proficiencyMap.insert(boost::bimap<Proficiency, std::string>::value_type(BEGINNER, "Beginner"));
		proficiencyMap.insert(boost::bimap<Proficiency, std::string>::value_type(MEDIUM, "Medium"));
		proficiencyMap.insert(boost::bimap<Proficiency, std::string>::value_type(ADVANCED, "Advanced"));
		proficiencyMap.insert(boost::bimap<Proficiency, std::string>::value_type(MASTER, "Master"));
	}
};

std::istream& operator>> (std::istream& input, Programmer& programmer) {
	std::string level;	
	input >> programmer.name >> programmer.age >> programmer.language >> level;
	programmer.level = programmer.proficiencyMap.right.at(level);
	return input;
}
