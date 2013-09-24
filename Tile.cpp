#include "Tile.hpp"


Tile::Tile(int dur, sf::Vector2f pos, sf::Texture & texture, sf::IntRect & rect)
{	
	durability = dur;

	sprite.setTexture(texture);
	sprite.setTextureRect(rect);
	sprite.setPosition(pos);

	collisionBox = sf::FloatRect(sprite.getGlobalBounds());
	sprite.setOrigin(collisionBox.width / 2, collisionBox.height / 2);

	changeState(ACTIVE);
}

void Tile::changeState(int state)
{
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
