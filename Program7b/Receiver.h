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
	void setFout(ofstream* out){ fout = out; }

//private:
	List<Pkt> rInbox, rAckBox;
	int LastAckNumber;
	bool FpktReceived;
	ofstream *fout;

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
	*fout << "Receiver::Send(): Sending ACK Packet: " << pktToReturn.seqNum << endl;
	return pktToReturn;
}

//if not corrupted add to rInbox
void Receiver::receive(const Pkt & thePkt){
	if (thePkt.seqNum != -1){
		rInbox.push_back(thePkt);
		
	}
	else{
		*fout << "Receiver::receive(): Dropping courrupted Packet." << endl;
	}
}

//process just arrived pkts and put them in ack
void Receiver::process(){
	rInbox.sort(); //lower case sort is primary merge sort
	
	*fout << "Receiver::process(): LastAck: "<< LastAckNumber<< " Sorting Incoming Pkts --> #";
	
	//updating ACK pkts and popping them from rINbox
	while (rInbox.size() > 0){
		if (rInbox.back().type == 'F'){
			FpktReceived = true;
			*fout << "Receiver::process(): Final Packet Found" << endl;
			rInbox.pop_front();
			break;
		}
		else{

			if (rInbox.front().seqNum == LastAckNumber + 1){ //found next pkt in sequence
				*fout << rInbox.front().seqNum << "Type:" << rInbox.front().type << ", ";
				//checking to see if it's the last pkt			
				LastAckNumber++;
				rInbox.pop_front();
			}

			//found duplicate
			if (rInbox.front().seqNum <= LastAckNumber){
				*fout << "Receiver::process(): Duplicate Pkt Found: Dropping: " << rInbox.front().seqNum << endl;
				rInbox.pop_front();
			}
			else{ //still waiting on another packet
				break;
			}
		}
	}
	*fout << "<--end" << endl;
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
	rAckBox.push_front(NewAckPkt);
	*fout << "Receiver::process(): Adding to AckList " << NewAckPkt;

	

}
