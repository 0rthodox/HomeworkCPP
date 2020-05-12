#include <SFML/Graphics.hpp>
#include <time.h>
#include <thread>
#include <iostream>

#include <boost/asio.hpp>
#include "RandomGenerator.h"
#include "Player.hpp"
#include "Gameloop.hpp"


int main()
{
	

#ifdef ONLINE
	auto port = 8000;
#ifdef SPECIFIC_CLIENT
	std::string ip = "93.175.5.75";
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(ip), port);
#else
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::any(), port);
#endif
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint.protocol());
	acceptor.bind(endpoint);
	acceptor.listen();
	boost::asio::ip::tcp::socket socket(io_service);
	acceptor.accept(socket);

	int newX1, newY1;
	parseData(socket, newX1, newY1);
	int newX2, newY2;
	parseData(socket, newX2, newY2);
	Direction d1, d2;
	parseData(socket, d1, d2);
	Player p1(sf::Color::Red, Gameloop::W, Gameloop::H, newX1, newY1, d1);
	Player p2(sf::Color::Green, Gameloop::W, Gameloop::H, newX2, newY2, d2);

#endif

	Gameloop(p2, p1, socket)();

	return 0;
}