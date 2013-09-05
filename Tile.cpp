#include "Tile.hpp"

TileState * Tile::getState(int type)
{
	switch(type)
	{
	case ALIVE:
		static AliveState s1;
		return &s1;
	case DYING:
		static DyingState s2;
		return &s2;
	case DEAD:
		static DeadState s3;
		return &s3;
	default:
		return 0;
	}
}

Tile::Tile(int dur, sf::Vector2f pos, sf::Texture & texture, sf::IntRect * rect = 0)
{	
	durability = dur;

	sprite.setTexture(texture);
	if (rect)
		sprite.setTextureRect(*rect);
	sprite.setPosition(pos);

	collisionBox = sf::FloatRect(sprite.getGlobalBounds());
}

