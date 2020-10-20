#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

using namespace sf;

class Game {
public:

	sf::RenderWindow* win = nullptr;
	sf::RectangleShape player;
	sf::RectangleShape cannon;

	Game(sf::RenderWindow * win) {
		this->win = win;

		player = sf::RectangleShape(Vector2f(64, 64));
		player.setFillColor(sf::Color(0xF57F5Dff));
		player.setOutlineColor(sf::Color(0x59EB7Fff));
		player.setOutlineThickness(2);
		player.setPosition(400, 400);
		player.setOrigin(25, 25);

		cannon = sf::RectangleShape(Vector2f(64, 8));
		cannon.setFillColor(sf::Color(0xffffffff));
		cannon.setOutlineColor(sf::Color(0x000000ff));
		cannon.setOutlineThickness(2);
		cannon.setOrigin(4, 4);
	}

	void processInput(sf::Event ev) {
		if (ev.type == sf::Event::Closed)
			win->close();
		if (ev.type == sf::Event::KeyReleased) {

		}
	}

	void pollInput(double dt) {
		sf::Vector2f ppos = player.getPosition();
		float speed = 600;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) 
			ppos.y-= dt * speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
			ppos.x -= dt * speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			ppos.y += dt * speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			ppos.x += dt * speed;
		player.setPosition(ppos);

		Vector2i mPos = sf::Mouse::getPosition(*win);
		float angle = atan2f(mPos.y - ppos.y, mPos.x - ppos.x);
		printf("mPos %d %d\n", mPos.x, mPos.y);
		printf("angle %f\n",angle);
		cannon.setRotation( (angle / (2 * 3.14156)) * 360);
		//cannon.setRotation(90);
		ppos.x += 8;
		ppos.y += 4;
		cannon.setPosition(ppos);
	}

	void update( double dt ) {
		pollInput(dt);
	}

	void draw(sf::RenderWindow& win) {
		win.draw(player);
		win.draw(cannon);
	}
};