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
	void loadTexture(const sf::Image & spritesheet);
	Paddle * generate(sf::Vector2f pos);
	void reset();
	void update(float time);
	void draw(sf::RenderWindow & window);
	void handleEvent(sf::Event e);
	Paddle * getFirst();
};

#endif
