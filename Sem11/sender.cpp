#include <iostream>

#include <boost/asio.hpp>

bool parseData(boost::asio::ip::tcp::socket& socket, std::string& message)
{
	boost::asio::streambuf buffer;
	boost::asio::read_until(socket, buffer, '\n');
	std::istream stream(&buffer);
	std::getline(stream, message);
	return message != "EOF";
}


void receive(boost::asio::ip::tcp::socket & socket){
	try {
		std::string name;
		parseData(socket, name);

		std::string message;
		while (parseData(socket, message)) {
			std::cout << name << ": " << message << std::endl;
		}

	}
	catch (std::system_error& err) {
		std::cerr << err.what();
	}
}

int main()
{
	try {
		std::string ip = "93.175.5.75";
		auto port = 8000u;

		boost::asio::ip::tcp::endpoint endpoint(
			boost::asio::ip::address::from_string(ip), port);
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::socket socket(io_service, endpoint.protocol());
		socket.connect(endpoint);


		std::cout << "Please input your name" << std::endl;
		std::string message;
		std::getline(std::cin, message);
		std::cout << "Now start messaging!" << std::endl;

		std::thread thread{ receive, std::ref(socket) };

		do {
			message.push_back('\n');
			boost::asio::write(socket, boost::asio::buffer(message));
		} while (std::getline(std::cin, message));

		boost::asio::write(socket, boost::asio::buffer("EOF\n"));

		thread.join();


	}
	catch (std::system_error& err) {
		std::cerr << err.what();
	}

	return EXIT_SUCCESS;
	
}