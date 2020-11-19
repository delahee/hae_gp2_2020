#include "Char.hpp"
#include "Game.hpp"

void Char::setCellPosition(int cx, int cy){
	rx = 0.5;
	ry = 0.99;
	this->cx = cx;
	this->cy = cy;
	state = Running;
	updateState = doRunningState;
}

void Char::setPosition(int rpx, int rpy) {
	cx = rpx / GRID_SIZE;
	rx = rpx - (cx * GRID_SIZE);

	cy = rpy / GRID_SIZE;
	ry = rpy - (cy * GRID_SIZE);
}

void Char::update(double dt) {

	if (state == Jumping) {
		speedY += gravityY;
	}

	if (speedY > maxFallSpeedY) {
		//speedY = maxFallSpeedY;
	}

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

	if (updateState) {
		updateState(this);
	}

	/*
	if (state == Jumping) {
		doJumpingState();
	}
	else 
	if (state == Running) {
		doRunningState();
	}
	*/

	speedX *= 0.87;

	spr.setPosition(getPositionPixel());
}

void Char::doRunningState(Char*lthis) {
	int cx = lthis->cx;
	int cy = lthis->cy;
	if (!lthis->isWallHit(cx, cy + 1)) {
		lthis->updateState = doJumpingState;
		lthis->state = Jumping;
	}
}

void Char::doJumpingState(Char* lthis) {
	if (lthis->speedY < 0)
		while (lthis->ry < 0) {
			lthis->ry++;
			lthis->cy--;
		}

	if (lthis->speedY > 0)
		while (lthis->ry > 0.99) {
			if (lthis->isWallHit(lthis->cx, lthis->cy + 1)) {
				lthis->ry = 0.99;
				lthis->speedY = 0.0;
				lthis->speedX *= 0.5;
				lthis->state = Running;
				lthis->updateState = doRunningState;
				break;
			}
			else {
				lthis->ry--;
				lthis->cy++;
			}
		}
}

void Char::setState(State st){
	state = st;
	if (st == Running) {
		
		updateState = doRunningState;
	}
	else if (st == Jumping) {
		updateState = doJumpingState;
	}
}

bool Char::isWallHit(int cx, int cy)
{
	return game->isWall(cx,cy);
}
