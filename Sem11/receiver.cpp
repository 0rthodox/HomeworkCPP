#include <iostream>

#include <boost/asio.hpp>

bool parseData(boost::asio::ip::tcp::socket& socket, std::string& message)
{
	boost::asio::streambuf buffer;
	boost::asio::read_until(socket, buffer, '\r');
	std::istream stream(&buffer);
	stream >> message;
	return message != "EOF";
}

int main()
{
	auto port = 3333u;
	std::string ip = "127.0.0.1";
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(ip), port);
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint.protocol());
	acceptor.bind(endpoint);
	acceptor.listen();
	boost::asio::ip::tcp::socket socket(io_service);
	acceptor.accept(socket);

	std::string name;
	if (!parseData(socket, name)) {
		return EXIT_FAILURE;
	}

	std::string message;
	while (parseData(socket, message)) {
		std::cout << name << ": " << message << std::endl;
	}
	return EXIT_SUCCESS;
}