#ifndef PADDLEFACT_H_
#define PADDLEFACT_H_

#include <SFML/Graphics.hpp>
#include "List.hpp"
#include "Paddle.hpp"

class PaddleFactory
{
private:
	sf::Texture texture;
	List<Paddle> active;
public:
	~PaddleFactory();
	List<Paddle> & getList() { return active; }
	void loadTexture(const sf::Image & image, const sf::IntRect & area = sf::IntRect());
	Paddle * generate(sf::Vector2f pos);
	void reset();
	void update();
	void draw(sf::RenderWindow & window);
	void handleEvent(sf::Event event);
};

#endif
