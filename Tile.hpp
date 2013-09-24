#ifndef TILE_H_
#define TILE_H_

#include "Collidable.hpp"
#include "TileState.hpp"

class Tile : public Collidable
{
	friend class TileActiveState;
	friend class TileDyingState;
	friend class TileDeadState;
	const static int ACTIVE = 0, DYING = 1, DEAD = 2;
private:
	static struct
	{
		TileActiveState active;
		TileDyingState dying;
		TileDeadState dead;
	} StateMachine;

	Tile();
	TileState * currentState;
	sf::Sprite sprite;
	int durability, timer;
	void changeState(int state);
public:
	Tile(int dur, sf::Vector2f pos, sf::Texture & texture, sf::IntRect & rect);
	void update() { currentState -> update(*this); }
	void handleEvent(sf::Event event) { currentState -> handleEvent(*this, event); }
	void draw(sf::RenderWindow & window) { currentState -> draw(*this, window); }
	void collide(Collidable & c) { currentState -> collide(*this, c); }
};

#endif
