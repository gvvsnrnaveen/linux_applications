#include <iostream>
#include "msgq_manager.h"

struct mydata{
	int a;
	int b;
	int c;
};

int main(int argc, char **argv){
	int result = 0;
	struct mydata obj = {
		.a = 10,
		.b = 20,
		.c = 30
	};
	naveen::MsgqManager *msgqManager = new naveen::MsgqManager("/mymsgq", 10, sizeof(struct mydata));
	std::cout << "Message queue created" << std::endl;
	result = msgqManager->msgqSend((const char*)&obj, sizeof(struct mydata), 1);
	if(result < 0){
		std::cout << "Failed to send the message over message queue" << std::endl;
		goto cleanup;
	}
	std::cout << "message sent" << std::endl;
	msgqManager->closeMsgq();
cleanup:
	sleep(5);
	msgqManager->destroyMsgq();
	delete msgqManager;
	return 0;
}
