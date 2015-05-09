#pragma once
using namespace std;
#include <iostream>



template<class T>
class Node
{
public:
	Node(){ next = prev = nullptr; }
	Node(const T& item){ next = prev = nullptr; data = item; }
	Node<T> *next, *prev;
	T data;

	/*
	Node<T>* getNext();
	Node<T>* getPrev();
	T getData();
	void setNext(Node<T> aNode);
	void setPrev(Node<T> aNode);
	void setData(T item);
	*/

};

