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
	size_t W;
	size_t H;
public:
	Player(sf::Color c, size_t W, size_t H) : 
		x(RandomGenerator(0, static_cast<int>(W - 1))()),
		y(RandomGenerator(0, static_cast<int>(H - 1))()),
		color(c),
		dir(static_cast<Direction>(RandomGenerator(0, 3)()))
	{}
	auto getDir() {
		return dir;
	}
	void setDir(Direction newDir) {
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

		if (x >= W) {
			x = 0;
		}
		if (x < 0) {
			x = W - 1;
		}
		if (y >= H) {
			y = 0;
		}
		if (y < 0) {
			y = H - 1;
		}
	}
};