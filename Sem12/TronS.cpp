#include <SFML/Graphics.hpp>
#include <time.h>
#include <thread>

#include <iostream>
#include <boost/asio.hpp>
#include "Player.hpp"
#include "GameLoop.hpp"

#define LOCAL

int main()
{
	RandomGenerator wGenerator(0, Gameloop::W - 1);
	RandomGenerator hGenerator(0, Gameloop::H - 1);
	auto p1 = Player(sf::Color::Red, Gameloop::W, Gameloop::H, wGenerator(), hGenerator());
	auto p2 = Player(sf::Color::Green, Gameloop::W, Gameloop::H, wGenerator(), hGenerator());

#ifdef ONLINE
#ifdef LOCAL
	std::string ip = "127.0.0.1";
#else
	std::string ip = "93.175.5.75";
#endif
	auto port = 3333;

	boost::asio::ip::tcp::endpoint endpoint(
		boost::asio::ip::address::from_string(ip), port);
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::socket socket(io_service, endpoint.protocol());
	socket.connect(endpoint);
	

	{
		std::stringstream dataStream;
		dataStream << static_cast<int>(p1.getX()) << ' ' << static_cast<int>(p1.getY()) << '\n';
		boost::asio::write(socket, boost::asio::buffer(dataStream.str()));

	}
	{
		std::stringstream dataStream;
		dataStream << static_cast<int>(p2.getX()) << ' ' << static_cast<int>(p2.getY()) << '\n';
		boost::asio::write(socket, boost::asio::buffer(dataStream.str()));

	}
		
#endif

	Gameloop(p1, p2, socket)();

    return 0;
}