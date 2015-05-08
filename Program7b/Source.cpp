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

	Pkt newPkt1;
	newPkt1.seqNum = 12;
	newPkt1.type = 'A';

	while (theSender.finished() == false){
		
		theSender.process();

		theSender.inPkts.push_back(newPkt1);
		cout << theSender.outPkts.back();
		system("pause");
		theSender.process();
	}
	

	system("pause");
	return 0;
}