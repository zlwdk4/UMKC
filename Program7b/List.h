//Chris Walter
//Program7
///List Class .h File -------->
//includes struct and merge sort




#pragma once
#include <iostream>
using namespace std;
#include "Node.h"

template<class T>
class List
{
public:
	List(){ count = 0; Head = Tail = nullptr; }
	~List(){ clear(); } //destructor 
	const List<T>& operator=(const List<T>& rhs);
	

	//Methods
	void printList();
	void push_front(const T& item);
	void push_back(const T& item);
    void push_ordered(const T& item);
	void clear();
	void sort(); //merge sort
	void printList2();
	const T front() const; 
	const T back() const;
	int size() const;
    void pop_front();
    void pop_back();
    bool isEmpty();
	void setFout(ofstream* out){ fout = out; }
	
 


	//Merge Sort Method 
	//Credit goes to Mr. Hare for the implementation
	void Sort(Node<T>*& H); 
	void Split(Node<T>*& H, Node<T>*& P, Node<T>*& Q);
	void Merge(Node<T>*& H, Node<T>*& P, Node<T>*& Q);



	int count;
	Node<T> *Head, *Tail;
	ofstream *fout;



};

//implementation ---------->

template<class T>
void List<T>::printList(){
	if (Head != nullptr){

		Node<T> *tmpNode = Head;
		int PrintCount = 1;
		int tot = this->size();
		*fout << "Head:" << Head << " " << Head->data << endl;
		while (tmpNode != nullptr) { 
			*fout << "Node:"<< PrintCount<<"/"<<tot << tmpNode->data;
			*fout << "PrevPtr:" << tmpNode->prev << " NxtPtr:" << tmpNode->next << " Self:" << tmpNode<< endl;
			tmpNode = tmpNode->next;
			PrintCount++;
		}
		*fout << "Tail:" << Tail<< " " << Tail->data<<endl;
	}
	if (Head == nullptr){
		*fout << "Empty List."<<endl;
	}
	
}


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

//adding to an ordered list
template<class T>
void List<T>::push_ordered(const T& item){
    if (item <= Head->data) { //put in front
        push_front(item);
        count++;
    }
    if (item >= Tail->data) { //put in back
        push_back(item);
        count++;
    }
    else{ //find correct location
        Node<T> *tmpNode = Head;
        while (item >= tmpNode->data) {
            tmpNode = tmpNode->next;
        }
        //found location in front of insertion site
        Node<T> *InsertionNode = new Node<T>(item); //new node is read for insertion
        tmpNode->prev->next = InsertionNode; //setttng prev node to point at new node
        InsertionNode->prev = tmpNode->prev; //new node is pointing at node behind it
        InsertionNode->next = tmpNode; //new node is pointing at node in front
        tmpNode->prev = InsertionNode; //front node is pointing at previous node
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

//print List
template<class T>
void List<T>::printList2(){

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
	//else{
	//	cout << "List<T>::front(): Head is null, Empty List." << endl;
	//	//return -1;
	//	
	//}
}

template<class T>
const T List<T>::back() const{
	if (Tail != nullptr){
		return Tail->data;
	}
	//else{
	//	//return -1;
	//	cout << "List<T>::back():Tail is null, Empty List." << endl; 
	//}
}

template<class T>
int List<T>::size() const{
	return count;
}

//removes front item from front of list
template<class T>
void List<T>::pop_front(){
    if (Head == nullptr) {
        //do nothing
        //cout <<"List<T>::pop_front(): Trying to pop from empty list"<<endl;
    }
    else{
		//Popping from list with more than 1 node
		if (Head->next != nullptr){
			Node<T> *nodePtr = Head;
			Head = Head->next;
			Head->prev = nullptr;
			delete nodePtr;
			count--;
		}

		//popping last item from list
		else{
			Node<T> *nodePtr = Head;
			Head = nullptr;
			Tail = nullptr;
			delete nodePtr; 
			count = 0; 
		}
       
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
		Tail->next = nullptr;
        delete nodePtr;
        count--;
    }
}

template<class T>
bool List<T>::isEmpty(){
    if (Head == nullptr) {
        return true;
    }
    else{
        return false;
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
	//don't sort if only one item
	if (this->size() < 2){
		//do nothing
	}
	
	else{
	Sort(Head);
	
	if (Head != nullptr){
		//Placing tail and end of newly merged list 
		Head->prev = nullptr; //cleaning first prev
		Node<T> *tmpNode = Head;
		Node<T> *prevNode = Head;

		while (tmpNode->next != nullptr){
			prevNode = tmpNode;
			tmpNode = tmpNode->next;
			tmpNode->prev = prevNode; //setting all prev ptrs correctly
		}
		Tail = prevNode->next;
		}
	}

	
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

///structure for Packets
///structure for Packets
struct Pkt {
	char type;
	int seqNum;

	bool operator<=(const Pkt& rhs) const{
		return (seqNum <= rhs.seqNum);
	}

	bool operator<(const Pkt& rhs) const {
		return (seqNum < rhs.seqNum);
	}

	bool operator>(const Pkt& rhs) const {
		return (seqNum > rhs.seqNum);
	}

	bool operator>=(const Pkt& rhs) const {
		return (seqNum >= rhs.seqNum);
	}

	bool operator==(const Pkt& rhs) const {
		return (seqNum == rhs.seqNum);
	}

	bool operator!=(const Pkt& rhs) const {
		return (seqNum != rhs.seqNum);
	}

	friend ostream& operator<<(ostream & out, const Pkt & thePkt){
		out << "Pkt Number: " << thePkt.seqNum << " Type: " << thePkt.type << endl;
		return out;
	}

};