#ifndef GAME_H_
#define GAME_H_

#include <SFML/Graphics.hpp>

#define NUMSTATES 1

class Game
{
	friend class GameState;
	GameState * states[NUMSTATES];
	int currentState;

public:
	const static int ScreenWidth = 800, ScreenHeight = 600;
	void init();
	void cleanup();

	void changeState(int state);

	void handleEvent(sf::Event e);
	void run(float time);
	void draw(sf::RenderWindow & window);

};

#endif
