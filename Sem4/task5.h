#pragma once

#include "Catalogue.h"
#include <iostream>
#include <fstream>

class SpamCompany {
public:
	void spam(std::ofstream& data, const Catalogue& catalogue) {
		data << "Spamming to: " << catalogue.randomPhoneNumber()->owner << std::endl;
	}
};

class Typography {
public:
	std::vector<Record> publish(const Catalogue& catalogue) {
		return { catalogue.getOrderedData().first, catalogue.getOrderedData().second };
	}
};

class Detective {
public:
	std::string find(const Catalogue& catalogue, const std::string& phoneNumber) {
		return catalogue.find(phoneNumber)->owner;
	}
};

void testTask5() {
	std::ofstream data;
	data.open("Sem4/S4T5.txt");
	Catalogue catalogue;
	catalogue.insert({ "0", "teacher Makarov" });
	catalogue.insert({ "1", "student Popov" });
	catalogue.insert({ "2", "rector Kudryavtsev" });
	SpamCompany().spam(data, catalogue);
	data << "\nPrinted data:\n";
	for (auto record : Typography().publish(catalogue)) {
		data << record.owner << ": " << record.phoneNumber << '\n';
	}
	data << "\nThis phone belongs to MIPT rectorate. Its owner is " <<
		Detective().find(catalogue, "2") << ".\n" << "Yours Sincerely,\nDetective." << std::endl;


}