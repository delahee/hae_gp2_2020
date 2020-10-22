#include "Game.hpp"

void Game::spawnFumes() {

	auto pos = player.getPosition();

	Particle p;
	p.x = pos.x - 20 + Dice::randF() * 40;
	p.y = pos.y - 20 + Dice::randF() * 40;
	p.el.setFillColor(Color(255*0.2, 255*0.2, 255*0.2, 255*0.7));
	p.life = 5 + Dice::randF() * 2;
	p.el.setRotation(360 * Dice::randF());

	p.scaleX = p.scaleY = 1.0 + Dice::randF() * 3.0;

	p.bhv = [](Particle* p,float dt ) {//= //& 
		if (p->life >= 4.8) {
			p->scaleX *= 1.01;
			p->scaleY *= 1.01;
		}
		else if (p->life <= 1) {
			p->scaleX *= 0.9;
			p->scaleY *= 0.9;
		}
	};
	beforeParts.add(p);
}

void Game::pollInput(double dt) {
	sf::Vector2f ppos = player.getPosition();
	float speed = 600;

	bool doSpawnFumes = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
		ppos.y -= dt * speed; doSpawnFumes = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		ppos.x -= dt * speed; doSpawnFumes = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		ppos.y += dt * speed; doSpawnFumes = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		ppos.x += dt * speed; doSpawnFumes = true;
	}

	if (doSpawnFumes)
		spawnFumes();

	player.setPosition(ppos);

	Vector2i mPos = sf::Mouse::getPosition(*win);
	float angle = atan2f(mPos.y - ppos.y, mPos.x - ppos.x);
	cannon.setRotation((angle / (2 * Lib::pi())) * 360);
	ppos.x += 8;
	ppos.y += 4;
	cannon.setPosition(ppos);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {

		if (!wasPressed) {
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

			spawnBullet(pos, ndir);
			wasPressed = true;
		}
	}
	else {
		wasPressed = false;
	}

}

void Game::spawnBullet(Vector2f pos, Vector2f dir) {
	Particle p;
	p.x = pos.x;
	p.y = pos.y;
	p.life = 100;
	p.dx = dir.x * 60 * 10;
	p.dy = dir.y * 60 * 10;

	p.bhv = [](Particle* p, float dt) {//= //& 
		if (p->life <= 10.0) {
			p->dx *= 0.98;
			p->dy *= 0.98;
		}

		if (p->life <= 20.0) {
			p->scaleX *= 0.95;
			p->scaleY *= 0.95;
		}

	};
	afterParts.add(p);
}
