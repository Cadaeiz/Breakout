#include "Tile.hpp"


Tile::Tile(int dur, sf::Vector2f pos, sf::Texture & texture, sf::IntRect & rect) : Collidable(CBRect(pos.x,pos.y,TILEW, TILEH), 3)
{	
	durability = dur;

	sprite.setTexture(texture);
	sprite.setTextureRect(rect);
	sprite.setPosition(pos);

	/* set position relative to center of sprite */
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
