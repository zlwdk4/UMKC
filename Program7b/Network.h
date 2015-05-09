#pragma once

#include "List.h"
#include <list>
#include "Sender.h"
#include "Receiver.h"
#include <vector>
#include "Node.h"
#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <fstream>

using namespace std; 


class Network{
public:
	Network(){ ; } //nothing to setup
	void pick_up(Sender & theSender);
	void pick_up(Receiver & theRec);
	void deliver(Sender& theSender);
	void deliver(Receiver& theRec);
	void setFout(ofstream* out){ fout = out;}

//private:
	list<Pkt> DpktsfromSender, AckPktsfromReceiver;
	ofstream *fout;
};


//Pick up from Sender

void Network::pick_up(Sender & theSender){
	
	//while sender has Pkts and we have less than 4 in the vector pick up.
	*fout<<endl << "Network::pick_up(): from Sender Pkts -->#";
	
	while (theSender.outPkts.size() > 0 && DpktsfromSender.size() < 4){
		
		DpktsfromSender.push_back(theSender.send()); //grab Data Pkt from Sender and put in Vector
		*fout  << DpktsfromSender.back().seqNum << ", ";
	}
	*fout << "--> end pickup" << endl<<endl;
	
	//3% Chance Corrupt Pkt
	if (rand() % 100 <3){
		*fout << "@Network::pick_up(): Corrupting Data Pkt: " << DpktsfromSender.front().seqNum << endl;
		DpktsfromSender.front().seqNum = -1; 
	}

	//33% chance shuffle
	if (rand() % 100 < 33){
		swap(DpktsfromSender.front(), DpktsfromSender.back());
		*fout << "@Network::pick_up(): shuffling Pkts: " << endl;
	}

	//2%chance to drop
	if (rand() % 100 < 2){
		DpktsfromSender.pop_back();
		*fout << "@Network::pick_up(): dropping 1 Pkt: " << endl;
	}

}

//Pick up from Receiver
void Network::pick_up(Receiver & theRec){
	
	AckPktsfromReceiver.push_back(theRec.send()); //grab Data Pkt from Receiver and put in Vector
	*fout << "Network::pick_up(): Picked up Pkt: #"<< AckPktsfromReceiver.back().seqNum << " from Receiver" << endl;

}

//Deliver 1 pkt to Sender
void Network::deliver(Sender& theSender){
	
		theSender.inPkts.push_back(AckPktsfromReceiver.back()); //deliver one packet from ACK vector
		*fout << "Network::Deliver(): Delivering pkt " << AckPktsfromReceiver.front().seqNum << " to Sender" << endl;
		AckPktsfromReceiver.pop_front(); //delete delivered packet
	
}

//Deliver up tp 4 to Receiver
void Network::deliver(Receiver& theRec){
	*fout << endl << "Network::Deliver(): to Receiver Pkts -->#";
	
	while (DpktsfromSender.size() > 0){
		theRec.rInbox.push_back(DpktsfromSender.front()); //deliver one packet from ACK vector
		*fout << DpktsfromSender.front().seqNum << " Type:" << DpktsfromSender.front().type << ", ";
		DpktsfromSender.pop_front(); //delete delivered packet
		
	}
	*fout << "--> end delivery" << endl;
}
