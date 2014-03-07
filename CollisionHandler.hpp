#ifndef COLLISIONHANDLER_H_
#define COLLISIONHANDLER_H_

#define NUM_TYPES 4

#include "Collidable.hpp"


class CollisionHandler
{
	friend class Collidable;
private:
	List<Collidable> collidables[NUM_TYPES];
	bool collisionMatrix[NUM_TYPES][NUM_TYPES];

	void addCollidable(Collidable * c) { collidables[c -> getType()].addItem(c); }
	void removeCollidable(Collidable * c) { collidables[c -> getType()].removeItem(c); }
public:
	CollisionHandler();
	void handleCollisions();
	bool checkCollisions(Collidable & c);
};

#endif
