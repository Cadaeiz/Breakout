#include "Wall.hpp"

Wall::Wall(sf::Vector2f pos, sf::Texture & texture, sf::IntRect * rect = 0)
{
	sprite.setTexture(texture);
	if (rect)
		sprite.setTextureRect(*rect);
	sprite.setPosition(pos);

	collisionBox = sf::FloatRect(sprite.getGlobalBounds());
}
