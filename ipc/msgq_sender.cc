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
