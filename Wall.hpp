#ifndef WALL_H_
#define WALL_H_

#include "Collidable.hpp"

class Wall : public Collidable
{
	sf::Sprite sprite;
public:
	Wall(sf::Vector2f pos, sf::Texture & texture, sf::IntRect * rect = 0);
	void draw(sf::RenderWindow & window) { window.draw(sprite); }
	void collide(Collidable & c) { }
};

#endif
