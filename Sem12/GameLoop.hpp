#pragma once
#include <boost/asio.hpp>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "RandomGenerator.h"
#include <utility>

#define ONLINE

enum GameStatus {
	STOPPED = 0,
	GOES_ON = 1
};

enum FieldStatus {
	EMPTY = 0,
	FIRST = 1,
	SECOND = 2
};

template <typename Socket, typename Arg1, typename Arg2>
void parseData(Socket& socket, Arg1& direction, Arg2& status)
{
	boost::asio::streambuf buffer;
	boost::asio::read_until(socket, buffer, '\n');
	std::istream stream(&buffer);
	int cDirection;
	int cStatus;
	stream >> cDirection >> cStatus;
	direction = static_cast<Arg1>(cDirection);
	status = static_cast<Arg2>(cStatus);
}

class Gameloop {
public:


	Gameloop(Player& p1, Player& p2, boost::asio::ip::tcp::socket& socket) :
		m_fPlayer(p1), m_sPlayer(p2), m_socket(socket)
	{
	}


	void operator()() {
		sf::RenderWindow window(sf::VideoMode(W,H), "Tron");
		window.setFramerateLimit(60);

		sf::Texture texture;
		texture.loadFromFile("Sem12/background.jpg");
		sf::Sprite sBackground(texture);

		sf::Sprite sprite;
		sf::RenderTexture t;

		t.create(W, H);
		t.setSmooth(true);
		sprite.setTexture(t.getTexture());
		t.clear();
		t.draw(sBackground);


		auto status = GameStatus::GOES_ON;

		while (window.isOpen()) {
			sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_fPlayer.getDir() != Direction::RIGHT) {
			m_fPlayer.setDir(Direction::LEFT);
		} if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_fPlayer.getDir() != Direction::LEFT) {
			m_fPlayer.setDir(Direction::RIGHT);
		} if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_fPlayer.getDir() != Direction::DOWN) {
			m_fPlayer.setDir(Direction::UP);
		} if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_fPlayer.getDir() != Direction::UP) {
			m_fPlayer.setDir(Direction::DOWN);
		}

#ifdef ONLINE
		std::stringstream dataStream;
		dataStream << static_cast<int>(m_fPlayer.getDir()) << ' ' << static_cast<int>(status) << '\n';
		boost::asio::write(m_socket, boost::asio::buffer(dataStream.str()));
		Direction direction;
		parseData(m_socket, direction, status);

		if (status == GameStatus::STOPPED) {
			return;
		}

		m_sPlayer.setDir(direction);

#else

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && m_sPlayer.getDir() != Direction::RIGHT) {
			m_sPlayer.setDir(Direction::LEFT);
		} if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && m_sPlayer.getDir() != Direction::LEFT) {
			m_sPlayer.setDir(Direction::RIGHT);
		} if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_sPlayer.getDir() != Direction::DOWN) {
			m_sPlayer.setDir(Direction::UP);
		} if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && m_sPlayer.getDir() != Direction::UP) {
			m_sPlayer.setDir(Direction::DOWN);
		}
#endif
		for (int i = 0; i < speed; i++)
		{
			m_fPlayer.tick();
			m_sPlayer.tick();
			if (m_field[m_fPlayer.getX()][m_fPlayer.getY()] != FieldStatus::EMPTY || m_field[m_sPlayer.getX()][m_sPlayer.getY()] != FieldStatus::EMPTY) {
				status = GameStatus::STOPPED;
			}
			m_field[m_fPlayer.getX()][m_fPlayer.getY()] = FieldStatus::FIRST;
			m_field[m_sPlayer.getX()][m_sPlayer.getY()] = FieldStatus::SECOND;

			sf::CircleShape c(3);
			c.setPosition(static_cast<float>(m_fPlayer.getX()), static_cast<float>(m_fPlayer.getY()));
			c.setFillColor(m_fPlayer.getColor());
			t.draw(c);
			c.setPosition(static_cast<float>(m_sPlayer.getX()), static_cast<float>(m_sPlayer.getY()));
			c.setFillColor(m_sPlayer.getColor());
			t.draw(c);
			t.display();
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}
}
	static const int W = 600;
	static const int H = 480;

private:	
	Player m_fPlayer;
	Player m_sPlayer;
	boost::asio::ip::tcp::socket& m_socket;
	
	int speed = 4;
	FieldStatus m_field[W][H] = { FieldStatus::EMPTY };
	
};