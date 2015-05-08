#pragma once

#include <iostream>
#include "List.h"
using namespace std; 

class Receiver{

public:
	Receiver(){ ; } //do nothing
	void setup();
	bool has_data();
	Pkt send();
	void receive(const Pkt & thePkt);
	void process();

//private:
	List<Pkt> rInbox, rAckBox;
	int LastAckNumber;
	bool FpktReceived;


};

void Receiver::setup(){
	//prep rAckBox to hold a zero pkt
	Pkt firstActPkt;
	firstActPkt.seqNum = 0; 
	firstActPkt.type = 'A';
	rAckBox.push_back(firstActPkt); 
	
	FpktReceived = false; 

}

//does outgoing AckBox have pkts?
bool Receiver::has_data(){
	return (rAckBox.size() > 0);
}

//pop and send pks from rAckBox
Pkt Receiver::send(){
	Pkt pktToReturn;
	pktToReturn = rAckBox.front();
	rAckBox.pop_front(); //remoing packet 
	cout << "Receiver::receive(): Sending ACK Packet: " << pktToReturn.seqNum << endl;
	return pktToReturn;
}

//if not corrupted add to rInbox
void Receiver::receive(const Pkt & thePkt){
	if (thePkt.seqNum != -1){
		rInbox.push_back(thePkt);
		
	}
	else{
		cout << "Receiver::receive(): Dropping courrupted Packet." << endl;
	}
}

//process just arrived pkts and put them in ack
void Receiver::process(){
	rInbox.sort(); //lower case sort is primary merge sort
	
	cout << "Receiver::process(): Sorting Incoming Packets" << endl;
	
	//updating ACK pkts and popping them from rINbox
	while (rInbox.size() > 0){
		if (rInbox.front().seqNum == LastAckNumber + 1){ //found next pkt in sequence
			
			//checking to see if it's the last pkt
			if (rInbox.front().type == 'F'){
				FpktReceived = true;
				cout << "Receiver::process(): Final Packet Found" << endl;
			}
			LastAckNumber++;
			rInbox.pop_front();
		}
		else{ //still waiting on another packet
			break;
		}
	}
	//prepping newAckPkt
	Pkt NewAckPkt;

	//check to see if Final pkt received
	if (FpktReceived == true){
		NewAckPkt.seqNum = LastAckNumber;
		NewAckPkt.type = 'F';
	}
	else{
		NewAckPkt.seqNum = LastAckNumber;
		NewAckPkt.type = 'A';
	}
	
	// adding newpkt to rAckBox
	rAckBox.push_back(NewAckPkt);
	cout << "Receiver::process(): Adding to AckList " << NewAckPkt;

	

}
