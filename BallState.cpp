#include "BallState.hpp"
#include "Ball.hpp"
#include "Game.hpp"
#include <math.h>

void BallLaunchState::init(Ball & b)
{
	b.primaryPaddle -> attach(&b);
	/* set the initial direction as vertical, and the rate of change of its angle */
	b.angle = -90;
	b.dtheta = 2;
}

void BallLaunchState::cleanup(Ball & b)
{
	b.primaryPaddle -> detach(&b);
}

void BallLaunchState::update(Ball & b)
{
	/* rotate the current angle of the ball */
	b.angle += b.dtheta;
	/* if horizontal, switch directions */
	if (b.angle >= 0 || b.angle <= -180)
	{
		b.dtheta *= -1;
		b.angle += b.dtheta;
	}
}

void BallLaunchState::draw(Ball & b, sf::RenderWindow & window)
{
	window.draw(b.sprite);
	/* draw line indicating current trajectory */
	sf::Vertex line[] = 
	{
		sf::Vertex(b.getCenter()),
		sf::Vertex(b.getCenter() + sf::Vector2f(5*sin(b.angle), 5*cos(b.angle)))
	};
	window.draw(line,2,sf::Lines);
}

void BallLaunchState::handleEvent(Ball & b, sf::Event event)
{
	if (event.type == sf::Event::KeyPressed &&
		event.key.code == sf::Keyboard::Space)
		b.changeState(Ball::MOVING);
}

void BallMovingState::init(Ball & b)
{
	/* set velocity from final trajectory from launch state */
	b.vel = sf::Vector2f(b.speed * sin(b.angle), b.speed * cos(b.angle));
}

void BallMovingState::update(Ball & b)
{
	b.move(b.vel);
	sf::Vector2f center = b.getCenter();
	/* if the ball has moved outside of the boundaries of the screen, go to dying state */
	if (center.x < 0 || center.x > Game::ScreenWidth ||
		center.y < 0 || center.y > Game::ScreenHeight)
	{
		b.changeState(Ball::DYING);
	}
}

/* on collision, negate the velocity on the axis the collision occured, then
 * displace the ball to be outside of the collidable object */
void BallMovingState::collide(Ball & b, Collidable & c)
{
	sf::FloatRect rect = c.getCollisionBox();
	
	sf::Vector2f distance = b.getCenter() - c.getCenter();

	/* if the collision is vertical */
	if (distance.x == 0 || abs(distance.y / distance.x) > abs(rect.height / rect.width))
	{
		b.vel.y *= -1;

		/* collision occurs on the bottom side of the collidable (top of ball) */
		if (distance.y > 0)
			b.move(sf::Vector2f(0,(rect.top + rect.height) - b.collisionBox.top));
		/* collision occurs on the top of the collidable (bottom of ball) */
		else
			b.move(sf::Vector2f(0,rect.top - (b.collisionBox.top + b.collisionBox.height)));
	}
	/* if the collision is horizontal */
	else
	{
		b.vel.x *= -1;

		/* collision occurs on the right of the collidable (left of ball) */
		if (distance.x > 0)
			b.move(sf::Vector2f((rect.left + rect.width) - b.collisionBox.left,0));
		/* collision occurs on the left of the collidable (right of ball) */
		else
			b.move(sf::Vector2f(rect.left - (b.collisionBox.left + b.collisionBox.width),0));
	}
}

void BallDyingState::init(Ball & b)
{
	/* reset collisionBox to prevent further collisions */
	b.collisionBox = sf::FloatRect(0,0,0,0);
}

void BallDyingState::update(Ball & b)
{
	/* decrement the opacity of the sprite until it is invisible */
	sf::Color color = b.sprite.getColor();
	if (color.a < 5)
		b.changeState(Ball::DEAD);

	color.a -= 5;
	b.sprite.setColor(color);
}
