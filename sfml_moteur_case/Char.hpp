#pragma once

#include "SFML/Graphics.hpp"

using namespace sf;

class Char {
public:
	static constexpr int GRID_SIZE = 16;

	sf::RectangleShape	spr;

	Char() {
		spr = RectangleShape(Vector2f(16,64));
		spr.setFillColor(sf::Color(0xFA3092ff));
		spr.setOrigin(8, 64);
	}

	int cx = 0;
	float rx = 0.0;

	int cy = 0;
	float ry = 0.0;

	void setPosition(int rpx, int rpy) {
		cx = rpx / GRID_SIZE;
		rx = rpx - (cx * GRID_SIZE);

		cy = rpy / GRID_SIZE;
		ry = rpy - (cy * GRID_SIZE);
	}

	Vector2f getPositionPixel() {
		return Vector2f(cx*GRID_SIZE + rx * GRID_SIZE, cy*GRID_SIZE + ry * GRID_SIZE);
	}

	void update(double dt) {
		spr.setPosition(getPositionPixel());
	}

	void draw(sf::RenderWindow & win) {
			win.draw(spr);
	}

};