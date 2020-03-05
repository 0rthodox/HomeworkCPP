#include "task1.h"
#include <unordered_set>
#include <map>
int main() {
	std::ofstream data;
	data.open("S4T1.txt");
	//s4::ctIterator<1000, 100000, 10, std::string, std::ofstream&>::ctIterate(s4::testSetVectorArray, data);
	{
		data << "Testing big values (mSec)" << std::endl;
		std::vector<std::string> winners;
		winners.push_back(s4::testSetVectorArray<std::chrono::milliseconds,20000>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::milliseconds,30000>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::milliseconds,40000>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::milliseconds,50000>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::milliseconds,60000>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::milliseconds,70000>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::milliseconds,80000>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::milliseconds,90000>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::milliseconds,100000>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::milliseconds,110000>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::milliseconds,120000>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::milliseconds,130000>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::milliseconds,140000>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::milliseconds,150000>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::milliseconds,160000>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::milliseconds,170000>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::milliseconds,180000>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::milliseconds,190000>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::milliseconds,200000>(data));
		std::map<std::string, int> results;
		for (const auto& collection : winners) {
			results[collection]++;
		}
		for (const auto& [collection, wins] : results) {
			data << "\nWinners:\n";
			data << collection << ": " << wins << " times of " << winners.size() << "\n" << std::endl;
		}	
    }
	{
		data << "Testing small values (muSec)" << std::endl;
		std::vector<std::string> winners;
		winners.push_back(s4::testSetVectorArray<std::chrono::microseconds, 50>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::microseconds, 100>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::microseconds, 200>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::microseconds, 300>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::microseconds, 400>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::microseconds, 500>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::microseconds, 1000>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::microseconds, 2000>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::microseconds, 3000>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::microseconds, 5000>(data));
		winners.push_back(s4::testSetVectorArray<std::chrono::microseconds, 10000>(data));
		std::map<std::string, int> results;
		for (const auto& collection : winners) {
			results[collection]++;
		}
		for (const auto& [collection, wins] : results) {
			data << "\nWinners:\n";
			data << collection << ": " << wins << " times of " << winners.size() << "\n" << std::endl;
		}
		
	}
	data.close();
}