#ifndef TILESTATE_H_
#define TILESTATE_H_

#include "Tile.hpp"
#include "State.hpp"

class TileState : State<Tile>
{
public:
	virtual void collide(Tile & t, Collidable & c) = 0;
};

class AliveState : public TileState
{
private:
	AliveState() { }
protected:
	void init(Tile & t) { }
	void cleanup(Tile & t) { }
public:
	void update(Tile & t) { }
	void draw(Tile & t, sf::RenderWindow & window) { window.draw(t.sprite); }
	void collide(Tile & t, Collidable & c);
	friend class Tile;
};

class DyingState : public TileState
{
private:
	DyingState() { }
protected:
	void init(Tile & t);
	void cleanup(Tile & t);
public:
	void update(Tile & t);
	void draw(Tile & t, sf::RenderWindow & window) { window.draw(t.sprite); }
	void collide(Tile & t, Collidable & c) { }
	friend class Tile;
};

class DeadState : public TileState
{
private:
	DeadState() { }
protected:
	void init(Tile & t);
	void cleanup(Tile & t) { }
public:
	void update(Tile & t);
	void draw(Tile & t, sf::RenderWindow & window) { }
	void collide(Tile & t, Collidable & c) { }
	friend class Tile;
};

#endif