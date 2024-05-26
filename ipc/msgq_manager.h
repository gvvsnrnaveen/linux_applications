#ifndef __MSGQ_MANAGER_H
#define __MSGQ_MANAGER_H
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <mqueue.h>
#include <errno.h>
#include <ctype.h>
#include <stdbool.h>
#include <syslog.h>

#include <sys/types.h>
#include <sys/syscall.h>

namespace naveen {
	class MsgqManager {
		public:
			MsgqManager();
			MsgqManager(std::string msgqName, int msgqLength, size_t elementSize);
			~MsgqManager();
			mqd_t openMsgq(std::string msgqName);
			int msgqSend(const char *data, size_t len, int timeout);
			int msgqRecv(char *data, size_t len, int timeout);
			void closeMsgq();
			void destroyMsgq();
		private:
			std::string msgqName;
			mqd_t mqdt;
	};
}

#endif
