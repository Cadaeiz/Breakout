#include "CollisionHandler.hpp"

void CollisionHandler::handleCollisions()
{
	List<Paddle>::Iterator pIter;
	List<Wall>::Iterator wIter;
	List<Ball>::Iterator bIter;
	List<Tile>::Iterator tIter;

	for(pIter = paddles.getIterator(); pIter.hasNext();)
	{
		Paddle * p = pIter.next();
		
		for(wIter = walls.getIterator(); wIter.hasNext();)
		{
			Wall * w = wIter.next();
			if (p -> intersects(*w))
				p -> collide(*w);
		}
	}

	for (bIter = balls.getIterator(); bIter.hasNext();)
	{
		Ball * b = bIter.next();
		
		for (pIter = paddles.getIterator(); pIter.hasNext();)
		{
			Paddle * p = pIter.next();
			if (b -> intersects(*p))
				b -> collide(*p);
		}
		for (wIter = walls.getIterator(); wIter.hasNext();)
		{
			Wall * w = wIter.next();
			if (b -> intersects(*w))
				b -> collide(*w);
		}
		for (tIter = tiles.getIterator(); tIter.hasNext();)
		{
			Tile * t = tIter.next();
			if (b -> intersects(*t))
				b -> collide(*t);
		}
	}
}
