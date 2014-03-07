#ifndef BALLFACTORY_H_
#define BALLFACTORY_H_

#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include "List.hpp"

class BallFactory
{
	private:
	sf::Texture texture;
	List<Ball> active;
public:
	~BallFactory();
	List<Ball> & getList() { return active; }
	void loadTexture(const sf::Image & spritesheet);
	Ball * generate(float speed, Paddle & paddle);
	void reset();
	void filterDead();
	void update(float time);
	void draw(sf::RenderWindow & window);
	void handleEvent(sf::Event event);
	bool isEmpty() { return !active.getIterator().hasNext(); }
};

#endif
