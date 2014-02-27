#ifndef COLLIDABLE_H_
#define COLLIDABLE_H_

#define HANDLER Singleton<CollisionHandler>::getInstance()

#include "GameObject.hpp"
#include "CollisionBox.hpp"
#include "CollisionHandler.hpp"
#include "Singleton.hpp"

class Collidable : public GameObject
{
protected:
	CollisionBox * box;
	int collisionType;
public:
	/* constructor: initializes collision box, adds object to collision handler */
	Collidable(int type = 0) : box(new CBRect(0,0,0,0)), collisionType(type) 
							   { HANDLER -> addCollidable(this); } /* default type is rectangle */
	Collidable(CBRect & rect, int type = 0) : box(new CBRect(rect)), collisionType(type)
							   { HANDLER -> addCollidable(this); }
	Collidable(CBCircle & circle, int type = 0) : box(new CBCircle(circle)), collisionType(type)
							   { HANDLER -> addCollidable(this); }
	Collidable(CBArray & arr, int type = 0) : box(new CBArray()), collisionType(type)
							   { HANDLER -> addCollidable(this); } /* does not use given array to add boxes (change later?) */
	/* destructor: removes object from collision handler */
	~Collidable() { HANDLER -> removeCollidable(this); }
	int getType() { return collisionType; }
	sf::Vector2f getCenter() { return box -> getCenter(); }
	sf::Vector2f getSize() { return box -> getSize(); }
	CollisionBox getCollisionBox() { return *box; }
	bool intersects(Collidable & c) { return box -> intersects(c.getCollisionBox()); }
	virtual void collide(Collidable & c) = 0;
};


#endif
