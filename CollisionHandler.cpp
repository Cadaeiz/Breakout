#include "CollisionHandler.hpp"

void CollisionHandler::handleCollisions()
{
	/* iterate through all pairs c1,c2 of Collidable objects in collidables */
	for (int i = 0; i < NUM_TYPES; i++)
	{
		List<Collidable>::Iterator iter1 = collidables[i].getIterator();
		while (iter1.hasNext())
		{
			Collidable & c1 = *iter1.next();
			for (int j = i; j < NUM_TYPES; j++)
			{
				/* if type i can collide with type j */
				if (collisionMatrix[i][j])
				{
					List<Collidable>::Iterator iter2 = collidables[j].getIterator();
					while (iter2.hasNext())
					{
						Collidable & c2 = *iter2.next();
						/* if c1 is currently overlapping with c2, handle the collision */
						if (c1.intersects(c2))
						{
							c1.collide(c2);
							c2.collide(c1);
						}
					}
				}
			}
		}
	}
}
