#include "Game.hpp"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

void Game::processInput(sf::Event ev) {
	if (ev.type == sf::Event::Closed) {
		win->close();
		closing = true;
		return;
	}
	if (ev.type == sf::Event::KeyReleased) {
		if (ev.key.code == sf::Keyboard::Key::Z) {
		}
			
		if (ev.key.code == sf::Keyboard::Key::S) {
			
		}
		
		if (ev.key.code == sf::Keyboard::Key::Q) {
			//mario.rx -= 0.1;
		}
		
		if (ev.key.code == sf::Keyboard::Key::D) {
			//mario.rx += 0.1;
		}

		if (ev.key.code == sf::Keyboard::Key::R) {
			mario.setPosition(640, 720);
		}

		if (ev.key.code == sf::Keyboard::Key::F) {
			//parse();
		}
		// ouvrir le descripteur de fichier
		//
		// F lire le ficher
		// lire 0 pour avancer
		// lire 1 pour reculer
		// lire 2 pour tourner a g / 3 tourner a droite
		// execute la liste de commande
		// on ferme le fichier

	
	}
}

 void Game::draw(sf::RenderWindow & win) {
	if (closing) return;

	win.draw(bg);

	beforeParts.draw(win);

	//turtle.draw(win);
	mario.draw(win);

	afterParts.draw(win);
}

void Game::pollInput(double dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		mario.rx -= 0.5 * dt  * 60.0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		mario.rx += 0.5 * dt  * 60.0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		if (!wasPressed) {
			onSpacePressed();
			wasPressed = true;
		}
	}
	else {
		wasPressed = false;
	}

}

void Game::onSpacePressed() {
	
}

void Game::onFileTick() {
	
}

static float timer = 0.0;
void Game::update(double dt) {
	pollInput(dt);

	beforeParts.update(dt);
	
	mario.update(dt);

	afterParts.update(dt);

	timer -= dt;
	if (timer <= 0.0) {
		onFileTick();
		timer = 0.1;
	}
}
