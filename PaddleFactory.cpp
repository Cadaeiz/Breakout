#include "PaddleFactory.hpp"

PaddleFactory::~PaddleFactory()
{
	/* delete all active objects */
	reset();
}

void PaddleFactory::loadTexture(const sf::Image & image, const sf::IntRect & area = sf::IntRect())
{
	texture.loadFromImage(image,area);
}

Paddle * PaddleFactory::generate(sf::Vector2f pos)
{
	Paddle * p = new Paddle(pos,texture);
	active.addItem(p);
	return p;
}

void PaddleFactory::reset()
{
	Paddle * p;
	List<Paddle>::Iterator iter = active.getIterator();
	while (iter.hasNext())
	{
		p = iter.next();
		active.removeItem(p);
		delete p;
	}
}

void PaddleFactory::update()
{
	List<Paddle>::Iterator iter = active.getIterator();
	while (iter.hasNext())
		iter.next() -> update();
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
