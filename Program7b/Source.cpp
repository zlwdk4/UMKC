#include <iostream>
#include <fstream>
#include "List.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Sender.h"
using namespace std;




//git random comment
int main(){
	
	//List<Pkt> Packets; 
	////Packets.printList();
	//Pkt bob;
	//Packets.push_back(bob); 
	//
	
	//
	
	Sender theSender; 

	theSender.setup(5); 
	
	//testing comparison operator for structs
	cout << (theSender.outPkts.Head->data <= theSender.outPkts.Head->next->data);

	system("pause");
	return 0;
}