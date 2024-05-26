#include "msgq_manager.h"

naveen::MsgqManager::MsgqManager(){

}

naveen::MsgqManager::MsgqManager(std::string msgqName, int msgqLength, size_t elementSize){
	struct mq_attr attr;
	memset(&attr, 0, sizeof(struct mq_attr));
	attr.mq_flags = 0;
	attr.mq_maxmsg = msgqLength;
	attr.mq_msgsize = elementSize;
	attr.mq_curmsgs = 0;

	struct rlimit rlim;
	memset(&rlim, 0, sizeof(struct rlimit));
	rlim.rlim_cur = RLIM_INFINITY;
	rlim.rlim_max = RLIM_INFINITY;
	setrlimit(RLIMIT_MSGQUEUE, &rlim);
	this->mqdt = mq_open(msgqName.c_str(), O_RDWR | O_CREAT, 0666, &attr);
	if(mqdt == -1){
		std::cout << "Failed to create message queue: " << msgqName << std::endl;
		exit(EXIT_FAILURE);
	}
	this->msgqName = msgqName;
}

naveen::MsgqManager::~MsgqManager(){
}

int naveen::MsgqManager::openMsgq(std::string msgqName){
	this->msgqName = msgqName;
	this->mqdt = mq_open(this->msgqName.c_str(), O_RDWR);
	// use the below to open in non blocking mode
	// need to handle the errors in application layer
	//this->mqdt = mq_open(this->msgqName.c_str(), O_RDWR | O_NONBLOCK);
	if(this->mqdt == (mqd_t)-1)
		return -1;
	return 0;
}

int naveen::MsgqManager::msgqSend(const char *data, size_t len, int timeout){
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	ts.tv_sec += (timeout + 1);
	len = mq_timedsend(this->mqdt, data, len, 0, &ts);
	if(len == -1){
		std::cout << "MQ send error: " << errno << std::endl;
		return -1;
	}
	return 0;
}

int naveen::MsgqManager::msgqRecv(char *data, size_t len, int timeout){
	struct timespec ts;
	if(timeout){
		clock_gettime(CLOCK_REALTIME, &ts);
		ts.tv_sec += timeout;
		len = mq_timedreceive(this->mqdt, data, len, 0, &ts);
	} else {
		len = mq_receive(this->mqdt, data, len, NULL);
	}
	if(len < 0){
		return -1;
	}
	return len;

}

void naveen::MsgqManager::closeMsgq(){
	mq_close(this->mqdt);
}

void naveen::MsgqManager::destroyMsgq(){
	mq_unlink(this->msgqName.c_str());
}
