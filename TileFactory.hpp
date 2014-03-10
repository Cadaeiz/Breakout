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
	void loadTexture(const sf::Image & spritesheet);
	sf::Texture & getTexture() { return texture; }
	Tile * generate(int dur, sf::Vector2f pos, int type);
	Tile * generate(std::string line);
	Tile * generate(Tile & tile);
	void reset();
	unsigned int filterDead();
	void update(float time);
	void draw(sf::RenderWindow & window);
	void handleEvent(sf::Event event);
	bool isEmpty() { return !active.getIterator().hasNext(); }
};

#endif
