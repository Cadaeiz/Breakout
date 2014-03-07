#include "Paddle.hpp"
#include "Wall.hpp"
#include "Game.hpp"
#include "Ball.hpp"

Paddle::Paddle(sf::Vector2f pos, sf::Texture & texture) : Collidable(CBRect(pos.x,pos.y,PADDLEW,PADDLEH), 1)
{
	sprite.setTexture(texture);
	sprite.setPosition(pos);

	/* set origin of sprite as the center */
	sprite.setOrigin(PADDLEW / 2, PADDLEH / 2);

	stuckBall = 0;
}

void Paddle::update(float time)
{
	float x = getCenter().x;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		x -= Game::ScreenWidth * time;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		x += Game::ScreenWidth * time;

	setXPos(x);
}

void Paddle::handleEvent(sf::Event event)
{
	if (event.type == sf::Event::MouseMoved)
		setXPos((float) event.mouseMove.x);
}

/* if paddle collides with a wall,
 * displace the paddle outside of the wall */
void Paddle::collide(Wall & c)
{
	float dx;
	/* if paddle is on the left side */
	if (c.getCenter().x > getCenter().x)
		dx = (c.getCenter().x - WALLWIDTH / 2) - (getCenter().x + PADDLEW / 2);
	/* if paddle is on the right side */
	else
		dx = (c.getCenter().x + WALLWIDTH / 2) - (getCenter().x - PADDLEW / 2);

	move(dx);
}

void Paddle::setXPos(float x)
{
	/* keep paddle within the boundaries of the screen */
	if (x < PADDLEW / 2)
		x = PADDLEW / 2;
	else if (x > Game::ScreenWidth - PADDLEW / 2)
		x = Game::ScreenWidth - PADDLEW / 2;

	move(x - getCenter().x);
}

void Paddle::move(float dx)
{
	sprite.move(dx,0);
	box -> move(sf::Vector2f(dx,0));

	/* if there is a ball attached, move it as well */
	if (stuckBall)
		stuckBall -> move(sf::Vector2f(dx,0));
}
