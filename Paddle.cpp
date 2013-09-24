#include "Paddle.hpp"
#include "Game.hpp"

Paddle::Paddle(sf::Vector2f pos, sf::Texture & texture)
{
	sprite.setTexture(texture);
	sprite.setPosition(pos);

	collisionBox = sf::FloatRect(sprite.getGlobalBounds());
	/* set origin of sprite as the center */
	size = sf::Vector2f(collisionBox.width, collisionBox.height);
	sprite.setOrigin(size.x / 2, size.y / 2);
}

void Paddle::update()
{
	float x = sprite.getPosition().x;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		x -= PADDLESTEP;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		x += PADDLESTEP;

	setXPos(x);
}

void Paddle::handleEvent(sf::Event event)
{
	if (event.type == sf::Event::MouseMoved)
		setXPos(event.mouseMove.x);
}

/* if paddle collides with a wall,
 * displace the paddle outside of the wall */
void Paddle::collide(Wall & c)
{
	sf::FloatRect box2 = c.getCollisionBox();
	/* if paddle is on the left side */
	if (c.getCenter().x > getCenter().x)
		move(box2.left - (collisionBox.left+collisionBox.width));
	/* if paddle is on the right side */
	else
		move((box2.left+box2.width) - collisionBox.left);
}

void Paddle::setXPos(float x)
{
	/* keep paddle within the boundaries of the screen */
	if (x < size.x / 2)
		x = size.x / 2;
	else if (x > Game::ScreenWidth - size.x / 2)
		x = Game::ScreenWidth - size.x / 2;

	sprite.setPosition(x, sprite.getPosition().y);
	collisionBox.left = x - size.x / 2;
}

void Paddle::move(float dx)
{
	sprite.move(dx,0);
	collisionBox.left += dx;
}
 