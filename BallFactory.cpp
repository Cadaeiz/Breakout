#include "BallFactory.hpp"

BallFactory::~BallFactory()
{
	/* delete all active objects */
	reset();
}

void BallFactory::loadTexture(const sf::Image & image, const sf::IntRect & area = sf::IntRect())
{
	texture.loadFromImage(image,area);
}

Ball * BallFactory::generate(sf::Vector2f pos)
{
	Ball * b = new Ball(pos,texture);
	active.addItem(b);
	return b;
}

void BallFactory::reset()
{
	Ball * b;
	List<Ball>::Iterator iter = active.getIterator();
	while (iter.hasNext())
	{
		b = iter.next();
		active.removeItem(b);
		delete b;
	}
}

/* delete all balls in a dead state */
void BallFactory::filterDead()
{
	Ball * b;
	List<Ball>::Iterator iter = active.getIterator();
	while (iter.hasNext())
	{
		b = iter.next();
		if (p -> isDead())
		{
			active.removeItem(b);
			delete b;
		}
	}
}

void BallFactory::update()
{
	List<Ball>::Iterator iter = active.getIterator();
	while (iter.hasNext())
		iter.next() -> update();
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
