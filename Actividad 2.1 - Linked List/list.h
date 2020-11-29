/*
 *  list.h
 *	Mariana Castro Payns
 *  A01706038
 */

#ifndef LIST_H_
#define LIST_H_

#include <string>
#include <sstream>
#include "exception.h"

template <class T> class List;
template <class T> class ListIterator;

template <class T>
class Link {
private:
	Link(T);
	Link(T, Link<T>*);
	Link(const Link<T>&);

	T	    value;
	Link<T> *next;

	friend class List<T>;
	friend class ListIterator<T>;
};

template <class T>
Link<T>::Link(T val) : value(val), next(0) {}

template <class T>
Link<T>::Link(T val, Link* nxt) : value(val), next(nxt) {}

template <class T>
Link<T>::Link(const Link<T> &source) : value(source.value), next(source.next) {}

template <class T>
class List {
public:
	List();
	List(const List<T>&);
	~List();
	
	int  length() const;	
	bool empty() const;
	void clear();

	void addFirst(T);
	void add(T);
	
	T    removeFirst();
	T    remove(int);
	
	bool update(int, T);
	
	int  find(T) const;	
	
	std::string toString() const;

private:
	Link<T> *head;
	int 	size;

};

template <class T>
List<T>::List() : head(0), size(0) {}

template <class T>
void List<T>::clear() {
	Link<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	size = 0;
}

template <class T>
List<T>::~List() {
	clear();
}

template <class T>
bool List<T>::empty() const{
	return (head == 0);
}

template <class T>
int List<T>::length() const{
	return size;
}

template <class T>
void List<T>::addFirst(T val){
	Link<T> *newLink;

	newLink = new Link<T>(val);
	if (newLink == 0) {
		throw OutOfMemory();
	}
	newLink->next = head;
	head = newLink;
	size++;
}

template <class T>
void List<T>::add(T val) {
	Link<T> *newLink, *p;

	newLink = new Link<T>(val);
	if (newLink == 0) {
		throw OutOfMemory();
	}
	
	if (empty()) {
		addFirst(val);
		return;
	}

	p = head;
	while (p->next != 0) {
		p = p->next;
	}

	newLink->next = 0;
	p->next = newLink;
	size++;
}

template <class T>
bool List<T>::update(int index, T val){
	int pos;
	Link<T> *p;

	if (index < 0 || index >= size) {
		throw IndexOutOfBounds();
	}

	p = head;
	pos = 0;
	while (pos != index) {
		p = p->next;
		pos++;
	}

	p->value=val;
	return true;
}

template <class T>
int List<T>::find(T val) const {
	int index;
	Link<T> *p;
	
	index=0;
	p=head;
	
	while (p!=0){
		if (p->value==val){
			return index;
		}
		index ++;
		p=p->next;
	}
	return  -1;
}

template <class T>
T List<T>::removeFirst(){
	T val;
	Link<T> *p;

	if (empty()) {
		throw NoSuchElement();
	}

	p = head;

	head = p->next;
	val = p->value;

	delete p;
	size--;

	return val;
}

template <class T>
T List<T>::remove(int index) {
	int pos;
	T val;
	Link<T> *p, *q;
	
	if(index < 0 || index >= size){
		throw IndexOutOfBounds();
	}
	
	if (index==0){
		return removeFirst();
	}
	
	q=0;
	p=head;
	pos=0;
	while (pos!=index){
		q=p;
		p=p->next;
		pos++;
	}
	
	val=p->value;
	q->next=p->next;
	size--;
	
	delete p;
	
	return val;
}

template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}


#endif /* LIST_H_ */