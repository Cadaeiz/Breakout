#include "Ball.hpp"

struct Ball::Machine Ball::StateMachine;
sf::SoundBuffer Ball::bounceBuffer, Ball::deadBuffer, Ball::launchBallBuffer, Ball::tileBounceBuffer;



Ball::Ball(sf::Texture & texture, float sp, Paddle & paddle) : Collidable(CBCircle(sf::Vector2f(0,0),BALLRAD), 0)
{
	/* place ball above center of paddle */
	setPosition(paddle.getCenter() - sf::Vector2f(0,(float) BALLRAD+paddle.getSize().y/2));
	sprite.setTexture(texture);

	sprite.setOrigin(BALLRAD, BALLRAD);

	primaryPaddle = &paddle;
	speed = sp;
	currentState = 0;
	changeState(LAUNCH);

	bounceSound.setBuffer(bounceBuffer);
	deadSound.setBuffer(deadBuffer);
	launchBallSound.setBuffer(launchBallBuffer);
	tileBounceSound.setBuffer(tileBounceBuffer);
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

void Ball::loadSounds()
{
	bounceBuffer.loadFromFile("bounce.wav");
	deadBuffer.loadFromFile("dead.wav");
	launchBallBuffer.loadFromFile("launchBall.wav");
	tileBounceBuffer.loadFromFile("tileBounce.wav");
}
