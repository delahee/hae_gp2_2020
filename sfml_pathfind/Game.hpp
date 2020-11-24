#pragma once

#include <vector>
#include <unordered_map>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "Particle.hpp"
#include "ParticleMan.hpp"
#include "Char.hpp"
#include <algorithm>
#include <unordered_map>

using namespace sf;


// comment stocker mon graph ? 
// comment sotcker des noeud (x,y)  qui représente les sommets du graph ?
// std::vector<sf::Vector2i>
// std::vector<std::pair(int cx, intcy)>
//
using std::size_t;
using std::hash;
using std::string;
namespace std {
	template <>
	struct hash<sf::Vector2i>{
		std::size_t operator()(const sf::Vector2i& k) const{
			return (hash<int>()(k.x) ^ (hash<int>()(k.y)) << 1);
		};
	};
}

class HotReloadShader;
class Game {
public:
	sf::RenderWindow*	win = nullptr;

	sf::RectangleShape  bg;
	HotReloadShader *	bgShader = nullptr;
	HotReloadShader *	doubleShader = nullptr;
	HotReloadShader *	displaceShader = nullptr;

	sf::Texture			tex;
	sf::Texture			tex2;
	sf::Texture			displaceMap;

	sf::RectangleShape	displace;

	Char				mario;

	bool				closing = false;
	
	std::vector<sf::Vector2i>		walls;
	std::vector<sf::RectangleShape> wallSprites;

	ParticleMan beforeParts;
	ParticleMan afterParts;

	Game(sf::RenderWindow * win);

	void cacheWalls();

	void processInput(sf::Event ev);
	bool wasPressed = false;
	void pollInput(double dt);
	void onSpacePressed();

	void update(double dt);

	void draw(sf::RenderWindow& win);

	void onFileTick();
	bool isWall(int cx, int cy);

	//creer la liste de toutes les cases pour dijkstra
	void createsNodes();

	std::vector<sf::Vector2i> allNodes;//0,0 1,1 2,2=>mur ?

	std::vector<sf::Vector2i> dij_pred;
	std::vector<float> d;
	void dij_init(std::vector<sf::Vector2i> & g, Vector2i start);
	bool dij_findMin(
		std::vector<sf::Vector2i>& q, 
		std::vector<float>& d,
		Vector2i& result);

	void dij_update(Vector2i s1, Vector2i s2);
};

