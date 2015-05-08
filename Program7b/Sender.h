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
	bool has_data() const;
	Pkt send();
	void process();
	
	bool finished();


//private:
	List<Pkt> outPkts, inPkts; //two list OUT queued up for outgoing packets and IN for ACK pkts
	int pktsToSend, pktsLeft;


};

//filling outgoing queue and preping incoming queue
void Sender::setup(int NPkts){

	//set variables to track number of packets left to send
	pktsToSend = NPkts; 
	pktsLeft = NPkts; 

	//prepping incoming queue with one acknowledge packet
	Pkt inTempPkt;
	inTempPkt.seqNum = 0;
	inTempPkt.type = 'A';
	inPkts.push_back(inTempPkt);

}
//check to see if outgoing list has data to send
bool Sender::has_data() const{
	if (outPkts.size() > 0)
		return true;
	else
		return false; 
}

//return the first packet in the list and deletes it
Pkt Sender::send(){
	Pkt pktToReturn;
	pktToReturn = outPkts.front();
	outPkts.pop_front(); 

	return pktToReturn; 
}
//Checks the last ACK in inPktList, checks outList and then fills outList with up to 10 packets
void Sender::process(){

	//if list OutGoing List is empty add one item
	if (outPkts.size() == 0){
		Pkt firstPkt;
		firstPkt.seqNum = 1;
		firstPkt.type = 'D';
		outPkts.push_back(firstPkt);
	}

	//checking last acknowledged pkt
	int LastAcked = inPkts.back().seqNum;

	cout << "Sender.process(): LastACKed == " << LastAcked << " queueing up 10 packets to send" << endl;

	//Check to see if we sent all packets if so prepare final
	if (inPkts.back().seqNum >= pktsToSend){
		cout << "Sender.process(): All Pkt send and Acknowledged Prepping Finish Pkt" << endl;
		Pkt newOutPkt; //create new pkt to add
		newOutPkt.seqNum = pktsToSend + 1;
		newOutPkt.type = 'F';
		inPkts.push_back(newOutPkt);
	}


	//if last ack is less than total need to send que up some more
	if (LastAcked < pktsToSend){

		//check outList is there less that 10 if so add and recheck
		if (outPkts.size() <= 4){

			int highestSeqNum = outPkts.back().seqNum; //high number currently in the que

			//not at end need to add more pkts & recheck
			while (outPkts.size() < 10){
				Pkt newOutPkt2; //create new pkt to add
				newOutPkt2.seqNum = highestSeqNum + 1;
				newOutPkt2.type = 'D';
				outPkts.push_back(newOutPkt2);
				highestSeqNum++;

				if (highestSeqNum > pktsToSend){
					break;
				}

			}
		}

	}
}


//checking to see if we've finished
bool Sender::finished(){
	if (inPkts.back().type == 'F')
		return true;
	else
		return false; 
}