#include "BallFactory.hpp"

BallFactory::~BallFactory()
{
	/* delete all active objects */
	reset();
}

void BallFactory::loadTexture(const sf::Image & spritesheet)
{
	texture.loadFromImage(spritesheet,sf::IntRect(120,0,40,40));
}

Ball * BallFactory::generate(float speed, Paddle & paddle)
{
	Ball * b = new Ball(texture,speed,paddle);
	active.addItem(b);
	return b;
}

void BallFactory::reset()
{
	List<Ball>::Iterator iter = active.getIterator();
	while (iter.hasNext())
	{
		delete iter.next();
		iter.removeLastItem();
	}
}

/* delete all balls in a dead state */
void BallFactory::filterDead()
{
	List<Ball>::Iterator iter = active.getIterator();
	while (iter.hasNext())
		if (iter.next() -> isDead())
			/* delete dead balls and remove them from the list */
			delete iter.removeLastItem();
}

void BallFactory::update(float time)
{
	List<Ball>::Iterator iter = active.getIterator();
	while (iter.hasNext())
		iter.next() -> update(time);
}

void BallFactory::draw(sf::RenderWindow & window)
{
	List<Ball>::Iterator iter = active.getIterator();
	while (iter.hasNext())
		iter.next() -> draw(window);
}

void BallFactory::handleEvent(sf::Event event)
{
	List<Ball>::Iterator iter = active.getIterator();
	while (iter.hasNext())
		iter.next() -> handleEvent(event);
}