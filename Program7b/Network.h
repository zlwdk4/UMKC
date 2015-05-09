#pragma once

#include "List.h"
#include "Sender.h"
#include "Receiver.h"
#include <vector>

#include "Node.h"
#include <iostream>
using namespace std; 


class Network{
public:
	Network(){ ; } //nothing to setup
	void pick_up(Sender & theSender);
	void pick_up(Receiver & theRec);
	void deliver(Sender& theSender);
	void deliver(Receiver& theRec);

private:
	List<Pkt> DpktsfromSender, AckPktsfromReceiver;
};

//Pick up from Sender
void Network::pick_up(Sender & theSender){
	
	//while sender has Pkts and we have less than 4 in the vector pick up.
	cout<<endl << "Network::pick_up(): from Sender Pkts -->#";
	
	while (theSender.outPkts.size() > 0 && DpktsfromSender.size() < 4){
		
		DpktsfromSender.push_back(theSender.send()); //grab Data Pkt from Sender and put in Vector
		cout  << DpktsfromSender.back().seqNum << ", ";
	}
	cout << "--> end pickup" << endl<<endl;
	//add dropping stuff later
}

//Pick up from Receiver
void Network::pick_up(Receiver & theRec){
	
	AckPktsfromReceiver.push_back(theRec.send()); //grab Data Pkt from Receiver and put in Vector
	cout << "Network::pick_up(): Picked up Pkt: #"<< AckPktsfromReceiver.back().seqNum << " from Receiver" << endl;

}

//Deliver 1 pkt to Sender
void Network::deliver(Sender& theSender){
	
		theSender.inPkts.push_back(AckPktsfromReceiver.back()); //deliver one packet from ACK vector
		cout << "Network::Deliver(): Delivering pkt " << AckPktsfromReceiver.front().seqNum << " to Sender" << endl;
		AckPktsfromReceiver.pop_front(); //delete delivered packet
	
}

//Deliver up tp 4 to Receiver
void Network::deliver(Receiver& theRec){
	cout << endl << "Network::Deliver(): to Receiver Pkts -->#";
	
	while (DpktsfromSender.size() > 0){
		theRec.rInbox.push_back(DpktsfromSender.front()); //deliver one packet from ACK vector
		cout << DpktsfromSender.front().seqNum << " Type:" << DpktsfromSender.front().type << ", ";
		DpktsfromSender.pop_front(); //delete delivered packet
		
	}
	cout << "--> end delivery" << endl;
}
