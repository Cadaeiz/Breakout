#include "CollisionBox.hpp"

bool CBRect::intersects(CBRect * cbr)
{
	sf::Vector2f diff = center - cbr -> center;
	sf::Vector2f combinedSize = (size + cbr -> size);
	return (2*abs(diff.x) < combinedSize.x && 2*abs(diff.y) < combinedSize.y);
}

bool CBRect::intersects(CBCircle * cbc)
{
	sf::Vector2f diff = center - cbc -> getCenter();
	float dx = abs(diff.x) - size.x / 2, 
		  dy = abs(diff.y) - size.y / 2;
	float radius = cbc -> getRadius();
	return ((dx < 0 && dy < radius) || (dy < 0 && dx < radius) || (dx*dx + dy*dy < radius*radius));
}

bool CBRect::intersects(CollisionBox * cb)
{
	if (cb -> getType() == 0)
		return intersects( (CBRect *) cb);
	else if (cb -> getType() == 1)
		return intersects( (CBCircle *) cb);
	else 
		return cb -> intersects(this);
}

bool CBCircle::intersects(CBCircle * cbc)
{
	sf::Vector2f diff = center -  cbc -> center;
	float radSum = radius + cbc -> radius;
	return (diff.x*diff.x + diff.y*diff.y < radSum * radSum);
}

bool CBCircle::intersects(CollisionBox * cb)
{
	if (cb -> getType() == 1)
		return intersects( (CBCircle *) cb);
	else
		return cb -> intersects(this);
}

CBArray::~CBArray()
{
	/* delete all collision boxes in list */
	List<CollisionBox>::Iterator iter = boxes.getIterator();
	while (iter.hasNext())
	{
		delete iter.next();
		iter.removeLastItem();
	}
}

bool CBArray::intersects(CollisionBox * box)
{
	/* check if any boxes in the list intersect the given box */
	List<CollisionBox>::Iterator iter = boxes.getIterator();
	while (iter.hasNext())
		if (iter.next() -> intersects(box))
			return true;
	
	return false;
}

/* to move an array, move all boxes inside the array */
void CBArray::move(sf::Vector2f diff)
{
	center += diff;
	List<CollisionBox>::Iterator iter = boxes.getIterator();
	while (iter.hasNext())
		iter.next() -> move(diff);
}
