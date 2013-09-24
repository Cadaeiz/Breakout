#include "TileState.hpp"

void TileActiveState::collide(Tile & t, Ball & b)
{
	if (--t.durability <= 0)
		t.changeState(Tile::DYING);
}

void TileDyingState::init(Tile & t)
{
	t.collisionBox = sf::FloatRect(0,0,0,0);
}


void TileDyingState::update(Tile & t)
{
	sf::Color color = t.sprite.getColor();
	if (color.a < 5)
		t.changeState(Tile::DEAD);

	color.a -= 5;
	t.sprite.setColor(color);
}
