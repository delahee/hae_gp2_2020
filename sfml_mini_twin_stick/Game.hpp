#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

using namespace sf;

class Game {
public:

	sf::RenderWindow* win = nullptr;
	sf::RectangleShape player;

	Game(sf::RenderWindow * win) {
		this->win = win;
		player = sf::RectangleShape(Vector2f(64, 64));
		player.setFillColor(sf::Color(0xF57F5Dff));
		player.setOutlineColor(sf::Color(0x59EB7Fff));
		player.setOutlineThickness(2);
		player.setPosition(50, 50);
		player.setOrigin(25, 25);
	}

	void processInput(sf::Event ev) {
		if (ev.type == sf::Event::Closed)
			win->close();
		if (ev.type == sf::Event::KeyReleased) {

		}
	}

	void pollInput() {
		sf::Vector2f ppos = player.getPosition();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) 
			ppos.y--;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
			ppos.x--;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			ppos.y++;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			ppos.x++;
		player.setPosition(ppos);
	}
	void update() {
		pollInput();
	}

	void draw(sf::RenderWindow& win) {
		win.draw(player);
	}
};