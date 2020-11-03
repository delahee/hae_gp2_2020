#include "Game.hpp"


void Game::processInput(sf::Event ev) {
	if (ev.type == sf::Event::Closed) {
		win->close();
		closing = true;
		return;
	}
	if (ev.type == sf::Event::KeyReleased) {
		if (ev.key.code == sf::Keyboard::Key::Z)
			//turtle.advance(30);
			turtle.advance2(30);
			
		if (ev.key.code == sf::Keyboard::Key::S)
			turtle.backward(30);
		
		if (ev.key.code == sf::Keyboard::Key::Q)
			turtle.turnLeft(45);
		
		if (ev.key.code == sf::Keyboard::Key::D)
			turtle.turnRight(45);
	}
}

void Game::pollInput(double dt) {
	sf::Vector2f ppos = turtle.getPosition();

	/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
		turtle.advance(30);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		turtle.backward(30);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		turtle.turnLeft(45);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		turtle.turnRight(45);
	}
	*/

	turtle.setPosition(ppos);

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
