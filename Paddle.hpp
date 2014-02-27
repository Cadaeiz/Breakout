#ifndef PADDLE_H_
#define PADDLE_H_

#define PADDLEW 160
#define PADDLEH 30

#include "Collidable.hpp"
#include "Wall.hpp"
#include "Ball.hpp"

class Paddle : public Collidable
{
	const static int STEP = 5;
private:
	sf::Sprite sprite;
	Ball * stuckBall;
	void setXPos(float x);
	void move(float dx);
public:
	Paddle(sf::Vector2f pos, sf::Texture & texture);
	void update();
	void draw(sf::RenderWindow & window) { window.draw(sprite); }
	void handleEvent(sf::Event event);
	void collide(Wall & c);
	void collide(Collidable & c) { }
	void attach(Ball * ball) { stuckBall = ball; }
	void detach(Ball * ball) { if  (ball == stuckBall) stuckBall = 0; }
};

#endif
