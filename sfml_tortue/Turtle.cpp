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
}

void Turtle::reset()
{
	angle = 0;
	shape.setPosition(400, 400);
	direction.setRotation(angle);
}

void Turtle::play(Cmd exe) {
	switch(exe)
	{
		case Advance:		advance(30);		break;
		case Backward:		backward(30);		break;
		case TurnLeft45:	turnLeft(45);		break;
		case TurnRight45:	turnRight(45);		break;
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
