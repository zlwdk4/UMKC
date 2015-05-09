#include <iostream>
#include <fstream>
#include "List.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Sender.h"
#include "Receiver.h"
#include "Network.h"
using namespace std;




//git random comment
int main(){
	
	Sender sender;
	Receiver rec;
	Network network;
	int roundCnt = 0;
	sender.setup(5);
	rec.setup();
	while (sender.finished() == false){
		sender.process();
		rec.process();
		network.pick_up(sender);
		network.pick_up(rec);
		network.deliver(sender);
		network.deliver(rec);

		roundCnt++;
		cout << endl << "Round: " << roundCnt << " complete." << endl;
		cout << "Sender.OutPkt.Back(): " << sender.outPkts.back();
		cout << "Sender.Inpkts.Back(): "<<sender.inPkts.back();
		system("pause");
		
	}
	
	

	

	system("pause");
	return 0;
}