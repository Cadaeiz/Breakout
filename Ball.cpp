#include "Ball.hpp"

Ball::Ball(sf::Vector2f Pos, sf::Texture & texture, float sp, Paddle & paddle)
{
	sprite.setTexture(texture);
	sprite.setPosition(Pos);

	collisionBox = sf::FloatRect(sprite.getGlobalBounds());

	size = sf::Vector2f(collisionBox.width, collisionBox.height);
	sprite.setOrigin(size.x / 2, size.y / 2);

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
	collisionBox.left = p.x - collisionBox.width / 2;
	collisionBox.top = p.y - collisionBox.height / 2;
}

void Ball::move(sf::Vector2f dp)
{
	sprite.move(dp);
	collisionBox.left += dp.x;
	collisionBox.top += dp.y;
}
