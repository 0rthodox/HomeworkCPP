#pragma once
#include <SFML/Graphics.hpp>
#include "RandomGenerator.h"

enum GameStatus {
	STOPPED = 0,
	GOES_ON = 1
};

enum Direction {
	DOWN = 0,
	LEFT = 1,
	RIGHT = 2,
	UP = 3
};

class Player
{
private:
	int x, y;
	Direction dir;
	sf::Color color;
	int m_width;
	int m_height;
public:
	Player(sf::Color c, int W, int H) : 
		x(RandomGenerator(0, static_cast<int>(W - 1))()),
		y(RandomGenerator(0, static_cast<int>(H - 1))()),
		dir(static_cast<Direction>(RandomGenerator(0, 3)())),
		color(c),
		m_width(W),
		m_height(H)
	{}
	auto getDir() {
		return dir;
	}
	void setDir(const Direction& newDir) {
		dir = newDir;
	}
	auto getX() {
		return x;
	}
	void setX(int newX) {
		x = newX;
	}
	auto getY() {
		return y;
	}
	void setY(int newY) {
		y = newY;
	}
	auto getColor() {
		return color;
	}
	void tick()
	{
		switch (dir) {
		case Direction::DOWN:
			y += 1; break;
		case Direction::UP:
			y -= 1; break;
		case Direction::LEFT:
			x -= 1; break;
		case Direction::RIGHT:
			x += 1; break;
		default:
			throw std::exception("Illegal argument: unknown direction");
		}

		if (x >= m_width) {
			x = 0;
		}
		if (x < 0) {
			x = m_width - 1;
		}
		if (y >= m_height) {
			y = 0;
		}
		if (y < 0) {
			y = m_height - 1;
		}
	}
};