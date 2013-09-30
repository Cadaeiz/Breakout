#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <SFML/Graphics.hpp>

class Game;

class GameState
{

public:
	virtual void handleEvent(Game & game, sf::Event e) = 0;
	virtual void run(Game & game, float time) = 0;
	virtual void draw(Game & game, sf::RenderWindow & window) = 0;

	virtual void init(Game & game) = 0;
	virtual void cleanup(Game & game) = 0;

	void changeState(GameState * state);
};

class MainMenuState : public GameState 
{
public:
	void handleEvent(Game & game, sf::Event e);
	void run(Game & game, float time);
	void draw(Game & game, sf::RenderWindow & window);

	void init(Game & game);
	void cleanup(Game & game);
};

class LoadStageState : public GameState
{
public:
	void handleEvent(Game & game, sf::Event e);
	void run(Game & game, float time);
	void draw(Game & game, sf::RenderWindow & window);

	void init(Game & game);
	void cleanup(Game & game);
};

class LoadLevelState : GameState
{
public:
	void handleEvent(Game & game, sf::Event e);
	void run(Game & game, float time);
	void draw(Game & game, sf::RenderWindow & window);

	void init(Game & game);
	void cleanup(Game & game);
};

class GameplayState : GameState
{
public:
	void handleEvent(Game & game, sf::Event e);
	void run(Game & game, float time);
	void draw(Game & game, sf::RenderWindow & window);

	void init(Game & game);
	void cleanup(Game & game);
};

class PauseState : GameState
{
public:
	void handleEvent(Game & game, sf::Event e);
	void run(Game & game, float time) { }
	void draw(Game & game, sf::RenderWindow & window);

	void init(Game & game);
	void cleanup(Game & game);
};


class GameOverState : GameState
{
public:
	void handleEvent(Game & game, sf::Event e);
	void run(Game & game, float time);
	void draw(Game & game, sf::RenderWindow & window);

	void init(Game & game);
	void cleanup(Game & game);
};

class ExitState : GameState
{
public:
	void handleEvent(Game & game, sf::Event e) { }
	void run(Game & game, float time) { }
	void draw(Game & game, sf::RenderWindow & window) { }

	void init(Game & game);
	void cleanup(Game & game) { }
};

#endif
