#include <iostream>

#include <boost/asio.hpp>

int main()
{
	std::string ip = "127.0.0.1";
	auto port = 3333u;

	boost::asio::ip::tcp::endpoint endpoint(
		boost::asio::ip::address::from_string(ip), port);
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::socket socket(io_service, endpoint.protocol());
	socket.connect(endpoint);


	std::cout << "Please input your name" << std::endl;		
	std::string message;
	std::getline(std::cin, message);
	std::cout << "Now start messaging!" << std::endl;

	do {
		message.push_back('\r');
		boost::asio::write(socket, boost::asio::buffer(message));
	} while (std::getline(std::cin, message));

	boost::asio::write(socket, boost::asio::buffer("EOF\r"));

	return EXIT_SUCCESS;
}