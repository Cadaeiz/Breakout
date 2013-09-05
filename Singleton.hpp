#ifndef SINGLETON_H_
#define SINGLETON_H_

template <class T>
class Singleton
{
private:
	Singleton();
public:
	static T * getInstance();
};

template <class T>
T * Singleton::getInstance()
{
	static T t;
	return &t;
}

#endif
