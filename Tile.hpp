#ifndef TILE_H_
#define TILE_H_

#include "Collidable.hpp"
#include "TileState.hpp"

class Tile : public Collidable
{
	const static int ALIVE = 0, DYING = 1, DEAD = 2;

	friend class State<Tile>;
private:
	Tile();
	TileState * currentState;
	sf::Sprite sprite;
	int durability;

public:
	static TileState * getState(int type);
	Tile(int dur, sf::Vector2f pos, sf::Texture & texture, sf::IntRect * rect = 0);
	void update() { currentState -> update(*this); }
	void draw(sf::RenderWindow & window) { currentState -> draw(*this, window); }
	void collide(Collidable & c) { currentState -> collide(*this, window); }
};

#endif
