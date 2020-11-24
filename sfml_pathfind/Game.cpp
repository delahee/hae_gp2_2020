#include "Char.hpp"
#include "Game.hpp"
#include "HotReloadShader.hpp"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

static int cols = 1280 / Char::GRID_SIZE;
static int lastLine = 720 / Char::GRID_SIZE - 1;

Game::Game(sf::RenderWindow * win) {
	this->win = win;
	bg = sf::RectangleShape(Vector2f(win->getSize().x, win->getSize().y));
	displace = sf::RectangleShape(Vector2f(1280,720));

	bool isOk = tex.loadFromFile("res/bg.jpg");
	if (!isOk) {
		printf("ERR : LOAD FAILED\n");
	}

	isOk = tex2.loadFromFile("res/bg2.jpg");
	if (!isOk)  printf("ERR : LOAD FAILED\n");
	
	isOk = displaceMap.loadFromFile("res/nm.png");
	if (!isOk)  printf("ERR : LOAD FAILED\n");

	bg.setTexture(&tex);
	displace.setTexture(&tex);
	bg.setSize(sf::Vector2f(1280, 720));

	bgShader = new HotReloadShader("res/bg.vert", "res/bg_time.frag");
	doubleShader = new HotReloadShader("res/bg.vert", "res/double.frag");
	displaceShader = new HotReloadShader("res/bg.vert", "res/displace.frag");
	
	for (int i = 0; i < 1280 / Char::GRID_SIZE; ++i) {
		walls.push_back( Vector2i(i, 0) );
		walls.push_back( Vector2i(i, lastLine) );

		walls.push_back( Vector2i(0, i) );
		walls.push_back( Vector2i(cols-1, i) );
	}

	
	cacheWalls();
	//mario.setPosition((int)1280 * 0.5, 720);

	mario = Char(this);
	mario.setCellPosition(cols>>1, lastLine-1);
}



void Game::cacheWalls()
{
	wallSprites.clear();
	for (Vector2i & w : walls) {
		sf::RectangleShape rect(Vector2f(16,16));
		rect.setPosition(w.x * Char::GRID_SIZE, w.y * Char::GRID_SIZE);
		rect.setFillColor(sf::Color(0x07ff07ff));
		wallSprites.push_back(rect);
	}

	createsNodes();
}

void Game::createsNodes(){
	allNodes.clear();
	for (int cx = 0; cx < cols; ++cx) {
		for (int cy = 0; cy < lastLine; ++cy) {
			Vector2i cell(cx, cy);
			if (!isWall(cx, cy))
				allNodes.push_back(cell);
		}
	}
}


void Game::processInput(sf::Event ev) {
	if (ev.type == sf::Event::Closed) {
		win->close();
		closing = true;
		return;
	}
	if (ev.type == sf::Event::KeyReleased) {
		/*
		if (ev.key.code == sf::Keyboard::Key::Z) {
		}
			
		if (ev.key.code == sf::Keyboard::Key::S) {
			
		}
		
		if (ev.key.code == sf::Keyboard::Key::Q) {
		}
		
		if (ev.key.code == sf::Keyboard::Key::D) {
		}
		*/

		if (ev.key.code == sf::Keyboard::Key::R) {
			mario.setCellPosition(cols >> 1, lastLine-1);
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

	//add walls on click
	if (ev.type == sf::Event::MouseButtonPressed ) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
			int wx = ev.mouseButton.x / Char::GRID_SIZE;
			int wy = ev.mouseButton.y / Char::GRID_SIZE;
			for (auto iter = walls.begin(); iter != walls.end(); iter++) {
				auto& w = *iter;
				if (w.x == wx && w.y == wy) {
					iter = walls.erase(iter);
					cacheWalls();
					return;
				}
			}
			walls.emplace_back(wx, wy);
			cacheWalls();
		}
		else {
			float destRx = 1.0 * ev.mouseButton.x / Char::GRID_SIZE;
			float destRy = 1.0 * ev.mouseButton.y / Char::GRID_SIZE;

			float myRx = mario.cx + mario.rx;
			float myRy = mario.cy + mario.ry;

			float dx = destRx - myRx;
			float dy = destRy - myRy;

			float len = sqrt(dx * dx + dy * dy);

			if (len != 0.0) {
				mario.setState(WalkTo);

				float dirX = dx / len;
				float dirY = dy / len;
				mario.speedX = dirX * 10;
				mario.speedY = dirY * 10;
				mario.destX = destRx;
				mario.destY = destRy;
			}	
		}
	}
}


static float g_time = 0.0;
static float g_tickTimer = 0.0;
void Game::update(double dt) {
	pollInput(dt);

	g_time += dt;
	if (bgShader) bgShader->update(dt);
	if (doubleShader) doubleShader->update(dt);
	if (displaceShader) displaceShader->update(dt);

	beforeParts.update(dt);

	mario.update(dt);

	afterParts.update(dt);

	g_tickTimer -= dt;
	if (g_tickTimer <= 0.0) {
		onFileTick();
		g_tickTimer = 0.1;
	}
}

 void Game::draw(sf::RenderWindow & win) {
	if (closing) return;

	{
		sf::RenderStates states = sf::RenderStates::Default;
		sf::Shader* sh = &bgShader->sh;
		states.shader = sh;
		sh->setUniform("texture", tex);
		
		sh->setUniform("time", g_time);
		win.draw(bg, states);
	}

	{
		sf::RenderStates states = sf::RenderStates::Default;
		sf::Shader* sh = &displaceShader->sh;
		states.shader = sh;
		sh->setUniform("texture", tex);
		sh->setUniform("texture2", displaceMap);
		sh->setUniform("uvTranslateDisp", Glsl::Vec2::Vector2(0, 0));
		sh->setUniform("uvScaleDisp", Glsl::Vec2::Vector2(1, 1));
		sh->setUniform("time", g_time);
		win.draw(displace, states);
	}

	beforeParts.draw(win);

	for (sf::RectangleShape & r : wallSprites)
	
		win.draw(r);

	sf::CircleShape sh(3, 3);
	sh.setFillColor(sf::Color(0xff0000ff));
	for (Vector2i& r : allNodes) {
		sh.setPosition(r.x * Char::GRID_SIZE + Char::GRID_SIZE * 0.5, r.y * Char::GRID_SIZE + Char::GRID_SIZE * 0.5);
		win.draw(sh);
	}


	//turtle.draw(win);
	mario.draw(win);

	afterParts.draw(win);
}

void Game::pollInput(double dt) {

	float lateralSpeed = 1.0;
	float maxSpeed = 10.0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		mario.setState(Running);
	}

	if (mario.state == Running) {
		lateralSpeed *= 2.0;
		maxSpeed *= 10.0;
	}

	bool moved = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		mario.speedX -= lateralSpeed;
		if (mario.speedX < -maxSpeed)
			mario.speedX = -maxSpeed;
		moved = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		mario.speedX += lateralSpeed;
		if (mario.speedX > maxSpeed)
			mario.speedX = maxSpeed;
		moved = true;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
		mario.speedY -= lateralSpeed;
		if (mario.speedY < -maxSpeed)
			mario.speedY = -maxSpeed;
		moved = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		mario.speedY += lateralSpeed;
		if (mario.speedY > maxSpeed)
			mario.speedY = maxSpeed;
		moved = true;
	}

	if (moved) {
		if (mario.state == Cover)
			mario.setState(Walking);
		//walkin  nope 
		//running nope
		if (mario.state == Idle)
			mario.setState(Walking);

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

bool Game::isWall(int cx, int cy)
{
	for (Vector2i & w : walls) {
		if (w.x == cx && w.y == cy)
			return true;
	}
	return false;
}


