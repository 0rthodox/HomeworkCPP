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


void receive(boost::asio::ip::tcp::socket& socket) {
	std::string name;
	parseData(socket, name);

	std::string message;
	while (parseData(socket, message)) {
		std::cout << name << ": " << message << std::endl;
	}
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

	std::cout << "Please input your name" << std::endl;
	std::string message;
	std::getline(std::cin, message);
	std::cout << "Now start messaging!" << std::endl;

	std::thread thread{ receive, std::ref(socket) };

	do {
		message.push_back('\r');
		boost::asio::write(socket, boost::asio::buffer(message));
	} while (std::getline(std::cin, message));

	boost::asio::write(socket, boost::asio::buffer("EOF\r"));

	thread.join();

	return EXIT_SUCCESS;
}