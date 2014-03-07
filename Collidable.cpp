#include "Collidable.hpp"
#include "CollisionHandler.hpp"
#include "Singleton.hpp"

#define HANDLER Singleton<CollisionHandler>::getInstance()


Collidable::Collidable(int type = 0) : box(new CBRect(0,0,0,0)), collisionType(type) 
{
	HANDLER -> addCollidable(this); 
} /* default type is rectangle */

Collidable::Collidable(CBRect & rect, int type = 0) : box(new CBRect(rect)), collisionType(type)
{
	HANDLER -> addCollidable(this); 
}

Collidable::Collidable(CBCircle & circle, int type = 0) : box(new CBCircle(circle)), collisionType(type)
{
	HANDLER -> addCollidable(this); 
}

Collidable::Collidable(CBArray & arr, int type = 0) : box(new CBArray()), collisionType(type)
{
	HANDLER -> addCollidable(this); 
} /* does not use given array to add boxes (change later?) */

/* destructor: removes object from collision handler */
Collidable::~Collidable() 
{
	HANDLER -> removeCollidable(this); 
}