#include "TileFactory.hpp"


TileFactory::~TileFactory()
{
	reset();
}

void TileFactory::loadTexture(const std::string & filename, const sf::IntRect & area = sf::IntRect())
{
	texture.loadFromFile(filename,area);
}

Tile * TileFactory::generate(int dur, sf::Vector2f pos)
{
	Tile * p = new Tile(dur,pos,texture);
	active.addItem(p);
	return p;
}

void TileFactory::reset()
{
	Tile * p;
	List<Tile>::Iterator iter = active.getIterator();
	while (iter.hasNext())
	{
		p = iter.next();
		active.removeItem(p);
		delete p;
	}
}

void TileFactory::filterDead()
{
	Tile * p;
	List<Tile>::Iterator iter = active.getIterator();
	while (iter.hasNext())
	{
		p = iter.next();
		if (p -> isDead())
		{
			active.removeItem(p);
			delete p;
		}
	}
}

void TileFactory::update()
{
	List<Tile>::Iterator iter = active.getIterator();
	while (iter.hasNext())
		iter.next() -> update();
}

void TileFactory::draw(sf::RenderWindow & window)
{
	List<Tile>::Iterator iter = active.getIterator();
	while (iter.hasNext())
		iter.next() -> draw(window);
}

void TileFactory::handleEvent(sf::Event event)
{
	List<Tile>::Iterator iter = active.getIterator();
	while (iter.hasNext())
		iter.next() -> handleEvent(event);
}
