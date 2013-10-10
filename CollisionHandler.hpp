#ifndef COLLISIONHANDLER_H_
#define COLLISIONHANDLER_H_

#include "Ball.hpp"
#include "Wall.hpp"
#include "Paddle.hpp"
#include "Tile.hpp"
#include "List.hpp"

class CollisionHandler
{
private:
	List<Ball> & balls;
	List<Wall> & walls;
	List<Paddle> & paddles;
	List<Tile> & tiles;

public:
	CollisionHandler(List<Ball> & b, List<Wall> & w, 
					 List<Paddle> & p, List<Tile> & t) :
					 balls(b), walls(w), paddles(p), tiles(t) { }
	void handleCollisions();
};

#endif
