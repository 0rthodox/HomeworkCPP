#define BOOST_DATE_TIME_NO_LIB

#include <iostream>
#include <mutex>
#include <string>
#include <thread>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/stable_vector.hpp>
#include <shared_mutex>

using Manager = boost::interprocess::managed_shared_memory::segment_manager;
using Mutex = boost::interprocess::interprocess_mutex;
using ConditionVariable = boost::interprocess::interprocess_condition;

using MessageAllocator = boost::interprocess::allocator<char, Manager>;
using Message = boost::interprocess::basic_string<char, std::char_traits<char>, MessageAllocator>;

using DataAllocator = boost::interprocess::allocator<Message, Manager>;
using Data = boost::interprocess::stable_vector<Message, DataAllocator>;

std::atomic_bool timeToBreak = false;

void reader(Data* data, std::atomic<size_t>& keptSize, Mutex* mutex, ConditionVariable* condition) {
	while (true) {
		std::unique_lock lock(*mutex);
		condition->wait(lock, [&data, &keptSize] { return data->size() > keptSize || timeToBreak; });
		if (timeToBreak) {
			break;
		}
		if (data->size() > keptSize) {
			std::cout << data->at(keptSize) << std::endl;
			++keptSize;
		}
	}

}



int main(int argc, char** argv)
{

	const std::string shared_memory_name = "managed_shared_memory";

	boost::interprocess::managed_shared_memory shared_memory(
		boost::interprocess::open_or_create, shared_memory_name.c_str(), 10240);
	MessageAllocator allocator{ shared_memory.get_segment_manager() };
	
	auto data = shared_memory.find_or_construct<Data>("Data")(allocator);

	const std::string mName = "mutex";
	const std::string cName = "cVariable";
	const std::string uName = "users";

	auto mutex =
		shared_memory.find_or_construct<Mutex>(
			mName.c_str())();
	auto condition =
		shared_memory.find_or_construct<ConditionVariable>(
			cName.c_str())();

	auto userCount = shared_memory.find_or_construct<std::atomic<size_t>>(
		uName.c_str())();

	(*userCount)++;

	

	std::atomic<size_t> keptSize = 0;

	std::string message;

	std::thread thread{ reader, data, std::ref(keptSize), mutex, condition};
	
	auto i = 0u;
	while (std::getline(std::cin, message)) {
		Message bMessage(message.data(), allocator);
		{
			std::lock_guard guard(*mutex);
			data->push_back(bMessage);
		}
		++keptSize;
		condition->notify_all();
	}
	timeToBreak = true;
	condition->notify_all();
	thread.join();

	if (!--*userCount) {
		boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());
	}


	system("pause");

	return EXIT_SUCCESS;
}