#ifndef BALL_H_
#define BALL_H_

#include "Collidable.hpp"

class Ball : public Collidable
{
	sf::Sprite sprite;
	sf::Vector2f pos, vel;
public:
	Ball(sf::Vector2f Pos, sf::Texture & texture, sf::IntRect * rect = 0);
	void draw(sf::RenderWindow & window) { window.draw(sprite); }
	void collide(Collidable & c);
};

#endif
