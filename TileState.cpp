#include "TileState.hpp"
#include "Tile.hpp"


void TileState::draw(Tile & t, sf::RenderWindow & window) 
{
	window.draw(t.sprite); 
}

void TileActiveState::collide(Tile & t, Collidable * c)
{
	if (c -> getType() == 0)
		collide(t,(Ball *) c);
}

void TileActiveState::collide(Tile & t, Ball * b)
{
	if (--t.durability <= 0)
		t.changeState(Tile::DYING);
}

void TileDyingState::init(Tile & t)
{
	/* reset collisionBox: no more collisions with this object should occur */
	((CBRect *) t.box) -> setSize(sf::Vector2f(0,0));
}


void TileDyingState::update(Tile & t, float time)
{
	/* decrement the opacity of the sprite until it is invisible */
	sf::Color color = t.sprite.getColor();
	if (color.a < 5)
		t.changeState(Tile::DEAD);

	color.a -= 5;
	t.sprite.setColor(color);
}
