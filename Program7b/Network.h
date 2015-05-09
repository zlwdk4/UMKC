#pragma once

#include "List.h"
#include "Sender.h"
#include "Receiver.h"
#include <vector>
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
	vector<Pkt> DpktsfromSender, AckPktsfromReceiver;
};

//Pick up from Sender
void Network::pick_up(Sender & theSender){
	
	//while sender has Pkts and we have less than 4 in the vector pick up.
	cout<<endl << "Network::pick_up(): Picking up from Sender" << " -->" << endl;
	
	while (theSender.outPkts.size() > 0 && DpktsfromSender.size() < 4){
		DpktsfromSender.push_back(theSender.send()); //grab Data Pkt from Sender and put in Vector
		cout << "Network::pick_up(): Picked up Pkt: #" << DpktsfromSender.back().seqNum << " from Sender" << endl;
	}
	cout << "---> end delivery" << endl<<endl;
	//add dropping stuff later
}

//Pick up from Receiver
void Network::pick_up(Receiver & theRec){
	
	AckPktsfromReceiver.push_back(theRec.send()); //grab Data Pkt from Receiver and put in Vector
	cout << "Network::pick_up(): Picked up Pkt: #"<< AckPktsfromReceiver.back().seqNum << " from Receiver" << endl;

}

//Deliver to Sender
void Network::deliver(Sender& theSender){
	cout << "Network::pick_up(): Delivering to Sender" << endl;
	while (AckPktsfromReceiver.size() > 0){
		theSender.inPkts.push_back(AckPktsfromReceiver.back()); //deliver one packet from ACK vector
		AckPktsfromReceiver.pop_back(); //delete delivered packet
	}
}

//Deliver to Receiver
void Network::deliver(Receiver& theRec){
	cout << endl << "Network::Deliver(): Delivering to Receiver" << " -->"<< endl;
	
	while (DpktsfromSender.size() > 0){
		theRec.rInbox.push_back(DpktsfromSender.back()); //deliver one packet from ACK vector
		cout << "Network::Deliver(): Delivering Pkt: #" << DpktsfromSender.back().seqNum << " to Receiver" << endl;
		DpktsfromSender.pop_back(); //delete delivered packet
		
	}
	cout << "---> end delivery" << endl;
}
