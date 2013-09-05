#include "Collidable.hpp"

sf::Vector2f Collidable::getCenter()
{
	float x = collisionBox.left + collisionBox.width / 2;
	float y = collisionBox.top + collisionBox.height / 2;
	return sf::Vector2f(x,y);
}

bool Collidable::intersects(Collidable & c)
{	
	return collisionBox.intersects(c.collisionBox);
}
