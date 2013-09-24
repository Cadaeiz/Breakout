#ifndef TILEFACT_H_
#define TILEFACT_H_

#include <SFML/Graphics.hpp>
#include "Tile.hpp"
#include "List.hpp"


class TileFactory
{
private:
	sf::Texture texture;
	List<Tile> active;
public:
	~TileFactory();
	List<Tile> & getList() { return active; }
	void loadTexture(const std::string & filename, const sf::IntRect & area = sf::IntRect());
	Tile * generate(int dur, sf::Vector2f pos);
	void reset();
	void update();
	void draw(sf::RenderWindow & window);
	void handleEvent(sf::Event event);

};

#endif
