#include "Turtle.hpp"

void Turtle::reset()
{
	angle = 0;
	shape.setPosition(400, 400);
	direction.setRotation(angle);
}

void Turtle::play(std::vector<Cmd> execute) {
	for (Cmd & cmd : execute) {
		switch (cmd)
		{
		case Advance:advance(30);		  break;
		case Backward:backward(30);		  break;
		case TurnLeft45:turnLeft(45);	  break;
		case TurnRight45:turnRight(45);	  break;
		default:
			break;
		}
	}
}
