#ifndef TILE_H_
#define TILE_H_

#define TILEW 80
#define TILEH 40

#include "Collidable.hpp"
#include "TileState.hpp"
#include <string>
#include <sstream>

using std::string;

class Tile : public Collidable
{
	friend class TileState;
	friend class TileActiveState;
	friend class TileDyingState;
	friend class TileDeadState;
	const static int ACTIVE = 0, DYING = 1, DEAD = 2;
private:
	static struct Machine
	{
		TileActiveState active;
		TileDyingState dying;
		TileDeadState dead;
	} StateMachine;

	Tile();
	TileState * currentState;
	sf::Sprite sprite;
	int durability, type;
	void changeState(int state);
public:
	Tile(int dur, sf::Vector2f pos, sf::Texture & texture, sf::IntRect & rect, int type = 0);
	Tile(int dur, sf::Vector2f pos, int type = 0);
	void setTexture(sf::Texture & texture) { sprite.setTexture(texture); sprite.setTextureRect(sf::IntRect((type/2)*80,(type%2)*40,80,40)); }
	Tile(Tile & tile);
	void update(float time) { currentState -> update(*this, time); }
	void handleEvent(sf::Event event) { currentState -> handleEvent(*this, event); }
	void draw(sf::RenderWindow & window) { currentState -> draw(*this, window); }
	void collide(Collidable * c) { currentState -> collide(*this, c); }
	bool isDead() { return (currentState == &StateMachine.dead); }
	string toString();
	void changeDur(int delta) { durability += delta; }
	void cycleType();
	void setPosition(float x, float y);
	bool isValid();
	void setColor(sf::Color color) { sprite.setColor(color); }
};

#endif
