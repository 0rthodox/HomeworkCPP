#pragma once
#include <SFML/Graphics.hpp>
#include "RandomGenerator.h"
#include <exception>



enum Direction {
	DOWN = 0,
	LEFT = 1,
	RIGHT = 2,
	UP = 3
};

class Player
{
public:
	Player(sf::Color c, int W, int H, int x, int y) :
		m_x(x),
		m_y(y),
		m_dir(static_cast<Direction>(RandomGenerator(0, 3)())),
		m_color(c),
		m_width(W),
		m_height(H)
	{}
	const auto getDir() const {
		return m_dir;
	}
	void setDir(const Direction& newDir)  {
		m_dir = newDir;
	}
	const auto getX() const {
		return m_x;
	}
	const auto getY() const {
		return m_y;
	}
	const auto getColor() const {
		return m_color;
	}
	void tick()
	{
		switch (m_dir) {
		case Direction::DOWN:
			++m_y; break;
		case Direction::UP:
			--m_y; break;
		case Direction::LEFT:
			--m_x; break;
		case Direction::RIGHT:
			++m_x; break;
		default:
			throw std::exception("Illegal argument: unknown direction");
		}

		if (m_x >= m_width) {
			m_x = 0;
		}
		if (m_x < 0) {
			m_x = m_width - 1;
		}
		if (m_y >= m_height) {
			m_y = 0;
		}
		if (m_y < 0) {
			m_y = m_height - 1;
		}
	}

private:
	int m_x, m_y;
	Direction m_dir;
	sf::Color m_color;
	int m_width;
	int m_height;
};