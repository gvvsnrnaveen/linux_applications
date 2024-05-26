/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 *
 * Author: Naveen Kumar Gutti
 */

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
