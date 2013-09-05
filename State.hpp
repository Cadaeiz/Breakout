#ifndef STATE_H_
#define STATE_H_

#include <SFML/Graphics.hpp>

template <class T>
class State
{
protected:
	virtual void init(T & t) = 0;
	virtual void cleanup(T & t) = 0;
	void changeState(T & t, int type);
public:
	virtual void update(T & t) = 0;
	virtual void draw(T & t, sf::RenderWindow & window) = 0;
	friend class T;
};

/*
 * example of a class using State
 *		getState creates creates a single static object of a class derived from State<T>
 *		each state derived from state<T> should be given a unique int to identify it (type)

class StateMachine
{
	friend class State<StateMachine>;
private:
	State<StateMachine> * currentState;
	static State<StateMachine> * getState(int type);
public:
	void update() { currentState -> update(*this); }
	void draw(sf::RenderWindow & window) { currentState -> draw(*this, window); }
}

*/
#endif
