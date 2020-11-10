#include "Char.hpp"

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
