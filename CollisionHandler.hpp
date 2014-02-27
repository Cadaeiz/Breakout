#ifndef COLLISIONHANDLER_H_
#define COLLISIONHANDLER_H_

#define NUM_TYPES 4

#include "Collidable.hpp"

class CollisionHandler
{
	friend class Collidable;
private:
	List<Collidable> collidables[NUM_TYPES];
	bool collisionMatrix[NUM_TYPES][NUM_TYPES] = {{true, true,  true,  true },  /* type 0: Ball collisions */
												  {true, false, true,  false},  /* type 1: Paddle collisions */
												  {true, true,  false, false},  /* type 2: Wall collisions */
												  {true, false, false, false}}; /* type 3: Tile collisions */
	
	void addCollidable(Collidable * c) { collidables[c -> getType()].addItem(c); }
	void removeCollidable(Collidable * c) { collidables[c -> getType()].removeItem(c); }
public:
	CollisionHandler() { }
	void handleCollisions();
};

#endif
