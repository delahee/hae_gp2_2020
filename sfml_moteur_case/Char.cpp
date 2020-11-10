#include "Char.hpp"

void Char::setCellPosition(int cx, int cy)
{
	rx = 0.5;
	ry = 0.0;
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
	if (rx > 1)
		while (rx > 1) {
			rx--;
			cx++;
		}

	if (rx < 0)
		while (rx < 0) {
			rx++;
			cx--;
		}

	spr.setPosition(getPositionPixel());
}
