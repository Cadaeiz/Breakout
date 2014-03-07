#include "PaddleFactory.hpp"

PaddleFactory::~PaddleFactory()
{
	/* delete all active objects */
	reset();
}

void PaddleFactory::loadTexture(const sf::Image & spritesheet)
{
	texture.loadFromImage(spritesheet, sf::IntRect(0,120,160,30));
}

Paddle * PaddleFactory::generate(sf::Vector2f pos)
{
	Paddle * p = new Paddle(pos,texture);
	active.addItem(p);
	return p;
}

void PaddleFactory::reset()
{
	List<Paddle>::Iterator iter = active.getIterator();
	while (iter.hasNext())
	{
		delete iter.next();
		iter.removeLastItem();
	}
}

void PaddleFactory::update(float time)
{
	List<Paddle>::Iterator iter = active.getIterator();
	while (iter.hasNext())
		iter.next() -> update(time);
}

void PaddleFactory::draw(sf::RenderWindow & window)
{
	List<Paddle>::Iterator iter = active.getIterator();
	while (iter.hasNext())
		iter.next() -> draw(window);
}

void PaddleFactory::handleEvent(sf::Event event)
{
	List<Paddle>::Iterator iter = active.getIterator();
	while (iter.hasNext())
		iter.next() -> handleEvent(event);
}

Paddle * PaddleFactory::getFirst()
{
	List<Paddle>::Iterator iter = active.getIterator();
	if (iter.hasNext())
		return iter.next();
	else
		return 0;
}