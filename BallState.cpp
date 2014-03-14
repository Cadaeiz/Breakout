#include "BallState.hpp"
#include "Ball.hpp"
#include "Game.hpp"
#include <math.h>

#define PI 3.14169265358


void BallState::draw(Ball & b, sf::RenderWindow & window) 
{ 
	window.draw(b.sprite); 
}

void BallLaunchState::init(Ball & b)
{
	b.primaryPaddle -> attach(&b);
	/* set the initial direction as vertical, and the rate of change of its angle */
	b.angle = -PI / 2;
	b.dtheta = 2*PI;
}

void BallLaunchState::cleanup(Ball & b)
{
	b.primaryPaddle -> detach(&b);
	b.launchBallSound.stop();
	b.launchBallSound.play();
}

void BallLaunchState::update(Ball & b, float time)
{
	/* rotate the current angle of the ball */
	b.angle += b.dtheta * time;
	/* if horizontal, switch directions */
	if (b.angle >= -PI*.05 || b.angle <= -.95*PI)
	{
		b.dtheta *= -1;
		b.angle += b.dtheta * time;
	}
}

void BallLaunchState::draw(Ball & b, sf::RenderWindow & window)
{
	window.draw(b.sprite);
	/* draw line indicating current trajectory */
	sf::Vertex line[] = 
	{
		sf::Vertex(b.getCenter()),
		sf::Vertex(b.getCenter() + sf::Vector2f(25*cos(b.angle), 25*sin(b.angle)))
	};
	window.draw(line,2,sf::Lines);
}

void BallLaunchState::handleEvent(Ball & b, sf::Event event)
{
	if (event.type == sf::Event::KeyPressed &&
		event.key.code == sf::Keyboard::Space ||
		event.type == sf::Event::MouseButtonPressed)
		b.changeState(Ball::MOVING);
}

void BallMovingState::init(Ball & b)
{
	/* set velocity from final trajectory from launch state */
	b.vel = sf::Vector2f(b.speed * cos(b.angle), b.speed * sin(b.angle));
}

void BallMovingState::update(Ball & b, float time)
{
	b.move(sf::Vector2f(b.vel.x * time, b.vel.y * time));
	sf::Vector2f center = b.getCenter();
	/* if the ball has moved outside of the boundaries of the screen, go to dying state */
	if (center.x < 0 || center.x > Game::ScreenWidth ||
		center.y < 0 || center.y > Game::ScreenHeight)
	{
		b.changeState(Ball::DYING);
	}
}

void BallMovingState::collide(Ball & b, Paddle * p)
{
	/* if ball is above the paddle */
	if (b.getCenter().y < p->getCenter().y)
	{
		/* assume the collision is vertical, and displace the ball outside of the paddle */
		b.move(sf::Vector2f(0,(p->getCenter().y - p->getSize().y / 2)-(b.getCenter().y + b.getSize().y / 2)));

		/* change the trajectory of the ball */
		sf::Vector2f traj = b.getCenter() - p->getCenter();
		float norm = sqrt(traj.x*traj.x + traj.y*traj.y);
		traj.x *= (b.speed / norm);
		traj.y *= (b.speed / norm);
		b.vel = traj;
	}
}

/* on collision, negate the velocity on the axis the collision occured, then
 * displace the ball to be outside of the collidable object */
void BallMovingState::collide(Ball & b, Collidable * c)
{
	if (c -> getType() == 3)
	{
		b.tileBounceSound.stop();
		b.tileBounceSound.play();
	}
	else
	{
		b.bounceSound.stop();
		b.bounceSound.play();
	}

	if (c -> getType() == 1)
	{
		collide(b,(Paddle *) c);
		return;
	}

	sf::Vector2f size = c -> getSize();
	
	sf::Vector2f distance = b.getCenter() - c -> getCenter();

	/* if the collision is vertical */
	if (distance.x == 0 || size.x != 0 && (abs(distance.y / distance.x) > abs(size.y / size.x)))
	{
		b.vel.y *= -1;

		/* collision occurs on the bottom side of the collidable (top of ball) */
		if (distance.y > 0)
			b.move(sf::Vector2f(0,(c->getCenter().y + size.y / 2) - (b.getCenter().y - b.getSize().y / 2)));
		/* collision occurs on the top of the collidable (bottom of ball) */
		else
			b.move(sf::Vector2f(0,(c->getCenter().y - size.y / 2) - (b.getCenter().y + b.getSize().y / 2)));
	}
	/* if the collision is horizontal */
	else
	{
		b.vel.x *= -1;

		/* collision occurs on the right of the collidable (left of ball) */
		if (distance.x > 0)
			b.move(sf::Vector2f((c->getCenter().x + size.x / 2)-(b.getCenter().x - b.getSize().x / 2),0));
		/* collision occurs on the left of the collidable (right of ball) */
		else
			b.move(sf::Vector2f((c->getCenter().x - size.x / 2)-(b.getCenter().x + b.getSize().x / 2),0));
	}
}

void BallDyingState::init(Ball & b)
{
	/* reset collisionBox to prevent further collisions */
	((CBRect *) b.box) -> setSize(sf::Vector2f(0,0));
	b.deadSound.play();
}

void BallDyingState::update(Ball & b, float time)
{
	/* decrement the opacity of the sprite until it is invisible */
	sf::Color color = b.sprite.getColor();
	if (color.a == 0 && b.deadSound.getStatus() == sf::Sound::Status::Stopped)
		b.changeState(Ball::DEAD);

	if (color.a > 0)
		color.a--;
	b.sprite.setColor(color);
}
