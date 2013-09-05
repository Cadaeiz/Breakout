#include "Paddle.hpp"

Paddle::Paddle(sf::Vector2f pos, sf::Texture & texture, sf::IntRect * rect = 0)
{
	xpos = pos.x;

	sprite.setTexture(texture);
	if (rect)
		sprite.setTextureRect(*rect);
	sprite.setPosition(pos);

	collisionBox = sf::FloatRect(sprite.getGlobalBounds());
}

void Paddle::collide(Collidable & c)
{

}

void Paddle::move(float dx)
{
	
}