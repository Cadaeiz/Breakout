#include "Wall.hpp"

Wall::Wall(sf::Vector2f pos, sf::Texture & texture, int length, bool horizontal = true)
{
	sf::IntRect rect = sf::IntRect(0,0,length,WALLWIDTH);
	sprite.setTexture(texture);
	sprite.setTextureRect(rect);
	if (!horizontal)
	{
		pos.x += WALLWIDTH;
		sprite.rotate(-90);
	}
	sprite.setPosition(pos);

	collisionBox = sf::FloatRect(sprite.getGlobalBounds());
}
