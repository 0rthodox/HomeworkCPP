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
typedef boost::interprocess::stable_vector<char_string, char_string_allocator>                   string_vector;


const std::string shared_memory_name = "managed_shared_memory";

boost::interprocess::managed_shared_memory shared_memory(
	boost::interprocess::open_or_create, shared_memory_name.c_str(), 1024);
StringAllocator allocator{ shared_memory.get_segment_manager() };

int main(int argc, char** argv)
{


	//boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());
	
	auto data = shared_memory.find_or_construct<string_vector>("Data")(allocator);

	const std::string mName = "mutex";
	const std::string cName = "cVariable";

	auto mutex =
		shared_memory.find_or_construct<Mutex>(
			mName.c_str())();
	auto condition =
		shared_memory.find_or_construct<ConditionVariable>(
			cName.c_str())();


	auto keptSize = 0u;
	//std::thread thread{ client, mutex, condition, data };

	std::string message;
	while (std::getline(std::cin, message)) {
		String bMessage(message.data(), allocator);
		{
			std::scoped_lock lock(*mutex);
			data->push_back(bMessage);
		}
		++keptSize;
		condition->notify_all();
		{
			std::unique_lock lock(*mutex);
			condition->wait(lock, [&data, &keptSize]() {
				return data->size() > keptSize; });
			//std::cout << data->back() << std::endl;
			std::cout << data->size() << ' ' << keptSize << std::boolalpha << (data->size() > keptSize) << std::endl;
		}

	}

	boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());

	system("pause");

	return EXIT_SUCCESS;
}

//#include <boost/interprocess/managed_shared_memory.hpp>
//#include <boost/interprocess/allocators/allocator.hpp>
//#include <boost/interprocess/containers/map.hpp>
//#include <boost/interprocess/containers/vector.hpp>
//#include <boost/interprocess/containers/string.hpp>
//
//using namespace boost::interprocess;
//
////Typedefs of allocators and containers
//typedef managed_shared_memory::segment_manager                       segment_manager_t;
//typedef allocator<void, segment_manager_t>                           void_allocator;
//typedef allocator<int, segment_manager_t>                            int_allocator;
//typedef vector<int, int_allocator>                                   int_vector;
//typedef allocator<int_vector, segment_manager_t>                     int_vector_allocator;
//typedef vector<int_vector, int_vector_allocator>                     int_vector_vector;
//typedef allocator<char, segment_manager_t>                           char_allocator;
//typedef basic_string<char, std::char_traits<char>, char_allocator>   char_string;
//typedef allocator<char_string, segment_manager_t>                    char_string_allocator;
//typedef vector<char_string, char_string_allocator>                   string_vector;
//
//class complex_data
//{
//	int               id_;
//	char_string       char_string_;
//	int_vector_vector int_vector_vector_;
//
//public:
//	//Since void_allocator is convertible to any other allocator<T>, we can simplify
//	//the initialization taking just one allocator for all inner containers.
//	complex_data(int id, const char* name, const void_allocator& void_alloc)
//		: id_(id), char_string_(name, void_alloc), int_vector_vector_(void_alloc)
//	{}
//	//Other members...
//};
//
////Definition of the map holding a string as key and complex_data as mapped type
//typedef std::pair<const char_string, complex_data>                      map_value_type;
//typedef std::pair<char_string, complex_data>                            movable_to_map_value_type;
//typedef allocator<map_value_type, segment_manager_t>                    map_value_type_allocator;
//typedef map< char_string, complex_data
//	, std::less<char_string>, map_value_type_allocator>          complex_map_type;
//
//int main()
//{
//	//Remove shared memory on construction and destruction
//	struct shm_remove
//	{
//		shm_remove() { shared_memory_object::remove("MySharedMemory"); }
//		~shm_remove() { shared_memory_object::remove("MySharedMemory"); }
//	} remover;
//
//	//Create shared memory
//	managed_shared_memory segment(create_only, "MySharedMemory", 65536);
//
//	//An allocator convertible to any allocator<T, segment_manager_t> type
//	void_allocator alloc_inst(segment.get_segment_manager());
//
//	//Construct the shared memory map and fill it
//	complex_map_type* mymap = segment.construct<complex_map_type>
//		//(object name), (first ctor parameter, second ctor parameter)
//		("MyMap")(std::less<char_string>(), alloc_inst);
//
//	int_vector_vector* v = segment.construct<int_vector_vector>
//		//(object name), (first ctor parameter, second ctor parameter)
//		("MyMap")(alloc_inst);
//
//	string_vector* vs = segment.construct<string_vector>
//		//(object name), (first ctor parameter, second ctor parameter)
//		("MyMap")(alloc_inst);
//
//	for (int i = 0; i < 100; ++i) {
//		//Both key(string) and value(complex_data) need an allocator in their constructors
//		char_string  key_object(alloc_inst);
//		complex_data mapped_object(i, "default_name", alloc_inst);
//		map_value_type value(key_object, mapped_object);
//		//Modify values and insert them in the map
//		mymap->insert(value);
//	}
//	return 0;
//}