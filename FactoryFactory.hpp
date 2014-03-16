#ifndef FACTORYFACTORY_H_
#define FACTORYFACTORY_H_

#include "BallFactory.hpp"
#include "WallFactory.hpp"
#include "TileFactory.hpp"
#include "PaddleFactory.hpp"
#include <string>

using std::string;

class FactoryFactory
{
public:
	BallFactory ballFactory;
	WallFactory wallFactory;
	TileFactory tileFactory;
	PaddleFactory paddleFactory;
	string stageType;

	FactoryFactory();
	void loadSpriteSheet(string filename);
	void loadLevel(string filename);
	string saveLevel();
	void reset();
	void exit();
	unsigned int filterDead();
	void update(float time);
	void draw(sf::RenderWindow & window);
	void handleEvent(sf::Event e);
};

#endif
