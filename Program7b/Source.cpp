#include <iostream>
#include <fstream>
#include "List.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;


int main(){


	/* initialize random seed: */
	int srand((NULL));
	int randomInt;
	

	List<int> Mylist, Mylist2;

	for (int i = 0; i < 4; i++){
		
		randomInt = rand() % 10 + 1; /* generate secret number between 1 and 10: */
		Mylist.push_front(randomInt);
	}
	//Mylist.push_front(1);
	//Mylist2.push_back(3);

	//Mylist.printList();
	//Mylist2.printList();

	//Mylist = Mylist2; 

	Mylist.printList();

	cout << "sorted: " << endl;

	Mylist.sort(); 
	Mylist.printList();

	cout << "Front: " << Mylist.front() << " and Back: " << Mylist.back() << " Size of List: " << Mylist.size() << endl;

	

	system("pause");
	return 0;
}