#ifndef BALL_H_
#define BALL_H_

#define BALLRAD 20.0

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Collidable.hpp"
#include "BallState.hpp"
#include "Paddle.hpp"

class Ball : public Collidable
{
	/* allow paddle to move the ball when attached in launch state */
	friend class Paddle;

	friend class BallState;
	friend class BallLaunchState;
	friend class BallMovingState;
	friend class BallDyingState;
	friend class BallDeadState;
	const static int LAUNCH = 0, MOVING = 1, DYING = 2, DEAD = 3;

private:
	static sf::SoundBuffer bounceBuffer, deadBuffer, launchBallBuffer, tileBounceBuffer;
	sf::Sound bounceSound, deadSound, launchBallSound, tileBounceSound;

	static struct Machine
	{
		BallLaunchState launch;
		BallMovingState moving;
		BallDyingState dying;
		BallDeadState dead;
	} StateMachine;
	BallState * currentState;

	Paddle * primaryPaddle;
	sf::Sprite sprite;
	sf::Vector2f vel;
	float angle, dtheta, speed;

	void changeState(int state);
	void setPosition(sf::Vector2f p);
	void move(sf::Vector2f dp);
public:
	static void loadSounds();
	Ball(sf::Texture & texture, float speed, Paddle & paddle);
	~Ball() { primaryPaddle -> detach(this); }
	void update(float time) { currentState -> update(*this, time); }
	void handleEvent(sf::Event event) { currentState -> handleEvent(*this, event); }
	void draw(sf::RenderWindow & window) { currentState -> draw(*this, window); }
	void collide(Collidable * c) { currentState -> collide(*this, c); }
	bool isDead() { return (currentState == &StateMachine.dead); }
	bool isPlaying() { return tileBounceSound.getStatus() == sf::Sound::Status::Playing; }
};

#endif
