#ifndef WALL_H_
#define WALL_H_

#define WALLWIDTH 40

#include "Collidable.hpp"

class Wall : public Collidable
{
private:
	sf::Sprite sprite;
	Wall();
public:
	Wall(sf::Vector2f pos, sf::Texture & texture, float length, bool horizontal);
	void update() { }
	void draw(sf::RenderWindow & window) { window.draw(sprite); }
	void handleEvent(sf::Event event) { }
	void collide(Collidable & c) { }
};

#endif
