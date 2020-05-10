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
	sf::RenderWindow window(sf::VideoMode(tronconsts::W, tronconsts::H), "Tron — Second Player");
	window.setFramerateLimit(60);

	sf::Texture texture;
	texture.loadFromFile("Sem12/background.jpg");
	sf::Sprite sBackground(texture);
	
	sf::Sprite sprite;
	sf::RenderTexture t;

	std::string winner;

	t.create(tronconsts::W, tronconsts::H);
	t.setSmooth(true);
	sprite.setTexture(t.getTexture());
	t.clear();
	t.draw(sBackground);

	auto status = GameStatus::GOES_ON;

#ifdef ONLINE
	auto port = 3333;
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
	std::cout << newX1 << ' ' << newY1 << std::endl;
	Player p1(sf::Color::Red, tronconsts::W, tronconsts::H, newX1, newY1);
	int newX2, newY2;
	parseData(socket, newX2, newY2);

	std::cout << newX2 << ' ' << newY2 << std::endl;
	Player p2(sf::Color::Green, tronconsts::W, tronconsts::H, newX2, newY2);

#endif

	auto iter = 0u;
	Gameloop(window, sprite, p1, p2, t, socket)();

	return 0;
}