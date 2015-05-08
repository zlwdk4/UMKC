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

	cout << theSender.outPkts.front();
	cout << theSender.outPkts.back();
	cout << theSender.outPkts.size() << endl;

	theSender.outPkts.pop_front();
	theSender.outPkts.pop_front();
	theSender.outPkts.pop_front();
	theSender.outPkts.pop_front();
	theSender.outPkts.pop_front();
	theSender.outPkts.pop_front();
	theSender.outPkts.pop_front();

	Pkt newPkt;
	newPkt.seqNum = 5;
	newPkt.type = 'A';
	theSender.inPkts.push_back(newPkt);

	theSender.process();

	
	cout << theSender.outPkts.front();
	cout << theSender.outPkts.back();
	cout << theSender.outPkts.size() << endl;

	theSender.outPkts.pop_back();


	Pkt newPkt1;
	newPkt1.seqNum = 12;
	newPkt1.type = 'A';
	theSender.inPkts.push_back(newPkt1);
	theSender.process();

	cout << theSender.outPkts.front();
	cout << theSender.outPkts.back();
	cout << theSender.outPkts.size() << endl;

	

	

	system("pause");
	return 0;
}