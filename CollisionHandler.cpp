#include "CollisionHandler.hpp"
#include "Collidable.hpp"

CollisionHandler::CollisionHandler()
{
	for (int i = 0; i < NUM_TYPES; i++)
	{
		collisionMatrix[0][i] = true;
		collisionMatrix[i][0] = true;
		if (i > 0)
			for (int j = 1; j < NUM_TYPES; j++)
			{
				collisionMatrix[j][i] = false;
				collisionMatrix[j][i] = false;
			}
	}

	collisionMatrix[1][2] = collisionMatrix[2][1] = true;
}

void CollisionHandler::handleCollisions()
{
	/* iterate through all pairs c1,c2 of Collidable objects in collidables */
	for (int i = 0; i < NUM_TYPES; i++)
	{
		List<Collidable>::Iterator iter1 = collidables[i].getIterator();
		while (iter1.hasNext())
		{
			Collidable * c1 = iter1.next();
			for (int j = i; j < NUM_TYPES; j++)
			{
				/* if type i can collide with type j */
				if (collisionMatrix[i][j])
				{
					List<Collidable>::Iterator iter2 = collidables[j].getIterator();
					while (iter2.hasNext())
					{
						Collidable * c2 = iter2.next();
						/* if c1 is currently overlapping with c2, handle the collision */
						if ((c1 != c2) && c1 -> intersects(c2))
						{
							c1 -> collide(c2);
							c2 -> collide(c1);
						}
					}
				}
			}
		}
	}
}


bool CollisionHandler::checkCollisions(Collidable & c)
{
	for (int i = 0; i < NUM_TYPES; i++)
	{
		List<Collidable>::Iterator iter = collidables[i].getIterator();
		while(iter.hasNext())
		{
			Collidable * c2 = iter.next();
			if (&c != c2 && c.intersects(c2))
				return true;
		}
	}

	return false;
}