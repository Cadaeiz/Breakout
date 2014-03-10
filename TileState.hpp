#ifndef TILESTATE_H_
#define TILESTATE_H_

#include "Ball.hpp"

class Tile;

class TileState
{
public:	
	virtual void init(Tile & t) = 0;
	virtual void cleanup(Tile & t) = 0;
	virtual void update(Tile & t, float time) = 0;
	void handleEvent(Tile & t, sf::Event event) { }
	void draw(Tile & t, sf::RenderWindow & window);
	virtual void collide(Tile & t, Collidable * c) = 0;
};

class TileActiveState : public TileState
{
public:
	void init(Tile & t) { }
	void cleanup(Tile & t) { }
	void update(Tile & t, float time) { }
	void collide(Tile & t, Collidable * c);
	void collide(Tile & t, Ball * b);
};

class TileDyingState : public TileState
{
public:
	void init(Tile & t);
	void cleanup(Tile & t) { }
	void update(Tile & t, float time);
	void collide(Tile & t, Collidable * c) { }
};

class TileDeadState : public TileState
{
public:
	void init(Tile & t) { }
	void cleanup(Tile & t) { }
	void update(Tile & t, float time) { }
	void collide(Tile & t, Collidable * c) { }
};

#endif
