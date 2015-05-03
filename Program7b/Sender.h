//Chris Walter
//Program7 Sender H file
#pragma once

#include <iostream>
using namespace std;
#include "List.h"


class Sender{
public:
	Sender(){ ; } //do nothing lists are already initialized to safe values
	void setup(int NPkts);
	Pkt send();

//private:
	List<Pkt> outPkts, inPkts; //two list OUT queued up for outgoing packets and IN for ACK pkts
	int pktsToSend, pktsLeft;


};

//filling outgoing queue and preping incoming queue
void Sender::setup(int NPkts){

	//filling outgoing queue with data packets
	for (int i = 1; i <= NPkts; i++){ 
		Pkt tmpPacket; 
		tmpPacket.seqNum = i; 
		
		if (i == (NPkts - 1)){
			tmpPacket.type = 'F'; //final packet
		}
		else{
			tmpPacket.type = 'D';
		}
		outPkts.push_back(tmpPacket);
		

	}

	//prepping incoming queue with one acknowledge packet
	Pkt inTempPkt;
	inTempPkt.seqNum = 0;
	inTempPkt.type = 'A';
	inPkts.push_back(inTempPkt);

}

//return the first packet 
Pkt Sender::send(){
	Pkt pktToReturn;
	pktToReturn = outPkts.front();
	outPkts.pop_front(); 

	return pktToReturn; 
}