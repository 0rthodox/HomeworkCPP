#pragma once

#include <string>
#include <string_view>
#include <thread>
#include <vector>
#include <future>

class DNASearcher {
public:
	DNASearcher(const std::string& dna);
	inline auto operator()(const std::string&);
private:
	inline auto search(size_t begin, size_t end, const std::string_view& toSearch);
	std::string m_data;
	std::mutex outputMutex;
};

//Ctor:
DNASearcher::DNASearcher(const std::string& dna) :
	m_data(dna) {}


inline auto DNASearcher::search(size_t begin, size_t end, const std::string_view& toSearch) {
	std::string_view data{m_data};
	data = data.substr(begin, end - begin + toSearch.size());
	std::set<size_t> indexes;
	for (auto i = begin; i <= end; ++i) {
		if (m_data.substr(i, toSearch.size()) == toSearch) {
			indexes.insert(i);
		}
	}
	return indexes;
}


inline auto DNASearcher::operator()(const std::string& toSearch) {
	auto numThreads = std::thread::hardware_concurrency();
	numThreads = numThreads ? numThreads : 4;
	auto blockSize = m_data.size() / numThreads;
	std::vector<std::future<std::set<size_t>>> futures;
	for (size_t i = 1; i < numThreads; ++i) {
		futures.push_back(std::async(std::launch::async, &DNASearcher::search, this, blockSize * (i - 1), blockSize * i, toSearch));
	}
	auto indexes = search(blockSize * (numThreads - 1), m_data.size(), toSearch);
	std::for_each(futures.begin(), futures.end(), [&indexes](auto& f) {
		indexes.merge(f.get());
		});
	return indexes;
}

//Methods:
