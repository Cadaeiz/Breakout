#include "Game.hpp"
#include "GameState.hpp"

void Game::init()
{
}


void Game::cleanup()
{
}


void Game::changeState(int state)
{
	if (currentState)
		currentState -> cleanup(*this);

	switch(state)
	{
	case MAINMENU:
		currentState = &StateMachine.mainMenu;
		break;
	case LOADSTAGE:
		currentState = &StateMachine.loadStage;
		break;
	case LOADLEVEL:
		currentState = &StateMachine.loadLevel;
		break;
	case GAMEPLAY:
		currentState = &StateMachine.gameplay;
		break;
	case PAUSE:
		currentState = &StateMachine.pause;
		break;
	case GAMEOVER:
		currentState = &StateMachine.gameover;
		break;
	case EXIT:
		currentState = &StateMachine.exit;
		break;
	}

	currentState -> init(*this);
}
