#ifndef GAME_H_
#define GAME_H_

#include <SFML/Graphics.hpp>
#include "FactoryFactory.hpp"
#include "Menu.hpp"
#include "GameState.hpp"

#define NUMSTAGES 4
#define NUMLEVELS 4

class Game
{
	friend class MainMenuState;
	friend class GameplayState;
	friend class PauseState;
	friend class GameOverState;
	friend class ExitState;
	friend class LevelCreationState;
	friend class LCPauseState;

	const static int MAINMENU	 = 0,
					 GAMEPLAY	 = 1,
					 PAUSE		 = 2,
					 GAMEOVER	 = 3,
					 EXIT		 = 4,
					 LEVELEDITOR = 5,
					 LCPAUSE	 = 6;

private:
	static struct Machine
	{
		MainMenuState mainMenu;
		GameplayState gameplay;
		PauseState pause;
		GameOverState gameover;
		ExitState exit;
		LevelCreationState levelcreation;
		LCPauseState lcpause;
	} StateMachine;
	GameState * currentState;
	void changeState(int state);
	
	FactoryFactory factory;
	int level, lives, stage;
	unsigned int score, highscore;
	sf::Texture bgTexture, menuTexture, buttonTexture;
	sf::Sprite bgSprite;
	List<Menu> menus;
	Menu * currentMenu;
	string stageNames[NUMSTAGES];
	int currentStage;
	float currentSpeed;
	sf::Font font;
	Tile activeTile;
	string filename;
	sf::Text filenameText, scoreText;
	bool typing;
	sf::Music bgmusic;

public:
	Game() : activeTile(3) { }
	const static int ScreenWidth = 800, ScreenHeight = 600;
	void init();
	void cleanup();

	void handleEvent(sf::Event e) { currentState -> handleEvent(*this, e); }
	void run(float time) { currentState -> run(*this, time); }
	void draw(sf::RenderWindow & window) { currentState -> draw(*this, window); drawScores(window); }
	void loadLevel();
	bool exited() { return currentState == &StateMachine.exit; }
	void drawScores(sf::RenderWindow & window);
};

#endif
