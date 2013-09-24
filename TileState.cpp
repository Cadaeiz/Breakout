#include "TileState.hpp"

void TileActiveState::collide(Tile & t, Ball & b)
{
	if (--t.durability <= 0)
		t.changeState(Tile::DYING);
}

void TileDyingState::init(Tile & t)
{
	t.collisionBox = sf::FloatRect(0,0,0,0);
	t.timer = 
}


void TileDyingState::update(Tile & t)
{
	
}
