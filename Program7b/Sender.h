//Chris Walter
//Program7 Sender H file
#pragma once

#include <iostream>
using namespace std;
#include "List.h"
#include <fstream>



class Sender{
public:
	Sender(){ ; } //do nothing lists are already initialized to safe values
	void setup(int NPkts);
	bool has_data() const;
	Pkt send();
	void process();
	bool finished();
	int getNpkts(){ return pktsToSend; }
	void setFout(ofstream* out){ fout = out; }

//private:
	List<Pkt> outPkts, inPkts; //two list OUT queued up for outgoing packets and IN for ACK pkts
	int pktsToSend, pktsLeft, LastAcked;
	bool cycleFinished; 
	ostream *fout;


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

	cycleFinished = false; 

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

	//updating last acked
	if (inPkts.size() != 0){
		LastAcked = inPkts.back().seqNum;
		if (inPkts.back().type == 'F'){
			cycleFinished = true; 
		}
		inPkts.pop_front(); //removing acked pkt
	}
	*fout << "Sender::process(): Last Acked: " << LastAcked << endl;
	
	//check if finshed
	if (LastAcked >= pktsToSend){
		
		Pkt newOutPkt; //create new pkt to add
		newOutPkt.seqNum = pktsToSend + 1;
		newOutPkt.type = 'F';
		outPkts.push_back(newOutPkt); //adding pkt to outgoing list
		*fout << "Sender.process(): All Pkts Sent and Acknowledged Prepping Finish Pkt"; 
		*fout << newOutPkt;
	}

	//not finshed need to add more pkts to outgoing
	else{
		if (outPkts.size() < 4){

				*fout << "Sender::process(): OutGoing List < 1 Adding --> # ";
				int outPktCounter = LastAcked;
				while (outPkts.size() < 10){
					if (outPktCounter >= pktsToSend){
						*fout << endl << "Sender::process(): Pkts queued == pkts requested." << endl;
						break;
					}
					Pkt newOutPkt2; //create new pkt to add
					newOutPkt2.seqNum = outPktCounter + 1;
					newOutPkt2.type = 'D';
					outPkts.push_back(newOutPkt2);
					outPktCounter++;
					*fout << newOutPkt2.seqNum << ", ";
				}
				*fout << "<--end" << endl;
			}		
		}
	
}

	

//checking to see if we've finished
bool Sender::finished(){
	if (cycleFinished==true){
		*fout << "Sender::finished(): Final Pkt Recieved and Confirmed" << endl;
		*fout << "Closing Connection..."<<endl;
		return true;
	}
	else{
		return false;
	}
}


