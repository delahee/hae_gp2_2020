#pragma once

#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "Particle.hpp"
#include "ParticleMan.hpp"
#include "Char.hpp"

using namespace sf;

class Game {
public:
	sf::RenderWindow*	win = nullptr;
	sf::RectangleShape  bg;
	sf::Texture			tex;

	Char				mario;

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

		mario.setPosition((int)1280 * 0.5, 720);
	}

	void processInput(sf::Event ev);
	bool wasPressed = false;
	void pollInput(double dt);
	void onSpacePressed();

	void update(double dt);

	void draw(sf::RenderWindow& win);

	void onFileTick();
};