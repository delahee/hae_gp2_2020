#pragma once

#include <vector>;

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "Particle.hpp"
#include "ParticleMan.hpp"

using namespace sf;

class Game {
public:

	sf::RenderWindow*	win = nullptr;
	sf::RectangleShape	player;
	sf::RectangleShape	cannon;

	sf::RectangleShape  bg;
	sf::Texture			tex;

	bool				closing = false;

	ParticleMan beforeParts;
	ParticleMan afterParts;

	Game(sf::RenderWindow * win) {
		this->win = win;
		bg = sf::RectangleShape(Vector2f(win->getSize().x, win->getSize().y));
		
		bool isOk = tex.loadFromFile("res/bg.jpg");
		if (!isOk) {
			printf("ERR : LOAD FAILED\n");
		}
		bg.setTexture(&tex);
		bg.setSize(sf::Vector2f(1280, 720));
		
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
		if (ev.type == sf::Event::Closed) {
			win->close();
			closing = true;
			return;
		}
		if (ev.type == sf::Event::KeyReleased) {

		}
	}

	bool wasPressed = false;

	void spawnFumes();

	void pollInput(double dt);

	void spawnBullet(Vector2f pos, Vector2f dir);

	void update( double dt ) {
		pollInput(dt);

		beforeParts.update(dt);
		afterParts.update(dt);
	}

	void draw(sf::RenderWindow& win) {
		if (closing) return;


		win.draw(bg);

		beforeParts.draw(win);

		win.draw(player);
		win.draw(cannon);

		afterParts.draw(win);
	}
};