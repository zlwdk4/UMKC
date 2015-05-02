#include <iostream>
#include <fstream>
#include "List.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

//git random comment
int main(){


	/* initialize random seed: */
	int srand((NULL));
	int randomInt;
	

	List<int> Mylist, Mylist2;

	for (int i = 0; i < 7; i++){
		
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
    
    Mylist.pop_front();
    cout << "Popping front..."<<endl;
	cout << "Front: " << Mylist.front() << " and Back: " << Mylist.back() << " Size of List: " << Mylist.size() << endl<<endl;
    
    Mylist.printList();
    
    //Mylist.push_ordered(5);
    cout << endl << "Pushing Ordered:" <<endl;
    Mylist.printList();

	

	system("pause");
	return 0;
}