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

	
	//if (updateState2) {
	//	updateState2(*this);
	//}
	if (cupdateState)
		cupdateState->updateState();

	speedX *= 0.87;

	spr.setPosition(getPositionPixel());
}

/*
void Char::doRunningState() {
	if (!isWallHit(cx, cy + 1)) {
		setState(Jumping);
	}
}
*/

/*
void Char::doJumpingState() {
	if (speedY < 0)
		while (ry < 0) {
			ry++;
			cy--;
		}

	if (speedY > 0)
		while (ry > 0.99) {
			if (isWallHit(cx, cy + 1)) {
				ry = 0.99;
				speedY = 0.0;
				speedX *= 0.5;
				setState(Running);
				break;
			}
			else {
				ry--;
				cy++;
			}
		}
}
*/

void Char::setState(State st){
	state = st;
	if (st == Running) {
		//updateState2 = std::mem_fn(&Char::doRunningState);
		delete(cupdateState);
		cupdateState = new CRunningState(this);
	}
	else if (st == Jumping) {
		//updateState2 = std::mem_fn(&Char::doJumpingState);
		delete(cupdateState);
		cupdateState = new CJumpingState(this);
	}
}

bool Char::isWallHit(int cx, int cy)
{
	return game->isWall(cx,cy);
}

void CJumpingState::updateState() {

	if (c->speedY < 0)
		while (c->ry < 0) {
			c->ry++;
			c->cy--;
		}

	if (c->speedY > 0)
		while (c->ry > 0.99) {
			if (c->isWallHit(c->cx, c->cy + 1)) {
				c->ry = 0.99;
				c->speedY = 0.0;
				c->speedX *= 0.5;
				c->setState(Running);
				break;
			}
			else {
				c->ry--;
				c->cy++;
			}
		}
}

void CRunningState::updateState() {
	if (!c->isWallHit(c->cx, c->cy + 1)) {
		c->setState(Jumping);
	}
}
