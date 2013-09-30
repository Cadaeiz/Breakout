#ifndef WALLFACT_H_
#define WALLFACT_H_

#include <SFML/Graphics.hpp>
#include "List.hpp"
#include "Wall.hpp"

class WallFactory
{
private:
	sf::Texture texture;
	List<Wall> active;
public:
	WallFactory();
	~WallFactory();
	List<Wall> & getList() { return active; }
	void loadTexture(const sf::Image & image, const sf::IntRect & area);
	Wall * generate(sf::Vector2f & pos, int length, bool horizontal);
	void reset();
	void draw(sf::RenderWindow & window);
};

#endif
