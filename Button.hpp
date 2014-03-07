#ifndef BUTTON_H_
#define BUTTON_H_

#include <SFML/Graphics.hpp>
#include <string>

using std::string;

class Button
{
private:
	sf::Sprite sprite;
	sf::Text text;
	int ID;
	sf::Vector2f halfSize, center;

public:
		Button(sf::Texture & texture, sf::Font & font, sf::Vector2f pos, string str, int ID);
		bool contains(float x, float y);
		bool contains(sf::Vector2f pos) { return contains(pos.x,pos.y); }
		void highlight() { sprite.setColor(sf::Color::Yellow); }
		void unhighlight() { sprite.setColor(sf::Color::White); }
		int getID() { return ID; }
		void draw(sf::RenderWindow & window) { window.draw(sprite); window.draw(text); }
};

#endif