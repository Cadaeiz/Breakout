#include "State.hpp"

template<class T>
void State::changeState(T & t, int type)
{
	if (t -> currentState != 0)
		(State<T> *) (t -> currentState) -> cleanup(t);
	t -> currentState = T::getState(type);
	(State<T> *) (t -> currentState) -> init(t);
}