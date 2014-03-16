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
	int num_elts;
	class Iterator
	{
	private:
		Node * nextNode, * prevNode;
		List<Item> * list;
	public:
		Iterator(List<Item> * list, Node * start = 0) : nextNode(start), prevNode(0), list(list) { }
		bool hasNext() { return (nextNode != 0); }
		Item * removeLastItem();
		Item * next();
	};

	List() : first(0), last(0), num_elts(0) { }
	~List();
	void addItem(Item * item);
	bool removeItem(Item * item);
	Iterator getIterator();
};


template <class Item>
void List<Item>::addItem(Item * item)
{
	Node * n = new Node;
	n -> item = item;
	/* add node to the end of the list */
	n -> prev = last;
	n -> next = 0;
	if (last == 0)
		first = n;
	else
		last -> next = n;
	last = n;
	num_elts++;
}

template <class Item>
bool List<Item>::removeItem(Item * item)
{
	bool removed = false;
	Node * match = 0;

	for (Node * n = first; n != 0; n = n -> next, delete match)
	{
		match = 0;
		if (n -> item == item)
		{
			removeNode(n);
			/* mark node for deletion */
			match = n;
			removed = true;
		}
	}
	return removed;
}

template <class Item>
void List<Item>::removeNode(Node * n)
{
	if (n -> prev != 0)
		(n -> prev) -> next = n -> next;
	else
		first = n -> next;

	if (n -> next != 0)
		(n -> next) -> prev = n -> prev;
	else
		last = n -> prev;
	num_elts--;
}

template <class Item>
List<Item>::~List()
{
	/* delete all remaining nodes */
	Node * n = first;

	while (first != 0)
	{
		n = first;
		first = first -> next;
		delete n;
	}
}

template <class Item>
typename List<Item>::Iterator List<Item>::getIterator()
{
	return Iterator(this, first);
}

template <class Item>
Item * List<Item>::Iterator::next()
{
	if(hasNext())
	{
		prevNode = nextNode;
		nextNode = nextNode -> next;
		return prevNode -> item;
	}
	else
		return 0;
}

template <class Item>
Item * List<Item>::Iterator::removeLastItem()
{
	Item * item = 0;
	if (prevNode != 0)
	{
		list -> removeNode(prevNode);
		item = prevNode -> item;
		delete prevNode;
		prevNode = 0;
	}
	return item;
}


#endif
