#ifndef FACTORY_H_
#define FACTORY_H_

#include "List.hpp"

template <class T>
class Factory
{
private:
	List<T> active;
public:
	~Factory();
	void filterDead();
	T * generate();
	void reset();
	List<T> * getList();
};

#endif