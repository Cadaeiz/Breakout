#include "GameState.hpp"
#include "Game.hpp"
#include <fstream>
#include "Singleton.hpp"
#include "CollisionHandler.hpp"

#define NUM_LIVES 5

void MainMenuState::init(Game & game)
{
	game.factory.reset();
	game.level = 0;
	game.lives = NUM_LIVES;
	game.stage = 0;
	game.score = 0;
	game.currentStage = 0;
	game.currentSpeed = 20;

	
	/* create Main Menu */
	game.currentMenu = new Menu(game.menuTexture, game.font, sf::Vector2f(400,300), "Breakout");
	game.menus.addItem(game.currentMenu);
	
	game.currentMenu -> addButton(game.buttonTexture, game.font, sf::Vector2f(0,5),"New Game", NewGame);
	game.currentMenu -> addButton(game.buttonTexture, game.font, sf::Vector2f(0,45),"Controls",Controls);
	game.currentMenu -> addButton(game.buttonTexture, game.font, sf::Vector2f(0,85),"Level Editor",LevelEditor);
	game.currentMenu -> addButton(game.buttonTexture, game.font, sf::Vector2f(0,125),"Exit",Exit);

	game.bgTexture.loadFromFile("mainmenubg.png");
}

void MainMenuState::handleEvent(Game &  game, sf::Event e)
{
	int ID = game.currentMenu -> handleEvent(e);
	switch(ID)
	{
	case NewGame:
		game.changeState(Game::GAMEPLAY);
		break;
	case Controls:
		game.currentMenu = new Menu(game.menuTexture, game.font, sf::Vector2f(400,300), "Controls");
		game.menus.addItem(game.currentMenu);

		game.currentMenu -> addButton(game.buttonTexture, game.font, sf::Vector2f(0,125),"Back",Back);
		game.currentMenu -> addText(sf::Vector2f(0,-35),game.font,20,"Move Paddle: Arrow Keys / Mouse Position");
		game.currentMenu -> addText(sf::Vector2f(0,5),game.font,20,"Launch Ball: Space / Left Mouse Button");
		game.currentMenu -> addText(sf::Vector2f(0,45),game.font,20,"Pause: Enter");
		break;

	case LevelEditor:
		game.currentMenu = new Menu(game.menuTexture, game.font, sf::Vector2f(400,300), "Choose Stage");
		game.menus.addItem(game.currentMenu);

		game.currentMenu -> addButton(game.buttonTexture, game.font, sf::Vector2f(0,-35),"<Type 1>",Stage1);
		game.currentMenu -> addButton(game.buttonTexture, game.font, sf::Vector2f(0,5),"<Type 2>",Stage2);
		game.currentMenu -> addButton(game.buttonTexture, game.font, sf::Vector2f(0,45),"<Type 3>",Stage3);
		game.currentMenu -> addButton(game.buttonTexture, game.font, sf::Vector2f(0,85),"<Type 4>",Stage4);
		game.currentMenu -> addButton(game.buttonTexture, game.font, sf::Vector2f(0,125),"Back",Back);
		break;
	case Exit:
		game.changeState(Game::EXIT);
		break;
	case Back:
		game.menus.removeItem(game.currentMenu);
		delete game.currentMenu;
		game.currentMenu = 0;
		for (List<Menu>::Iterator iter = game.menus.getIterator(); iter.hasNext();)
			game.currentMenu = iter.next();
		break;
	case Stage1:
	case Stage2:
	case Stage3:
	case Stage4:
		/* change to the given stage graphics, then load the Level Editor */
		game.currentStage = ID - 5;
		game.bgTexture.loadFromFile(game.stageNames[game.currentStage] + "bg.png");
		game.factory.loadSpriteSheet(game.stageNames[game.currentStage] + "ss.png");
		
		game.changeState(Game::LEVELEDITOR);
		break;
	}
}

void MainMenuState::draw(Game & game, sf::RenderWindow & window)
{
	window.draw(game.bgSprite);
	List<Menu>::Iterator iter = game.menus.getIterator();
	while(iter.hasNext())
		iter.next() -> draw(window);
}

void MainMenuState::cleanup(Game & game)
{
	/* remove & delete all menus in list */
	List<Menu>::Iterator iter = game.menus.getIterator();
	while(iter.hasNext())
	{
		delete iter.next();
		iter.removeLastItem();
	}
	game.currentMenu = 0;
}

void GameplayState::run(Game & game, float time)
{
	if (game.factory.tileFactory.isEmpty())
		game.loadLevel();

	if (game.factory.ballFactory.isEmpty())
	{
		if (--game.lives < 0)
			game.changeState(Game::GAMEOVER);

		game.factory.ballFactory.generate(game.currentSpeed,*game.factory.paddleFactory.getFirst());
	}

	game.factory.update(time);
	Singleton<CollisionHandler>::getInstance() -> handleCollisions();
	game.score += 100 * game.factory.filterDead();
}

void GameplayState::handleEvent(Game & game, sf::Event e)
{
	if (e.type == sf::Event::KeyPressed && 
		e.key.code == sf::Keyboard::Return)
		game.changeState(Game::PAUSE);
	else
		game.factory.paddleFactory.handleEvent(e);
}

void GameplayState::draw(Game & game, sf::RenderWindow & window)
{
	window.draw(game.bgSprite);
	game.factory.draw(window);
}

void GameOverState::init(Game & game)
{
	/* create Game Over Menu */
	game.currentMenu = new Menu(game.menuTexture, game.font, sf::Vector2f(400,300), "Game Over");

	game.currentMenu -> addButton(game.buttonTexture, game.font, sf::Vector2f(0,45),"Continue",Continue);
	game.currentMenu -> addButton(game.buttonTexture, game.font, sf::Vector2f(0,85),"Main Menu",MainMenu);
	game.currentMenu -> addButton(game.buttonTexture, game.font, sf::Vector2f(0,125),"Exit",Exit);

	/* add score to menu (and check if a new high score was reached) */
	string score = "Score: " + game.score;
	if (game.score > game.highscore)
	{
		game.score = game.highscore;
		score += "(new record!)";
	}
	game.currentMenu -> addText(sf::Vector2f(0,-70),game.font,20,score);

	/* reset the current level and number of lives */
	game.level = 0;
	game.lives = NUM_LIVES;
}

void GameOverState::handleEvent(Game & game, sf::Event e)
{
	int ID = game.currentMenu -> handleEvent(e);
	switch(ID)
	{
	case Continue:
		game.changeState(Game::GAMEPLAY);
		break;
	case MainMenu:
		game.changeState(Game::MAINMENU);
		break;
	case Exit:
		game.changeState(Game::EXIT);
		break;
	}
}

void GameOverState::draw(Game & game, sf::RenderWindow & window)
{
	window.draw(game.bgSprite);
	game.factory.draw(window);
	game.currentMenu -> draw(window);
}

void GameOverState::cleanup(Game & game)
{
	/* delete the Game Over menu */
	delete game.currentMenu;
	game.currentMenu = 0;
	game.factory.reset();
}


void PauseState::init(Game & game)
{
	/* create pause menu */
	game.currentMenu = new Menu(game.menuTexture, game.font, sf::Vector2f(400,300), "Paused");

	game.currentMenu -> addButton(game.buttonTexture, game.font, sf::Vector2f(0,45),"Continue",Continue);
	game.currentMenu -> addButton(game.buttonTexture, game.font, sf::Vector2f(0,85),"Main Menu",MainMenu);
	game.currentMenu -> addButton(game.buttonTexture, game.font, sf::Vector2f(0,125),"Exit",Exit);

}

void PauseState::handleEvent(Game & game, sf::Event e)
{
	int ID = game.currentMenu -> handleEvent(e);
	switch(ID)
	{
	case Continue:
		game.changeState(Game::GAMEPLAY);
		break;
	case MainMenu:
		game.changeState(Game::MAINMENU);
		break;
	case Exit:
		game.changeState(Game::EXIT);
		break;
	}
}

void PauseState::draw(Game & game, sf::RenderWindow & window)
{
	window.draw(game.bgSprite);
	game.factory.draw(window);
	game.currentMenu -> draw(window);
}

void PauseState::cleanup(Game & game)
{
	/* delete the pause menu */
	delete game.currentMenu;
	game.currentMenu = 0;
}


void LevelCreationState::handleEvent(Game & game, sf::Event e)
{
	switch(e.type)
	{
	case sf::Event::KeyPressed:
		if (e.key.code == sf::Keyboard::Return)
			game.changeState(Game::LCPAUSE);
		break;

	case sf::Event::MouseMoved:
		game.activeTile.setPosition((float) e.mouseMove.x, (float) e.mouseMove.y);
		if (game.activeTile.isValid())
			game.activeTile.setColor(sf::Color::Green);
		else
			game.activeTile.setColor(sf::Color::Red);
		break;

	case sf::Event::MouseButtonPressed:
		/* if clicking on a position where the tile can be placed */
		if (e.mouseButton.button == sf::Mouse::Left && game.activeTile.isValid())
			game.factory.tileFactory.generate(game.activeTile);
		else if (e.mouseButton.button == sf::Mouse::Right)
			game.activeTile.cycleType();
		break;

	case sf::Event::MouseWheelMoved:
		game.activeTile.changeDur(e.mouseWheel.delta);
		break;
	}
}

void LevelCreationState::draw(Game & game, sf::RenderWindow & window)
{
	window.draw(game.bgSprite);
	game.factory.draw(window);


}

void LCPauseState::init(Game & game)
{
	/* create pause menu */
	game.currentMenu = new Menu(game.menuTexture, game.font, sf::Vector2f(400,300), "Paused");

	game.currentMenu -> addButton(game.buttonTexture, game.font, sf::Vector2f(0,5),"Continue",Continue);
	game.currentMenu -> addButton(game.buttonTexture, game.font, sf::Vector2f(0,45),"Save Design",SaveDesign);
	game.currentMenu -> addButton(game.buttonTexture, game.font, sf::Vector2f(0,85),"Main Menu",MainMenu);
	game.currentMenu -> addButton(game.buttonTexture, game.font, sf::Vector2f(0,125),"Exit",Exit);

	game.typing = false;
	game.filename = "";
	game.filenameText.setFont(game.font);
	game.filenameText.setCharacterSize(20);
	game.filenameText.setPosition(400,345);
}

void LCPauseState::handleEvent(Game & game, sf::Event e)
{
	int ID = game.currentMenu -> handleEvent(e);
	switch(ID)
	{
	case Continue:
		game.changeState(Game::LEVELEDITOR);
		break;
	case SaveDesign:
		game.typing = true;
		game.filename = "";
		game.filenameText.setString("");
		break;
	case MainMenu:
		game.changeState(Game::MAINMENU);
		break;
	case Exit:
		game.changeState(Game::EXIT);
		break;
	}

	if (game.typing && e.type == sf::Event::TextEntered)
	{
		if (e.text.unicode < 128)
		{
			game.filename += static_cast<char>(e.text.unicode);
			game.filenameText.setString(game.filename);
		}
	}
	if (game.typing && e.type == sf::Event::KeyPressed &&
		e.key.code == sf::Keyboard::Return)
	{
		game.filenameText.setString(game.filename + " (saved)");
		game.typing = false;

		std::ofstream file;
		file.open(game.filename + ".data");
		file << game.stageNames[game.currentStage] << '\n';
		List<Tile>::Iterator iter = game.factory.tileFactory.getList().getIterator();
		while (iter.hasNext())
			file << iter.next() -> toString();

		file.close();
	}
}

void LCPauseState::draw(Game & game, sf::RenderWindow & window)
{
	window.draw(game.bgSprite);
	game.factory.draw(window);
	game.currentMenu -> draw(window);
	window.draw(game.filenameText);
}

void LCPauseState::cleanup(Game & game)
{
	/* delete the pause menu */
	delete game.currentMenu;
	game.currentMenu = 0;
}


void ExitState::init(Game & game)
{
	/* set the exit flag and delete any remaining menus */
	game.factory.exit();
}