#ifndef LIST_H_
#define LIST_H_

template <class Item>
class List
{
private:
	struct Node
	{
		Item * item;
		Node * next;
		Node * prev;
	};
	Node * first, * last;
	void removeNode(Node * n);
public:
	class Iterator
	{
	private:
		Node * nextNode, * prevNode;
	public:
		Iterator(Node * start = 0) : nextNode(start), prevNode(0) { }
		bool hasNext() { return (nextNode != 0); }
		Item * removeLastItem();
		Item * next();
	};

	List() : first(0), last(0) { }
	~List();
	void addItem(Item * item);
	bool removeItem(Item * item);
	Iterator getIterator();
};

#endif