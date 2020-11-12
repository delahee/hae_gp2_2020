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
		if (ev.key.code == sf::Keyboard::Key::Z)
			//turtle.advance(30);
			turtle.advance2(30);
			
		if (ev.key.code == sf::Keyboard::Key::S)
			turtle.backward(30);
		
		if (ev.key.code == sf::Keyboard::Key::Q)
			turtle.turnLeft(45);
		
		if (ev.key.code == sf::Keyboard::Key::D)
			turtle.turnRight(45);

		if (ev.key.code == sf::Keyboard::Key::R) {
			turtle.reset();
		}

		if (ev.key.code == sf::Keyboard::Key::F) {
			parse();
		}
		// ouvrir le descripteur de fichier
		//
		// F lire le ficher
		// lire 0 pour avancer
		// lire 1 pour reculer
		// lire 2 pour tourner a g / 3 tourner a droite
		// execute la liste de commande
		// on ferme le fichier

		if (ev.key.code == sf::Keyboard::Key::T) {
			vector<Cmd> cmds = { Cmd::Advance, Cmd::Advance, Cmd::Advance, Cmd::Advance,Cmd::TurnLeft45, Cmd::Advance };
			turtle.reset();
			turtle.play(cmds);
		}
	}
}

 void Game::draw(sf::RenderWindow & win) {
	if (closing) return;

	win.draw(bg);

	beforeParts.draw(win);

	turtle.draw(win);

	afterParts.draw(win);
}

void Game::parse() {
	FILE * cmd = fopen("res/cmd.txt", "r");
	if (!cmd) {
		//
		printf("no such file res/cmd.txt\n");
	}
	else {
		vector<Cmd> cmds;
		int retVal = 0;
		do {
			char _cmd[128] = {};
			retVal = fscanf(cmd, "%s", _cmd);
			string strCmd(_cmd);
			if (strCmd == "Advance")			cmds.push_back(Advance);
			else if (strCmd == "Backward")		cmds.push_back(Backward);
			else if (strCmd == "TurnLeft45")	cmds.push_back(TurnLeft45);
			else if (strCmd == "TurnRight45")	cmds.push_back(TurnRight45);
			else if (strCmd == "DrawOn")		cmds.push_back(DrawOn);
			else if (strCmd == "DrawOff")		cmds.push_back(DrawOff);
			else {
				printf("does not understand cmd %s", _cmd);
				break;
			}
		} while (retVal != EOF);

		turtle.reset();
		turtle.playProgressive(cmds);
	}
}
void Game::pollInput(double dt) {
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

static time_t lastModification = 0;
static struct stat statDesc;

void Game::onFileTick() {
	stat("res/cmd.txt", &statDesc);

	if (lastModification < statDesc.st_mtime) {
		parse();
		lastModification = statDesc.st_mtime;
	}
}

static float timer = 0.0;
void Game::update(double dt) {
	pollInput(dt);

	beforeParts.update(dt);
	turtle.update(dt);
	afterParts.update(dt);

	timer -= dt;
	if (timer <= 0.0) {
		onFileTick();
		timer = 0.1;
	}
}
