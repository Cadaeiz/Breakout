#include "Wall.hpp"

Wall::Wall(sf::Vector2f pos, sf::Texture & texture, float length, bool horizontal = true)
{
	/* set length of texture box to given value (tiled texture means any length works */
	sf::IntRect rect = sf::IntRect(0,0,length,WALLWIDTH);
	sprite.setTexture(texture);
	sprite.setTextureRect(rect);
	
	/* set position relative to center of sprite */
	sprite.setOrigin(length / 2, WALLWIDTH / 2);
	sprite.setPosition(pos);
	if (!horizontal)
		sprite.rotate(90);

	collisionBox = sf::FloatRect(sprite.getGlobalBounds());
}
