#ifndef PADDLE_H_
#define PADDLE_H_

#include "Collidable.hpp"

class Paddle : public Collidable
{
	sf::Sprite sprite;
	float xpos;
public:
	Paddle(sf::Vector2f pos, sf::Texture & texture, sf::IntRect * rect = 0);
	void draw(sf::RenderWindow & window) { window.draw(sprite); }
	void collide(Collidable & c);
	void move(float dx);
};

#endif
