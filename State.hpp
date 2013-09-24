#ifndef STATE_H_
#define STATE_H_

#include <SFML/Graphics.hpp>

template <class T>
class State
{
protected:
	virtual void init(T::Data & d) = 0;
	virtual void cleanup(T::Data & d) = 0;
	void changeState(T::Data & d, int type);
public:
	virtual void update(T::Data & d) = 0;
	virtual void draw(T::Data & d, sf::RenderWindow & window) = 0;
};

/*
 * example of a class using State
 *		getState creates creates a single static object of a class derived from State<T>
 *		each state derived from state<T> should be given a unique int to identify it (type)
 *		all object data (except for currentState) should be kept in data (Data struct)

class StateMachine
{
private:
	State<StateMachine> * currentState;
	Data data;
	static State<StateMachine> * getState(int type);
public:
	struct Data {...};
	void update() { currentState -> update(data); }
	void draw(sf::RenderWindow & window) { currentState -> draw(data, window); }
}

*/
#endif
