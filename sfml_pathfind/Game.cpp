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

/// x 0... bcp
// y 0... bcp
// ( combiné x et y ? )
// x + y * (bcp +1) => key collisionnera ni avec x ni avec y

struct ElementOfD{
	sf::Vector2i	pos;
	float		weight;
};
static std::vector<ElementOfD> d;


void addToD(ElementOfD elem) {
	d.push_back(elem);
}

bool getFromD(Vector2i pos, ElementOfD & result) {
	for (ElementOfD& el : d) {
		if (el.pos.x == pos.x && el.pos.y == pos.y) {
			result = el;
			return true;
		}
	}
	return false;
}

int getKey(sf::Vector2i vec) {
	return vec.x + (vec.y * 256);
	//x = 0 => 0
	//x =3 et y = 2
	//key = 3 + 256*2 = 511
	//=> moins de colonne que 256 
}

 bool Game::dij_findMin(std::vector<sf::Vector2i>& q, std::vector<float>& d, Vector2i & result) {
	float min = 1000 * 1000 * 1000;
	Vector2i vertex(-1, -1);
	bool isFound = false;
	for (auto& s : q) {

		if( d[getKey(s)] < min){
			min = d[getKey(s)];
			vertex = s;
			isFound = true;
		}
	}
	result = vertex;
	return isFound;
}

 static float dist(Vector2i s1, Vector2i s2) {
	 return sqrt(pow(s2.x - s1.x, 2) + pow(s2.y - s1.y, 2));
 }

void Game::dij_update(Vector2i s1, Vector2i s2)
{
	int ks1 = getKey(s1);
	int ks2 = getKey(s2);
	float ndist = d[ks1] + dist(s1, s2);
	if (d[ks2] > ndist ) {
		d[ks2] = ndist;
		dij_pred[ks2] = s1;
	}
}

void Game::dij_init(std::vector<sf::Vector2i>& g, Vector2i start)
{
	d.clear();
	d.resize(10000000);
	for (auto& s : g) {
		int key = getKey(s);
		d[key] = 1000 * 1000 * 1000;
	}
	d[getKey(start)] = 0;
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
		*/

		if (ev.key.code == sf::Keyboard::Key::K) {
			dij_init(allNodes, Vector2i(mario.cx, mario.cy));
			std::vector<Vector2i> q;
			q.push_back(Vector2i(66, 67));
			q.push_back(Vector2i(66, 68));
			q.push_back(Vector2i(66, 69));

			std::vector<float> d;
			d.resize(1024 * 1024,1000 * 1000);
			d[getKey(Vector2i(66, 67))] = 3;
			d[getKey(Vector2i(66, 68))] = 4;
			Vector2i res;
			bool found = dij_findMin(q,d,res);
			auto pos = 66;
		}
		

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



