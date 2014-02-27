#include "Ball.hpp"

Ball::Ball(sf::Vector2f Pos, sf::Texture & texture, float sp, Paddle & paddle) : Collidable(CBCircle(Pos, BALLRAD / 2), 0)
{
	sprite.setTexture(texture);
	sprite.setPosition(Pos);

	sprite.setOrigin(BALLRAD / 2, BALLRAD / 2);

	primaryPaddle = &paddle;
	speed = sp;
	currentState = 0;
	changeState(LAUNCH);
}

void Ball::changeState(int state)
{
	if (currentState)
		currentState -> cleanup(*this);

	switch(state)
	{
	case LAUNCH:
		currentState = &StateMachine.launch;
		break;
	case MOVING:
		currentState = &StateMachine.moving;
		break;
	case DYING:
		currentState = &StateMachine.dying;
		break;
	case DEAD:
		currentState = &StateMachine.dead;
		break;
	}

	currentState -> init(*this);
}

void Ball::setPosition(sf::Vector2f p)
{
	sprite.setPosition(p);
	box -> setPosition(p);
}

void Ball::move(sf::Vector2f dp)
{
	sprite.move(dp);
	box -> move(dp);
}
