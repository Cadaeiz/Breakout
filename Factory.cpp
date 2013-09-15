#include "Factory.hpp"

template <class T>
Factory::~Factory()
{
	reset();
}

template <class T>
void Factory::filterDead()
{
	List<T>::Iterator iter = active.getIterator();
	T * t;
	while (iter.hasNext())
	{
		t = iter.next();
		if (t -> isDead())
		{
			active.removeItem(t);
			delete t;
		}
	}
}

template <class T>
void Factory::reset()
{
	List<T>::Iterator iter = active.getIterator();
	T * t;
	while (iter.hasNext())
	{
		t = iter.next();
		active.removeItem(t);
		delete t;
	}
}

template <class T>
T * Factory::generate()
{
	T * t = new T();
	active.addItem(t);
	return t;
}

template <class T>
List<T> * getList()
{
	return &active;
}