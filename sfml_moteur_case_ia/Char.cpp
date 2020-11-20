#include "Char.hpp"
#include "Game.hpp"

void Char::setCellPosition(int cx, int cy){
	rx = 0.5;
	ry = 0.99;
	this->cx = cx;
	this->cy = cy;
	setState( Running );
}

void Char::setPosition(int rpx, int rpy) {
	cx = rpx / GRID_SIZE;
	rx = rpx - (cx * GRID_SIZE);

	cy = rpy / GRID_SIZE;
	ry = rpy - (cy * GRID_SIZE);
}

void Char::update(double dt) {

	rx += speedX * dt;
	ry += speedY * dt;

	while (rx > 1) {
		if (isWallHit(cx + 1, cy)) {
			rx = 0.95;
		}
		else {
			rx--;
			cx++;
		}
	}

	while (rx < 0) {
		if (isWallHit(cx - 1, cy)) {
			rx = 0.05;
		}
		else {
			rx++;
			cx--;
		}
	}

	while (ry > 1) {
		if (isWallHit(cx, cy+1)) {
			ry = 0.95;
		}
		else {
			ry--;
			cy++;
		}
	}

	while (ry < 0) {
		if (isWallHit(cx, cy-1)) {
			ry = 0.05;
		}
		else {
			ry++;
			cy--;
		}
	}

	switch (state)
	{
	case Idle:
		if (
			isWallHit(cx, cy - 1)
			|| isWallHit(cx, cy + 1)
			|| isWallHit(cx - 1, cy)
			|| isWallHit(cx + 1, cy)
			) {
			setState(Cover);
		}
		break;
	case Cover:
		break;
	case Walking:
		if ((abs(speedX) < 0.01) && (abs(speedY) < 0.01)) {
			speedX = 0.0;
			speedY = 0.0;
			setState(Idle);
		}
		break;
	case Running:
		if ((abs(speedX) < 0.01) && (abs(speedY) < 0.01)) {
			speedX = 0.0;
			speedY = 0.0;
			setState(Idle);
		}
		break;
	default:
		break;
	}

	speedX *= 0.87;
	speedY *= 0.87;

	spr.setPosition(getPositionPixel());
}

void Char::setState(State st){
	state = st;
	switch (state)
	{
	case Idle:
		spr.setFillColor(sf::Color(0xffffffff));
		break;
	case Cover:
		spr.setFillColor(sf::Color(0xF0E452ff));
		break;
	case Walking:
		spr.setFillColor(sf::Color(0x57FAB1ff));
		break;
	case Running:
		spr.setFillColor(sf::Color(0xF75E59ff));
		break;
	default:
		break;
	}
}

bool Char::isWallHit(int cx, int cy)
{
	return game->isWall(cx,cy);
}

