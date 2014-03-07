#ifndef COLLIDABLE_H_
#define COLLIDABLE_H_


#include "GameObject.hpp"
#include "CollisionBox.hpp"

class Collidable : public GameObject
{
protected:
	CollisionBox * box;
	int collisionType;
public:
	/* constructor: initializes collision box, adds object to collision handler */
	Collidable(int type);
	Collidable(CBRect & rect, int type);
	Collidable(CBCircle & circle, int type);
	Collidable(CBArray & arr, int type);
	/* destructor: removes object from collision handler */
	~Collidable();
	int getType() { return collisionType; }
	sf::Vector2f getCenter() { return box -> getCenter(); }
	sf::Vector2f getSize() { return box -> getSize(); }
	CollisionBox & getCollisionBox() { return *box; }
	bool intersects(Collidable & c) { return box -> intersects(c.getCollisionBox()); }
	virtual void collide(Collidable & c) = 0;
};


#endif
