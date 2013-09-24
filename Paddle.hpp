#ifndef PADDLE_H_
#define PADDLE_H_

#include "Collidable.hpp"
#include "Wall.hpp"

#define PADDLESTEP 5


class Paddle : public Collidable
{
private:
	sf::Sprite sprite;
	sf::Vector2f size;
	void setXPos(float x);
	void move(float dx);
public:
	Paddle(sf::Vector2f pos, sf::Texture & texture);
	void update();
	void draw(sf::RenderWindow & window) { window.draw(sprite); }
	void handleEvent(sf::Event event);
	void collide(Wall & c);
	void collide(Collidable & c) { }
};

#endif
