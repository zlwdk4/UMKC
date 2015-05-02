
#pragma once
#include <iostream>

using namespace std;

#include "Node.h"



///List Class .h File -------->

template<class T>
class List
{
public:
	List(){ count = 0; Head = Tail = nullptr; }
	~List(){ clear(); } //destructor 
	const List<T>& operator=(const List<T>& rhs);
	//List(const List<T> & other); copy constructor

	//Methods

	void push_front(const T& item);
	void push_back(const T& item);
	void clear();
	void sort(); //merge sort
	void printList();
	const T front() const; 
	const T back() const;
	int size() const;
    void pop_front();
    void pop_back();


	//Merge Sort Method 
	//Credit goes to Mr. Hare for the implementation
	void Sort(Node<T>*& H); 
	void Split(Node<T>*& H, Node<T>*& P, Node<T>*& Q);
	void Merge(Node<T>*& H, Node<T>*& P, Node<T>*& Q);


private:
	int count;
	Node<T> *Head, *Tail;



};

//implementation ---------->

template<class T>
const List<T>& List<T>::operator=(const List<T>& rhs){
	if (this != &rhs){
		clear(); //remove existing data on left of operand
		Node<T> *nodePtr = rhs.Head; //create new ptr and point to first node on right
		while (nodePtr != nullptr){ //while not at end
			push_back(nodePtr->data); //create new nodes on left of operand
			nodePtr = nodePtr->next; //advance to new node
		}
	}
	return *this; 

}

template <class T>
void List<T>::push_front(const T& item){

	if (Head == nullptr){ //list is empty add a new node and set tail and head to that node
		Head = new Node<T>(item);
		Tail = Head;
		count++; 
	}
	else {
		Node<T>* tempNode = new Node<T>(item);
		Head->prev = tempNode;
		Head->prev->next = Head;
		Head = Head->prev;
		count++;
	}

}

template<class T>
void List<T>::push_back(const T& item){
	if (Head == nullptr){  //list is empty add a new node and set tail and head to new node
		Head = new Node<T>(item);
		Tail = Head;
		count++; 
	}
	else{
		Tail->next = new Node<T>(item);
		Tail->next->prev = Tail;
		Tail = Tail->next;
		count++;
	}

	
}
template<class T>
void List<T>::clear(){
	
	while (Head != nullptr){
		Node<T> *temp = Head;  //hold on to Head
		Head = Head->next;  //advance head
		delete temp;       //delete old node
	}
	count = 0; //zero items in list
}


template<class T>
void List<T>::printList(){

	if (Head == nullptr){
		cout << "Empty List" << endl;
	}

	else{
		Node<T> *temp;
		temp = Head;
		while (temp != nullptr){
		
			cout << temp->data << endl;
			temp = temp->next;

		}

	}
}

template<class T>
const T List<T>::front() const{
	if (Head != nullptr){
		return Head->data;
	}
	else{
		return -1;
		cout << "Head is null, Empty List." << endl;
	}
}

template<class T>
const T List<T>::back() const{
	if (Tail != nullptr){
		return Tail->data;
	}
	else{
		return -1;
		cout << "Tail is null, Empty List." << endl; 
	}
}

template<class T>
int List<T>::size() const{
	return count;
}

//removes front item from list
template<class T>
void List<T>::pop_front(){
    if (Head == nullptr) {
        //do nothing
        cout <<"Trying to pop from empty list"<<endl;
    }
    else{
        Node<T> *nodePtr = Head;
        Head = Head->next;
        delete nodePtr;
        count--;
    }
}
//removes item from back of list
template<class T>
void List<T>::pop_back(){
    if (Head == nullptr) {
        //do nothing
        cout <<"Trying to pop from empty list"<<endl;
    }
    else{
        Node<T> *nodePtr = Tail;
        Tail = Tail->prev;
        delete nodePtr;
        count--;
    }
}







/////////////////////////
/*
Mergesort for list class
Provided by Mr. Hare. 
*/

template<class T>
void List<T>::sort()
{
	Sort(Head);
	
	//Placing tail and end of newly merged list
	Node<T> *tmpNode = Head;
	Node<T> *prevNode = Head;
	while (tmpNode != nullptr){
		prevNode = tmpNode;
		tmpNode = tmpNode->next;
	}
	Tail = prevNode;
}

template<class T>
void List<T>::Sort(Node<T>*& H)
{
	Node<T> *P, *Q;

	if (H != nullptr && H->next != nullptr) // at least 2 items
	{
		Split(H, P, Q);
		if (P != nullptr && P->next != nullptr)
			Sort(P);
		if (Q != nullptr && Q->next != nullptr)
			Sort(Q);
		Merge(H, P, Q);
	}
}

template<class T>
void List<T>::Split(Node<T>*& H, Node<T>*& P, Node<T>*& Q)
{
	Node<T>* tmp;
	int size = 0;

	tmp = H;
	while (tmp != nullptr)
	{
		size++;
		tmp = tmp->next;
	}
	size /= 2;
	tmp = H;
	for (int k = 0; k < size - 1; k++)
		tmp = tmp->next;
	P = H; // NOT P = Head; !!!!!!! 
	Q = tmp->next;
	tmp->next = nullptr;
}


template<class T>
void List<T>::Merge(Node<T>*& H, Node<T>*& P, Node<T>*& Q)
{
	Node<T> *LastMerged;

	if (P->data <= Q->data)
	{
		H = P;
		P = P->next;
	}
	else
	{
		H = Q;
		Q = Q->next;
	}
	LastMerged = H;
	while (P != NULL && Q != NULL)
	{
		if (P->data <= Q->data)
		{
			LastMerged->next = P;
			LastMerged = P;
			P = P->next;
		}
		else
		{
			LastMerged->next = Q;
			LastMerged = Q;
			Q = Q->next;
		}
	}
	if (P == NULL)
		LastMerged->next = Q;
	else{
		LastMerged->next = P;
	}

	

	
}