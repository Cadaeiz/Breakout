#ifndef GAME_H_
#define GAME_H_

#include <SFML/Graphics.hpp>

#define NUMSTATES 1

class Game
{
	friend class MainMenuState;
	friend class LoadStageState;
	friend class LoadLevelState;
	friend class GameplayState;
	friend class PauseState;
	friend class GameOverState;
	friend class ExitState;
	const static int MAINMENU	= 0,
					 LOADSTAGE	= 1,
					 LOADLEVEL	= 2,
					 GAMEPLAY	= 3,
					 PAUSE		= 4,
					 GAMEOVER	= 5,
					 EXIT		= 6;
private:
	static struct
	{
		MainMenuState mainMenu;
		LoadStageState loadStage;
		LoadLevelState loadLevel;
		GameplayState gameplay;
		PauseState pause;
		GameOverState gameover;
		ExitState exit;
	} StateMachine;
	GameState * currentState;
	void changeState(int state);

public:
	const static int ScreenWidth = 800, ScreenHeight = 600;
	void init();
	void cleanup();

	void handleEvent(sf::Event e) { currentState -> handleEvent(*this, e); }
	void run(float time) { currentState -> run(*this, time); }
	void draw(sf::RenderWindow & window) { currentState -> draw(*this, window); }
};

#endif
