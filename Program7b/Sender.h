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

//private:
	List<Pkt> outPkts, inPkts; //two list OUT queued up for outgoing packets and IN for ACK pkts


};

//filling outgoing queue
void Sender::setup(int NPkts){
	for (int i = 0; i < NPkts; i++){ //filling outgoing queue with data packets
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
}