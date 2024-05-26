#include <iostream>
#include "msgq_manager.h"

struct mydata{
	int a;
	int b;
	int c;
};

int main(int argc, char **argv){
	int result = 0;
	struct mydata obj = {0};
	naveen::MsgqManager *msgqManager = new naveen::MsgqManager();
	msgqManager->openMsgq("/mymsgq");
	std::cout << "Message queue opened" << std::endl;
	result = msgqManager->msgqRecv((char*)&obj, sizeof(struct mydata), 2);
	if(result < 0){
		std::cout << "Failed to recv the message over message queue" << std::endl;
		goto cleanup;
	}
	std::cout << "message received: " << obj.a << ", " << obj.b << ", " << obj.c << std::endl;
	msgqManager->closeMsgq();
cleanup:
	delete msgqManager;
	return 0;
}
