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
	
	//Packets.push_back(bob); 
	
	Sender theSender; 
	 

	theSender.setup(11); 
	
	theSender.process(); 

	cout << theSender.outPkts.back()<<endl;
	cout << theSender.outPkts.front() << endl;
	cout << theSender.outPkts.size()<<endl;


	system("pause");
	return 0;
}