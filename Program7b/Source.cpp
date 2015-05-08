#include <iostream>
#include <fstream>
#include "List.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Sender.h"
#include "Receiver.h"
using namespace std;




//git random comment
int main(){
	
	//List<Pkt> Packets; 
	////Packets.printList();
	
	//Packets.push_back(bob); 
	/*
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
	
	*/

	Receiver theRec;
	Pkt pkt1;
	pkt1.seqNum = 1;
	pkt1.type = 'D';

	Pkt pkt2;
	pkt2.seqNum = 2;
	pkt2.type = 'D';

	Pkt pkt3;
	pkt3.seqNum = 3;
	pkt3.type = 'F';


	theRec.setup();
	cout << theRec.rAckBox.front();

	theRec.receive(pkt1);
	theRec.receive(pkt2);

	theRec.process();
	

	
	theRec.receive(pkt3);

	theRec.send();
	cout << theRec.rAckBox.front();
	cout << theRec.rAckBox.back();

	theRec.process();

	system("pause");
	return 0;
}