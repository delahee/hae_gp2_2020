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
					if( strCmd == "Advance" )		cmds.push_back(Advance);
					if( strCmd == "Backward" )		cmds.push_back(Backward);
					if( strCmd == "TurnLeft45" )	cmds.push_back(TurnLeft45);
					if( strCmd == "TurnRight45" )	cmds.push_back(TurnRight45);
				} while (retVal != EOF);

				turtle.reset();
				turtle.playProgressive(cmds);
			}

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
