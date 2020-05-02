#pragma once
#include <SFML/Graphics.hpp>
#include "RandomGenerator.h"

constexpr size_t W = 640;
constexpr size_t H = 480;


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
public:
	Player(sf::Color c)
	{
		x = RandomGenerator(0llu, W - 1)();
		y = RandomGenerator(0llu, H - 1)();
		color = c;
		dir = static_cast<Direction>(RandomGenerator(0, 3)());
	}
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
	void tick() noexcept
	{
		if (dir == 0) {
			y += 1;
		} else if (dir == 1) {
			x -= 1;
		} else if (dir == 2) {
			x += 1;
		} else if (dir == 3) {
			y -= 1;
		}
		else {
			std::cout << "Unknown direction" << std::endl;
		}

		if (x >= W) {
			x = 0;
		}  if (x < 0) {
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