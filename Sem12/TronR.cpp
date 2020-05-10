#include <SFML/Graphics.hpp>
#include <time.h>
#include <thread>
#include <iostream>

#include <boost/asio.hpp>
#include "RandomGenerator.h"
#include "Player.hpp"
#include "Gameloop.hpp"

#define ONLINE

int main()
{
	sf::RenderWindow window(sf::VideoMode(tron::W, tron::H), "Tron — Second Player");
	window.setFramerateLimit(60);

	sf::Texture texture;
	texture.loadFromFile("Sem12/background.jpg");
	sf::Sprite sBackground(texture);

	Player p1(sf::Color::Red, tron::W, tron::H), p2(sf::Color::Green, tron::W, tron::H);

	sf::Sprite sprite;
	sf::RenderTexture t;

	std::string winner;

	t.create(tron::W, tron::H);
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

	std::stringstream dataStream;
	dataStream << static_cast<int>(p2.getX()) << ' ' << static_cast<int>(p2.getY()) << '\n';
	boost::asio::write(socket, boost::asio::buffer(dataStream.str()));
	int newX, newY;
	parseData(socket, newX, newY);
	p1.setX(newX);
	p1.setY(newY);

#endif

	auto iter = 0u;
	Gameloop x{ window, sprite, p1, p2, t };

	return 0;
}