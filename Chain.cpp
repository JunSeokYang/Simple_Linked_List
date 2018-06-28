#include <iostream>

using namespace std;

template <typename T> class Chain;
template <typename T> class Node;

template <typename T>
class Node {
public:
	friend class Chain<T>;
	Node(T element = 0, Node<T>* next = 0);
private:
	T data;
	Node<T>* link;
};

template <typename T>
Node<T>::Node(T element = 0, Node<T>* next = 0) :
	data{ element }, link{ next } {}

template <typename T>
class Chain {
public:
	Chain(T data = 0, Node<T>* next = 0);
	T Insert(T data, Node<T>* x);
	T InsertBack(T data);
	Chain<T> Concatenate(Chain<T>& linkedchain);
	class ChainIterator {
	public:
		ChainIterator(Node<T>* startNode = 0) { current = startNode; }

		T& operator*()const { return current->data; }
		T* operator->()const { return &current->data; }

		ChainIterator& operator++() { current = current->link; return *this; }
		ChainIterator operator++(int) { ChainIterator old = *this; current = current->link; return old; }

		bool operator!=(const ChainIterator right)const { return current != right.current }
		bool operator==(const ChainIterator right)const { return current == right.current }

	private:
		Node<T>* current;
	};
	class ChainIterator begin() { return ChainIterator(first); }
	class ChainIterator end() { return ChainIterator(0); }
private:

	Node<T>* first,last;
};

template <typename T>
Chain<T>::Chain(T data = 0, Node<T>* next = 0) :
	first{ new Node<T>(data,next) } {}

template <typename T>
T Chain<T>::Insert(T data, Node<T>* x) {
	if (first) {
		x->link = new Node<T>(data, x->link);
		if (x->link->link == 0)
			last = x->link;
	}
	else
		last = first = new Node<T>(data);
	return data;
}

template <typename T>
T Chain<T>::InsertBack(T data) {
	if (first) {
		last->link = new Node<T>(data);
		last = last->link;
	}
	else
		first = last = new Node<T>(data);
}

template <typename T>
Chain<T> Chain<T>::Concatenate(Chain<T>& linkedchain) {
	if (first) {
		last->link = linkedchain.first;
		last = linkedchain.last;
	}
	else {
		first = linkedchain.first;
		last = linkedchain.last;
	}
	linkedchain.first = linkedchain.last = 0;
}

void main(void) {
	Chain<int> a(1);
}