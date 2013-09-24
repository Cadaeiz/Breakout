#ifndef COLLIDABLE_H_
#define COLLIDABLE_H_


#include "GameObject.hpp"

class Collidable : public GameObject
{
protected:
	sf::FloatRect collisionBox;
public:
	Collidable() : collisionBox(0,0,0,0) { }
	Collidable(sf::FloatRect & box) : collisionBox(box) { }
	Collidable(sf::Vector2f & pos, sf::Vector2f & size) : collisionBox(pos,size) { }
	sf::Vector2f getCenter();
	sf::FloatRect getCollisionBox() { return collisionBox; }
	virtual bool intersects(Collidable & c);
	virtual void collide(Collidable & c) = 0;
};


#endif
