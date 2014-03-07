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
	const static int NewGame = 0, Controls = 1, LevelEditor = 2, Exit = 3, Back = 4,
					 Stage1 = 5, Stage2 = 6, Stage3 = 7, Stage4 = 8;
public:
	void handleEvent(Game & game, sf::Event e);
	void run(Game & game, float time) { }
	void draw(Game & game, sf::RenderWindow & window);

	void init(Game & game);
	void cleanup(Game & game);
};

class GameplayState : public GameState
{
public:
	void handleEvent(Game & game, sf::Event e);
	void run(Game & game, float time);
	void draw(Game & game, sf::RenderWindow & window);

	void init(Game & game) { }
	void cleanup(Game & game) { }
};

class PauseState : public GameState
{
	const static int Continue = 0, MainMenu = 1, Exit = 2;
public:
	void handleEvent(Game & game, sf::Event e);
	void run(Game & game, float time) { }
	void draw(Game & game, sf::RenderWindow & window);

	void init(Game & game);
	void cleanup(Game & game);
};


class GameOverState : public GameState
{
	const static int Continue = 0, MainMenu = 1, Exit = 2;
public:
	void handleEvent(Game & game, sf::Event e);
	void run(Game & game, float time) { }
	void draw(Game & game, sf::RenderWindow & window);

	void init(Game & game);
	void cleanup(Game & game);
};

class ExitState : public GameState
{
public:
	void handleEvent(Game & game, sf::Event e) { }
	void run(Game & game, float time) { }
	void draw(Game & game, sf::RenderWindow & window) { }

	void init(Game & game);
	void cleanup(Game & game) { }
};

class LevelCreationState : public GameState
{
public:
	void handleEvent(Game & game, sf::Event e);
	void run(Game & game, float time) { }
	void draw(Game & game, sf::RenderWindow & window);

	void init(Game & game) { }
	void cleanup(Game & game) { }
};

class LCPauseState : public GameState
{
	const static int Continue = 0, MainMenu = 1, SaveDesign = 2, Exit = 3;
public:
	void handleEvent(Game & game, sf::Event e);
	void run(Game & game, float time) { }
	void draw(Game & game, sf::RenderWindow & window);

	void init(Game & game);
	void cleanup(Game & game);
};

#endif
