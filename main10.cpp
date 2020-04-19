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
using StringAllocator = boost::interprocess::allocator<char, boost::interprocess::managed_shared_memory::segment_manager>;
using String = boost::interprocess::basic_string<char, std::char_traits<char>, StringAllocator>;
using Allocator = boost::interprocess::allocator<String, StringAllocator>;
using Stack = boost::interprocess::stable_vector<String, Allocator>;
using Mutex = boost::interprocess::interprocess_mutex;
using ConditionVariable = boost::interprocess::interprocess_condition;

typedef boost::interprocess::managed_shared_memory::segment_manager                       segment_manager_t;
typedef boost::interprocess::allocator<void, segment_manager_t>                           void_allocator;
typedef boost::interprocess::allocator<char, segment_manager_t>                           char_allocator;
typedef boost::interprocess::basic_string<char, std::char_traits<char>, char_allocator>   char_string;
typedef boost::interprocess::allocator<char_string, segment_manager_t>                    char_string_allocator;
typedef boost::interprocess::stable_vector<char_string, char_string_allocator>                   Data;

std::atomic_bool timeToBreak = false;

void reader(Data* data, size_t& keptSize) {
	
	while (true) {
		if (data->size() > keptSize) {
			std::cout << data->back() << std::endl;
			++keptSize;
		}
		if (timeToBreak) {
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

}



int main(int argc, char** argv)
{

	const std::string shared_memory_name = "managed_shared_memory";

	boost::interprocess::managed_shared_memory shared_memory(
		boost::interprocess::open_or_create, shared_memory_name.c_str(), 1024);
	StringAllocator allocator{ shared_memory.get_segment_manager() };
	
	auto data = shared_memory.find_or_construct<Data>("Data")(allocator);

	const std::string mName = "mutex";
	const std::string cName = "cVariable";

	auto mutex =
		shared_memory.find_or_construct<Mutex>(
			mName.c_str())();
	auto condition =
		shared_memory.find_or_construct<ConditionVariable>(
			cName.c_str())();


	auto keptSize = data->size();

	std::string message;

	std::thread thread{ reader, data, std::ref(keptSize)};
	
	auto i = 0u;
		while (std::getline(std::cin, message)) {
			if (message == "\\exit") {
				timeToBreak = true;
				thread.join();
				break;
			} else
				{
					String bMessage(message.data(), allocator);
					data->push_back(bMessage);
				}
				++keptSize;
	}

	boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());

	system("pause");

	return EXIT_SUCCESS;
}