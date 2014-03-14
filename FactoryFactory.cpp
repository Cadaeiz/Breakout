#include "FactoryFactory.hpp"
#include <fstream>

FactoryFactory::FactoryFactory()
{
	/* generate walls and paddle, since these never change */
	wallFactory.generate(sf::Vector2f(400,100),800,true);
	wallFactory.generate(sf::Vector2f(20,360),480,false);
	wallFactory.generate(sf::Vector2f(780,360),480,false);

	paddleFactory.generate(sf::Vector2f(400,535));
}

void FactoryFactory::loadSpriteSheet(string filename)
{
	stageType = filename;
	sf::Image image;
	image.loadFromFile(filename);

	wallFactory.loadTexture(image);
	tileFactory.loadTexture(image);
	ballFactory.loadTexture(image);
	paddleFactory.loadTexture(image);
}

void FactoryFactory::loadLevel(string filename)
{
	reset();

	std::ifstream file;
	file.open(filename);
	std::string line;
	getline(file,line);
	while (getline(file,line))
		tileFactory.generate(line);
	file.close();
}

string FactoryFactory::saveLevel()
{
	string str = stageType + '\n';
	List<Tile>::Iterator iter = tileFactory.getList().getIterator();

	while (iter.hasNext())
		str.append(iter.next() -> toString());

	return str;
}

void FactoryFactory::reset()
{
	tileFactory.reset();
	ballFactory.reset();
}

void FactoryFactory::exit()
{
	wallFactory.reset();
	tileFactory.reset();
	ballFactory.reset();
	paddleFactory.reset();
}

unsigned int FactoryFactory::filterDead()
{
	ballFactory.filterDead();
	return tileFactory.filterDead();
}

void FactoryFactory::update(float time)
{
	tileFactory.update(time);
	paddleFactory.update(time);
	ballFactory.update(time);
}

void FactoryFactory::draw(sf::RenderWindow & window)
{
	wallFactory.draw(window);
	tileFactory.draw(window);
	paddleFactory.draw(window);
	ballFactory.draw(window);
}

void FactoryFactory::handleEvent(sf::Event e)
{
	tileFactory.handleEvent(e);
	paddleFactory.handleEvent(e);
	ballFactory.handleEvent(e);
}