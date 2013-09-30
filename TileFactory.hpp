#ifndef TILEFACT_H_
#define TILEFACT_H_

#include <SFML/Graphics.hpp>
#include "List.hpp"
#include "Tile.hpp"


class TileFactory
{
private:
	sf::Texture texture;
	List<Tile> active;
public:
	~TileFactory();
	List<Tile> & getList() { return active; }
	void loadTexture(const sf::Image & image, const sf::IntRect & area = sf::IntRect());
	Tile * generate(int dur, sf::Vector2f pos);
	void reset();
	void filterDead();
	void update();
	void draw(sf::RenderWindow & window);
	void handleEvent(sf::Event event);

};

#endif
