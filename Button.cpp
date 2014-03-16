#include "Button.hpp"

Button::Button(sf::Texture & texture, sf::Font & font, sf::Vector2f pos, string str, int ID) : ID(ID)
{
	sprite.setTexture(texture);

	text.setString(str);
	text.setFont(font);
	
	halfSize.x = sprite.getGlobalBounds().width / 2;
	halfSize.y = sprite.getGlobalBounds().height / 2;

	text.setCharacterSize((unsigned int) halfSize.y);
	center = pos;
	sprite.setPosition(pos - halfSize);
	pos.y -= 5;
	text.setPosition(pos);
	sf::FloatRect rect = text.getLocalBounds();
	text.setOrigin(rect.width / 2, rect.height / 2);
}

bool Button::contains(float x, float y)
{
	return ( abs(x - center.x) < halfSize.x && abs(y - center.y) < halfSize.y);
}
