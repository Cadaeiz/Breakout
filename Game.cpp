#include "Game.hpp"
#include "GameState.hpp"

#include <sstream>


struct Game::Machine Game::StateMachine;

void Game::init()
{
	menuTexture.loadFromFile("menu.png");
	buttonTexture.loadFromFile("button.png");

	
	stageNames[0] = "forest";
	stageNames[1] = "water";
	stageNames[2] = "sky";
	stageNames[3] = "space";

	font.loadFromFile("arial.ttf");
	changeState(MAINMENU);
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
	case LEVELEDITOR:
		currentState = &StateMachine.levelcreation;
		break;
	case LCPAUSE:
		currentState = &StateMachine.lcpause;
		break;
	}

	currentState -> init(*this);
}

void Game::loadLevel()
{
	/* update current level */
	if (++level > NUMLEVELS)
	{
		level = 1;
		if (++currentStage >= NUMSTAGES)
		{
			currentStage = 0;
			currentSpeed *= 1.5;
		}
	}

	bgTexture.loadFromFile(stageNames[currentStage] + "bg.png");
	factory.loadSpriteSheet(stageNames[currentStage] + "ss.png");
	std::stringstream stagelevel;
	stagelevel << stageNames[currentStage] << level << ".data";
	factory.loadLevel(stagelevel.str());
}
