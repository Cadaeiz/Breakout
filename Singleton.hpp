#ifndef SINGLETON_H_
#define SINGLETON_H_

template <class T>
class Singleton
{
private:
	Singleton();
	static T t;
public:
	static T * getInstance() { return &t; }
};

#endif
