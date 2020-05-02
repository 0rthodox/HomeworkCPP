#include <SFML/Graphics.hpp>
#include <time.h>
#include <thread>

#include "RandomGenerator.h"
#include <iostream>
#include <boost/asio.hpp>
#include "Player.hpp"

#define ONLINE
#define LOCAL

using namespace sf;

enum FieldStatus {
	EMPTY = 0,
	FIRST = 1,
	SECOND = 2
};

//constexpr size_t W = 600;
//constexpr size_t H = 480;
int speed = 4;
FieldStatus field[W][H] = { FieldStatus::EMPTY };


template <typename Arg1, typename Arg2>
bool parseData(boost::asio::ip::tcp::socket& socket, Arg1& direction, Arg2& status)
{
	boost::asio::streambuf buffer;
	boost::asio::read_until(socket, buffer, '\n');
	std::istream stream(&buffer);
	if (!stream) {
		std::cout << "Stream is empty!" << std::endl;
		return true;
	}
	else {
		int cDirection;
		int cStatus;
		stream >> cDirection >> cStatus;
		std::cout << "Parsed data: " << cDirection << ' ' << cStatus << std::endl;
		direction = static_cast<Arg1>(cDirection);
		status = static_cast<Arg2>(cStatus);
		return false;
	}
}



void displayWinner(RenderWindow&, std::string&, const Sprite&);

int main()
{
    RenderWindow window(VideoMode(W, H), "The Tron status!");
    window.setFramerateLimit(60);

    Texture texture;
    texture.loadFromFile("Sem12/background.jpg");
    Sprite sBackground(texture);

    Player p1(Color::Red), p2(Color::Green); 

    Sprite sprite;
    RenderTexture t;

	std::string winner;

    t.create(W, H);
    t.setSmooth(true);
    sprite.setTexture(t.getTexture());
    t.clear();
	t.draw(sBackground);

    auto status = GameStatus::GOES_ON;

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
	std::cout << "Sent data: " << static_cast<int>(p1.getX()) << ' ' << static_cast<int>(p1.getY()) << '\n';
	boost::asio::write(socket, boost::asio::buffer(dataStream.str()));

	int newX, newY;
	parseData(socket, newX, newY);
	std::cout << "Parsed directions: " << "x = " << newX << "y = " << newY << std::endl;
	p2.setX(newX);
	p2.setY(newY);
#endif
	auto iter = 0u;

    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }


		if (Keyboard::isKeyPressed(Keyboard::Left) && p1.getDir() != Direction::RIGHT) {
			p1.setDir(Direction::LEFT);
		} if (Keyboard::isKeyPressed(Keyboard::Right) && p1.getDir() != Direction::LEFT) {
			p1.setDir(Direction::RIGHT);
		} if (Keyboard::isKeyPressed(Keyboard::Up) && p1.getDir() != Direction::DOWN) {
			p1.setDir(Direction::UP);
		} if (Keyboard::isKeyPressed(Keyboard::Down) && p1.getDir() != Direction::UP) {
			p1.setDir(Direction::DOWN);
		}

#ifdef ONLINE
		std::stringstream dataStream;
		dataStream << static_cast<int>(p2.getDir()) << ' ' << static_cast<bool>(status) << '\n';
		boost::asio::write(socket, boost::asio::buffer(dataStream.str()));
		std::cout << "Sent!" << std::endl;
		Direction direction;
		while (parseData(socket, direction, status));
		std::cout << "Received, direction = " << direction << std::endl;

		p2.setDir(direction);

#else

		if (Keyboard::isKeyPressed(Keyboard::A) && p2.getDir() != Direction::RIGHT) {
			p2.setDir(Direction::LEFT);
		} if (Keyboard::isKeyPressed(Keyboard::D) && p2.getDir() != Direction::LEFT) {
			p2.setDir(Direction::RIGHT);
		} if (Keyboard::isKeyPressed(Keyboard::W) && p2.getDir() != Direction::DOWN) {
			p2.setDir(Direction::UP);
		} if (Keyboard::isKeyPressed(Keyboard::S) && p2.getDir() != Direction::UP) {
			p2.setDir(Direction::DOWN);
		}
#endif

		if (status == GameStatus::STOPPED) {
			continue;
			if (1000 == iter++) {
				break;
			}
		}


        for(int i = 0; i < speed; i++)
		{
            p1.tick();
			p2.tick();
			if (field[p1.getX()][p1.getY()] != FieldStatus::EMPTY) {
				winner = "Player 2";
				status = GameStatus::STOPPED;
			}
			if (field[p2.getX()][p2.getY()] != FieldStatus::EMPTY) {
				winner = "Player 1";
				status = GameStatus::STOPPED;
			}
            field[p1.getX()][p1.getY()] = FieldStatus::FIRST; 
            field[p2.getX()][p2.getY()] = FieldStatus::SECOND;
    
            CircleShape c(3);
            c.setPosition(static_cast<float>(p1.getX()), static_cast<float>(p1.getY()));
			c.setFillColor(p1.getColor());
			t.draw(c);
			c.setPosition(static_cast<float>(p2.getX()), static_cast<float>(p2.getY()));
			c.setFillColor(p2.getColor());
			t.draw(c);
            t.display();    
        }

		window.clear();
		window.draw(sprite);
		window.display();
    }

    return 0;
}