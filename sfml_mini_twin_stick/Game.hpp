#pragma once

#include <vector>;

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "Particle.hpp"


using namespace sf;

class Game {
public:

	sf::RenderWindow*	win = nullptr;
	sf::RectangleShape	player;
	sf::RectangleShape	cannon;

	sf::RectangleShape  bg;
	sf::Texture			tex;

	bool				closing = false;

	std::vector<Particle> parts;


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
		cannon.setRotation( (angle / (2 * Lib::pi())) * 360);
		//cannon.setRotation(90);
		ppos.x += 8;
		ppos.y += 4;
		cannon.setPosition(ppos);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
			
			Vector2f dir(mPos.x - ppos.x, mPos.y - ppos.y);
			Vector2f pos(ppos.x, ppos.y);

			Vector2f ndir = dir;
			double len = sqrt(ndir.x*ndir.x + ndir.y * ndir.y);
			if (len <= 0.0)
				len = 1.0;
			ndir.x /= len;
			ndir.y /= len;

			pos.x += ndir.x * 48;
			pos.y += ndir.y * 48;

			spawnParticle(pos, ndir);
		}
	}

	void spawnParticle(Vector2f pos, Vector2f dir) {
		Particle p;
		p.x = pos.x;
		p.y = pos.y;

		p.dx = dir.x * 60 * 10;
		p.dy = dir.y * 60 * 10;
		parts.push_back(p);
	}

	void update( double dt ) {
		pollInput(dt);

		for (auto iter = parts.begin(); iter != parts.end(); ) {
			Particle & p = *iter;
			p.update(dt);
			if (p.destroyed)
				iter = parts.erase(iter);
			else
				iter++;
		}
	}

	void draw(sf::RenderWindow& win) {
		if (closing) return;
		win.draw(bg);
		win.draw(player);
		win.draw(cannon);

		for (Particle & p : parts) {
			win.draw(p.el);
		}
	}
};