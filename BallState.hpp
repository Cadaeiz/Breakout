#ifndef BALLSTATE_H_
#define BALLSTATE_H_

#include <SFML/Graphics.hpp>

class Ball;
class Paddle;
class Collidable;

class BallState
{
public:	
	virtual void init(Ball & b) = 0;
	virtual void cleanup(Ball & b) = 0;
	virtual void update(Ball & b, float time) = 0;
	virtual void handleEvent(Ball & b, sf::Event event) = 0;
	virtual void draw(Ball & b, sf::RenderWindow & window);
	virtual void collide(Ball & b, Collidable & c) = 0;
};

class BallLaunchState : public BallState
{
	void init(Ball & b);
	void cleanup(Ball & b);
	void update(Ball & b, float time);
	void handleEvent(Ball & b, sf::Event event);
	void draw(Ball & b, sf::RenderWindow & window);
	void collide(Ball & b, Collidable & c) { }
};

class BallMovingState : public BallState
{
	void init(Ball & b);
	void cleanup(Ball & b) { }
	void update(Ball & b, float time);
	void handleEvent(Ball & b, sf::Event event) { }
	void collide(Ball & b, Paddle & p);
	void collide(Ball & b, Collidable & c);
};

class BallDyingState : public BallState
{
	void init(Ball & b);
	void cleanup(Ball & b) { }
	void update(Ball & b, float time);
	void handleEvent(Ball & b, sf::Event event) { }
	void collide(Ball & b, Collidable & c) { }
};

class BallDeadState : public BallState
{
	void init(Ball & b) { }
	void cleanup(Ball & b) { }
	void update(Ball & b, float time) { }
	void handleEvent(Ball & b, sf::Event event) { }
	void collide(Ball & b, Collidable & c) { }
};
#endif
