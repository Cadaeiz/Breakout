#ifndef MENU_H_
#define MENU_H_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.hpp"

#define MAX_BUTTONS 10
#define MAX_TEXTS 10

class Menu
{
private:
	static sf::SoundBuffer mouseOverBuffer, pressButtonBuffer;
	sf::Sound mouseOverSound, pressButtonSound;
	sf::Sprite sprite;
	(Button *) buttons[MAX_BUTTONS];
	(sf::Text *) texts[MAX_TEXTS];
	int numButtons, numTexts, currentButton;
public:
	static void loadSounds();
	Menu(sf::Texture & texture, sf::Font & font, sf::Vector2f pos, string title);
	~Menu();
	int handleEvent(sf::Event e);
	void addButton(sf::Texture & texture, sf::Font & font, sf::Vector2f pos, string str, int ID);
	void addText(sf::Vector2f pos, sf::Font & font, int fontSize, string str);
	void draw(sf::RenderWindow & window);
	bool isPlayingSound() { return pressButtonSound.getStatus() == sf::Sound::Status::Playing; }
};

#endif
