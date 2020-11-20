#pragma once

#include "SFML/Graphics.hpp"
#include <functional>

using namespace sf;

class Game;

enum State {
	Running,
};

class Char;

class CState {
public:
		Char* c = nullptr;
		CState(Char* _c) : c(_c) {
			//this->c = _c;
		};
		virtual void	updateState() = 0; 
};

class CRunningState : public CState {
public:
					CRunningState(Char* _c) : CState(_c) { };
	virtual void	updateState() override;
};

class Char {
public:
	static constexpr int GRID_SIZE = 16;

	sf::RectangleShape	spr;
	Game*				game = nullptr;

	Char(Game*g=nullptr) {
		spr = RectangleShape(Vector2f(16,16*3));
		spr.setFillColor(sf::Color(0xFA3092ff));
		spr.setOrigin(8, 16*2.5);
		this->game = g;
	}

	float speedX = 0.0;//rx par secondes
	float speedY = 0.0;//rx par secondes

	//float maxFallSpeedY = 80.0;
	//float gravityY = 4;

	State state = Running;
	CState* cupdateState = nullptr;

	int		cx = 0;
	float	rx = 0.0;

	int		cy = 0;
	float	ry = 0.0;

	void setCellPosition(int cx, int cy);
	void setPosition(int rpx, int rpy);

	Vector2f getPositionPixel() {
		return Vector2f(cx*GRID_SIZE + rx * GRID_SIZE, cy*GRID_SIZE + ry * GRID_SIZE);
	}

	void update(double dt);

	void draw(sf::RenderWindow & win) {
			win.draw(spr);
	}

	void setState(State st);
	bool isWallHit(int cx, int cy);

	//void doRunningState();
	//void doJumpingState();
	//std::function<void(Char&)> updateState2;

	//std::mem_fn<Char::*,void(void)> test;
};