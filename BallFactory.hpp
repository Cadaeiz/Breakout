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
	void loadTexture(const sf::Image & image, const sf::IntRect & area = sf::IntRect());
	Ball * generate(sf::Vector2f pos);
	void reset();
	void filterDead();
	void update();
	void draw(sf::RenderWindow & window);
	void handleEvent(sf::Event event);
};

#endif
