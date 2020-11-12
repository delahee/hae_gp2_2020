#include "Char.hpp"
#include "Game.hpp"

void Char::setCellPosition(int cx, int cy)
{
	rx = 0.5;
	ry = 0.99;
	this->cx = cx;
	this->cy = cy;
}

void Char::setPosition(int rpx, int rpy) {
	cx = rpx / GRID_SIZE;
	rx = rpx - (cx * GRID_SIZE);

	cy = rpy / GRID_SIZE;
	ry = rpy - (cy * GRID_SIZE);
}

void Char::update(double dt) {
	while (rx > 1) {
		if (isWallHit(cx + 1, cy)) {
			rx = 0.5;
		}
		else {
			rx--;
			cx++;
		}
	}

	while (rx < 0) {
		if (isWallHit(cx - 1, cy)) {
			rx = 0.5;
		}
		else {
			rx++;
			cx--;
		}
	}

	spr.setPosition(getPositionPixel());
}

bool Char::isWallHit(int cx, int cy)
{
	return game->isWall(cx,cy);
}
