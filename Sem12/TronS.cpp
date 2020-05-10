#include <SFML/Graphics.hpp>
#include <time.h>
#include <thread>

#include "RandomGenerator.h"
#include <iostream>
#include <boost/asio.hpp>
#include "Player.hpp"
#include "GameLoop.hpp"

#define ONLINE
#define LOCAL

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(tron::W, tron::H), "Tron — First Player");
    window.setFramerateLimit(60);

    Texture texture;
    texture.loadFromFile("Sem12/background.jpg");
    Sprite sBackground(texture);

    Player p1(Color::Red, tron::W, tron::H), p2(Color::Green, tron::W, tron::H);

    Sprite sprite;
    RenderTexture t;
	
    t.create(tron::W, tron::H);
    t.setSmooth(true);
    sprite.setTexture(t.getTexture());
    t.clear();
	t.draw(sBackground);

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

	std::stringstream dataStream;
	dataStream << static_cast<int>(p1.getX()) << ' ' << static_cast<int>(p1.getY()) << '\n';
	boost::asio::write(socket, boost::asio::buffer(dataStream.str()));

	int newX, newY;
	parseData(socket, newX, newY);
	p2.setX(newX);
	p2.setY(newY);
#endif

	Gameloop x{ window, sprite, p1, p2, t };

    return 0;
}