#include "WallFactory.hpp"

WallFactory::WallFactory()
{
	texture.setRepeated(true);
}

WallFactory::~WallFactory()
{
	reset();
}

void WallFactory::loadTexture(const std::string & filename, const sf::IntRect & area = sf::IntRect())
{
	texture.loadFromFile(filename,area);
}

Wall * WallFactory::generate(sf::Vector2f & pos, int length, bool horizontal = true)
{
	Wall * w = new Wall(pos,texture,length,horizontal);
	active.addItem(w);
	return w;
}

void WallFactory::reset()
{
	Wall * w;
	List<Wall>::Iterator iter = active.getIterator();
	while (iter.hasNext())
	{
		w = iter.next();
		active.removeItem(w);
		delete w;
	}
}

void WallFactory::draw(sf::RenderWindow & window)
{
	List<Wall>::Iterator iter = active.getIterator();

	while (iter.hasNext())
		iter.next() -> draw(window);
}