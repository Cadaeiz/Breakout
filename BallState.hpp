#ifndef BALLSTATE_H_
#define BALLSTATE_H_

class BallState
{
public:	
	virtual void init(Ball & b) = 0;
	virtual void cleanup(Ball & b) = 0;
	virtual void update(Ball & b) = 0;
	void handleEvent(Ball & b, sf::Event event) { }
	void draw(Ball & b, sf::RenderWindow & window) { window.draw(t.sprite); }
	virtual void collide(Ball & b, Collidable & c) = 0;

};

class BallLaunchState : public BallState
{
	void init(Ball & b);
	void cleanup(Ball & b);
	void update(Ball & b);
	void handleEvent(Ball & b, sf::Event event);
	void collide(Ball & b, Collidable & c) { }
};

class BallMovingState : public BallState
{
	void init(Ball & b);
	void cleanup(Ball & b);
	void update(Ball & b);
	void handleEvent(Ball & b, sf::Event event) { }
	void collide(Ball & b, Collidable & c);
};

class BallDyingState : public BallState
{
	void init(Ball & b);
	void cleanup(Ball & b);
	void update(Ball & b);
	void handleEvent(Ball & b, sf::Event event) { }
	void collide(Ball & b, Collidable & c) { }
};

class BallDeadState : public BallState
{
	void init(Ball & b) { }
	void cleanup(Ball & b) { }
	void update(Ball & b) { }
	void handleEvent(Ball & b, sf::Event event) { }
	void collide(Ball & b, Collidable & c) { }
};
#endif
