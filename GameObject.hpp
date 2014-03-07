#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <SFML/Graphics.hpp>

class GameObject
{
	virtual void update(float time) = 0;
	virtual void draw(sf::RenderWindow & window) = 0;
	virtual void handleEvent(sf::Event event) = 0;
};

#endif
