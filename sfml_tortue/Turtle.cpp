#include "Turtle.hpp"

void Turtle::update(double dt){
	life += dt;
	if (cmdBuffer.size()) {
		if (life > 1.0) {
			play(cmdBuffer[0]);
			cmdBuffer.erase(cmdBuffer.begin());
			life = 0;
		}
	}

	angle = (targetAngle - angle) * 0.12 + angle;
	Vector2f position = shape.getPosition();
	position.x = (targetPosition.x - position.x) * 0.1 + position.x;
	position.y = (targetPosition.y - position.y) * 0.1 + position.y;
	_setPosition(position);
	direction.setRotation(angle);
}

void Turtle::reset()
{
	targetAngle = angle = 0;
	shape.setPosition(400, 400);
	targetPosition = shape.getPosition();
	direction.setRotation(angle);
}

void Turtle::play(Cmd exe) {
	switch(exe)
	{
		case Advance:		advance(30);		break;
		case Backward:		backward(30);		break;
		case TurnLeft45:	turnProgressive(45);		break;
		case TurnRight45:	turnProgressive(-45);		break;
		default:
			break;
	}
}

void Turtle::play(std::vector<Cmd> execute) {
	for (Cmd & cmd : execute) 
		play(cmd);
}

void Turtle::playProgressive(std::vector<Cmd> & execute) {
	cmdBuffer = execute;
}
