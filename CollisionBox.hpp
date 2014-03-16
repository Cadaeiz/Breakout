#ifndef COLLISION_BOX
#define COLLISION_BOX

#include "GameObject.hpp"
#include "List.hpp"

class CBCircle;
class CBRect;
class CBArray;

/* Generic Collision Box held by all collidable objects */
class CollisionBox
{
protected:
	int type;
public:
	int getType() { return type; }
	virtual sf::Vector2f getCenter() = 0;
	virtual sf::Vector2f getSize() = 0;
	virtual void setPosition(sf::Vector2f pos) = 0;
	virtual void move(sf::Vector2f pos) = 0;
	virtual bool intersects(CollisionBox * c) = 0;
};

/* Rectangular Collision Box */
class CBRect : public CollisionBox
{
protected:
	sf::Vector2f center;
	sf::Vector2f size;
public:
	CBRect(sf::Vector2f center, sf::Vector2f size) : center(center), size(size) { type = 0;}
	CBRect(float x, float y, float width, float height) : center(sf::Vector2f(x,y)), size(sf::Vector2f(width,height)) { type = 0; }
	CBRect(CBRect & rect) : center(rect.center), size(rect.size) { type = 0; }
	void setPosition(sf::Vector2f pos) {center =  pos; }
	void setSize(sf::Vector2f sz) { size = sz; }
	sf::Vector2f getCenter() { return center; }
	sf::Vector2f getSize() { return size; }
	void move(sf::Vector2f diff) { center += diff; }
	bool intersects(CBRect * cbr);
	bool intersects(CBCircle * cbc);
	bool intersects(CollisionBox * cb);
};

/* Circular Collision Box */
class CBCircle : public CollisionBox
{
protected:
	sf::Vector2f center;
	float radius;
public:
	CBCircle(sf::Vector2f center, float radius) : center(center), radius(radius) { type = 1; }
	CBCircle(float x, float y, float radius) : center(sf::Vector2f(x,y)), radius(radius) { type = 1; }
	CBCircle(CBCircle & circle) : center(circle.center), radius(circle.radius) { type = 1; }
	void setPosition(sf::Vector2f pos) { center = pos; }
	void setRadius(float rad) { radius = rad; }
	sf::Vector2f getCenter() { return center; }
	sf::Vector2f getSize() { return sf::Vector2f(2*radius, 2*radius); }
	float getRadius() { return radius; }
	void move(sf::Vector2f diff) { center += diff; }
	bool intersects(CBCircle * cbc);
	bool intersects(CollisionBox * cb);
};

/* array of circular and rectangular collision boxes */
class CBArray : public CollisionBox
{
protected:
	List<CollisionBox> boxes;
	sf::Vector2f center;
public:
	CBArray(sf::Vector2f center = sf::Vector2f(0,0)) : center(center) { type = 2; }
	CBArray(CBArray & arr) : center(arr.center) { type = 2; }
	~CBArray();
	void addCircle(sf::Vector2f center, float radius) { boxes.addItem(new CBCircle(center, radius)); }
	void addCircle(float x, float y, float radius) { boxes.addItem(new CBCircle(x, y, radius)); }
	void addRect(sf::Vector2f center, sf::Vector2f size) {boxes.addItem(new CBRect(center, size)); }
	void addRect(float x, float y, float width, float height) {boxes.addItem(new CBRect(x, y, width, height)); }
	sf::Vector2f getCenter() { return center; }
	sf::Vector2f getSize() { return sf::Vector2f(0,0); }
	void move(sf::Vector2f diff);
	void setPosition(sf::Vector2f pos) { move(pos - center); }
	bool intersects(CollisionBox * box);
};

#endif
