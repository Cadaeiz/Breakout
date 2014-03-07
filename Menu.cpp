#include "Menu.hpp"

Menu::Menu(sf::Texture & texture, sf::Font & font, sf::Vector2f pos, string title)
{
	sprite.setTexture(texture);
	sf::Vector2f halfSize(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sprite.setPosition(pos);
	sprite.setOrigin(halfSize);

	numButtons = 0;
	numTexts = 0;

	addText(sf::Vector2f(0,-135),font, 20,title);
}

int Menu::handleEvent(sf::Event e)
{
	switch(e.type)
	{
	case sf::Event::MouseMoved:
		for (int i = 0; i < numButtons; i++)
		{
			if(buttons[i] -> contains((float) e.mouseMove.x, (float) e.mouseMove.y))
				buttons[i] -> highlight();
			else
				buttons[i] -> unhighlight();
		}
		break;

	case sf::Event::MouseButtonPressed:
		if (e.mouseButton.button == sf::Mouse::Left)
			for (int i = 0; i < numButtons; i++)
				if (buttons[i] -> contains((float) e.mouseButton.x, (float) e.mouseButton.y))
					return buttons[i] -> getID();
		break;
	}
	return -1;
}

void Menu::addButton(sf::Texture & texture, sf::Font & font, sf::Vector2f pos, string str, int ID)
{
	buttons[numButtons++] = new Button(texture,font,pos,str,ID);
}

void Menu::addText(sf::Vector2f pos, sf::Font & font, int fontSize, string str)
{
	texts[numTexts] = new sf::Text();
	texts[numTexts] -> setFont(font);
	texts[numTexts] -> setString(str);
	texts[numTexts] -> setPosition(pos);
	texts[numTexts] -> setCharacterSize(fontSize);
	sf::FloatRect rect = texts[numTexts] -> getLocalBounds();
	texts[numTexts++] -> setOrigin(rect.width / 2, rect.height / 2);
}

void Menu::draw(sf::RenderWindow & window)
{
	window.draw(sprite);

	for (int i = 0; i < numButtons; i++)
		buttons[i] -> draw(window);
	for (int i = 0; i < numTexts; i++)
		window.draw(*texts[i]);
}

Menu::~Menu()
{
	/* delete all buttons and text */
	while (--numButtons >= 0)
		delete buttons[numButtons];

	while (--numTexts >= 0)
		delete texts[numTexts];
}