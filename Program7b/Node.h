//Chris Walter
//Program7
//Node Class which is called by List Class

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

};

