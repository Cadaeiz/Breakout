#ifndef BALL_H_
#define BALL_H_

#include <SFML/Graphics.hpp>
#include "Collidable.hpp"
#include "BallState.hpp"

class Ball : public Collidable
{
	friend class BallState;
	friend class BallLaunchState;
	friend class BallMovingState;
	friend class BallDyingState;
	friend class BallDeadState;
	const static int LAUNCH = 0, MOVING = 1, DYING = 2, DEAD = 3;
private:
	static struct
	{
		BallLaunchState launch;
		BallMovingState moving;
		BallDyingState dying;
		BallDeadState dead;
	} StateMachine;
	BallState * currentState;
	sf::Sprite sprite;
	sf::Vector2f pos, vel;
	void changeState(int state);
public:
	Ball(sf::Vector2f Pos, sf::Texture & texture, sf::IntRect * rect = 0);
	void update() { currentState -> update(*this); }
	void handleEvent(sf::Event event) { currentState -> handleEvent(*this, event); }
	void draw(sf::RenderWindow & window) { currentState -> draw(*this, window); }
	void collide(Collidable & c) { currentState -> collide(*this, c); }
	bool isDead() { return (currentState == &StateMachine.dead); }
};

#endif
