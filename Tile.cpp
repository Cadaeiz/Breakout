#include "Tile.hpp"
#include "Singleton.hpp"
#include "CollisionHandler.hpp"

CollisionHandler Singleton<CollisionHandler>::t;

struct Tile::Machine Tile::StateMachine;

Tile::Tile(int dur, sf::Vector2f pos, sf::Texture & texture, sf::IntRect & rect, int type) : Collidable(CBRect(pos.x,pos.y,TILEW, TILEH), 3), type(type)
{	
	durability = dur;

	setTexture(texture);
	sprite.setPosition(pos);

	/* set position relative to center of sprite */
	sprite.setOrigin(TILEW / 2, TILEH / 2);

	currentState = 0;
	changeState(ACTIVE);
}

Tile::Tile(int dur, int type) : Collidable(CBRect(0,0,TILEW, TILEH), 3), type(type)
{
	durability = dur;

	sprite.setOrigin(TILEW / 2, TILEH / 2);
	currentState = 0;
	changeState(DEAD);
}

Tile::Tile(Tile & tile) : Collidable(CBRect(0,0,TILEW, TILEH), 3), type(tile.type)
{
	box -> setPosition(tile.getCenter());

	durability = tile.durability;

	sprite.setTexture(*tile.sprite.getTexture());
	sprite.setTextureRect(tile.sprite.getTextureRect());
	sprite.setPosition(tile.getCenter());

	sprite.setOrigin(TILEW / 2, TILEH / 2);

	currentState = 0;
	changeState(ACTIVE);
}

void Tile::changeState(int state)
{
	if (currentState)
		currentState -> cleanup(*this);
	
	switch(state)
	{
	case ACTIVE:
		currentState = &StateMachine.active;
		break;
	case DYING:
		currentState = &StateMachine.dying;
		break;
	case DEAD:
		currentState = &StateMachine.dead;
		break;
	}

	currentState -> init(*this);
}

string Tile::toString()
{
	std::stringstream ss;
	ss << type << ' ' << durability << ' ';
	ss << getCenter().x << ' ' << getCenter().y << '\n';
	
	return ss.str();
}

void Tile::cycleType()
{
	if (++type >= 4)
		type = 0;

	sprite.setTextureRect(sf::IntRect((type/2)*80,(type%2)*40,80,40));
}

void Tile::setPosition(float x, float y)
{
	sprite.setPosition(x,y);
	box -> setPosition(sf::Vector2f(x,y));
}

/* checks whether the tile collides with any
   other objects at its current position */
bool Tile::isValid()
{
	return !Singleton<CollisionHandler>::getInstance() -> checkCollisions(*this);
}
