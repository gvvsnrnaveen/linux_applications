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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <libipset/session.h>
#include <libipset/ipset.h>

struct ipset_session *session = NULL;
enum {
	NAV_IPSET_CREATE,
	NAV_IPSET_DESTROY,
	NAV_IPSET_ADD,
	NAV_IPSET_DEL,
	NAV_IPSET_FLUSH,
	NAV_IPSET_CHECK
};

void my_signal_handler(int sig){
	switch(sig){
		case SIGTERM:
		case SIGINT:
			if(session)
				ipset_session_fini(session);
			exit(0);
			break;
		default:
			break;
	}

}

void handle_ipset_create(struct ipset_session *session){
	char set_name[32] = {0};
	char set_type[32] = {0};
	const struct ipset_type *type = NULL;
	fprintf(stdout, "Enter set name: \n");
	scanf("%s", set_name);
	fprintf(stdout, "Enter set type: \n");
	scanf("%s", set_type);

	if(ipset_session_data_set(session, IPSET_SETNAME, set_name) < 0){
		fprintf(stderr, "%d,Failed to set the ipset setname to session\n", __LINE__);
		return;
	}

	ipset_session_data_set(session, IPSET_OPT_TYPENAME, set_type);

	type = ipset_type_get(session, IPSET_CMD_CREATE);
	if(!type){
		fprintf(stderr, "%d, Failed to get the ipset type\n", __LINE__);
		return;
	}
	if(ipset_session_data_set(session, IPSET_OPT_TYPE, type) < 0){
		fprintf(stderr, "%d, Failed to set the ipset type\n", __LINE__);
		return;
	}

	if(ipset_cmd(session, IPSET_CMD_CREATE, 0) < 0){
		fprintf(stderr, "%d, Error to perform create \n", __LINE__);
		return;
	}
	fprintf(stdout, "Create success\n");
	ipset_cache_del(NULL);

}

void handle_ipset_destroy(struct ipset_session *session){
	char set_name[32] = {0};
	fprintf(stdout, "Enter set name: \n");
	scanf("%s", set_name);
	if(ipset_session_data_set(session, IPSET_SETNAME, set_name) < 0){
		fprintf(stderr, "%d,Failed to set the ipset name to session\n", __LINE__);
		return;
	}
	if(ipset_cmd(session, IPSET_CMD_DESTROY, 0) < 0){
		fprintf(stderr, "%d, Error to destroy ipset\n", __LINE__);
		return;
	}
	fprintf(stdout, "Destroy success\n");
}

void handle_ipset_add_del(struct ipset_session *session, int cmd){
	int pre_ipset_cmd = 0;
	const struct ipset_type *type = NULL;
	char set_name[32] = {0};
	char ipaddr[32] = {0};

	if(cmd == NAV_IPSET_ADD){
		pre_ipset_cmd = IPSET_CMD_ADD;
	} else if(cmd == NAV_IPSET_DEL){
		pre_ipset_cmd = IPSET_CMD_DEL;
	} else {
		return;
	}

	fprintf(stdout, "Enter the setname:\n");
	scanf("%s", set_name);
	fprintf(stdout, "Enter the ipaddress: \n");
	scanf("%s", ipaddr);

	if(ipset_session_data_set(session, IPSET_SETNAME, set_name) < 0){
		fprintf(stderr, "%d: Failed to set ipset name\n", __LINE__);
		return;
	}
	type = ipset_type_get(session, pre_ipset_cmd);
	if(!type){
		fprintf(stderr, "%d: failed to get type\n", __LINE__);
		return;
	}

	if(ipset_parse_elem(session, type->last_elem_optional, ipaddr) < 0){
		fprintf(stderr, "%d: failed to parse ip addr\n", __LINE__);
		return;
	}
	if(ipset_cmd(session, pre_ipset_cmd, 0) < 0){
		fprintf(stdout, "failed to perform add/del\n");
		return;
	}

	fprintf(stdout, "Add/Del Success\n");
}

void handle_ipset_flush(struct ipset_session *session){
	char set_name[32] = {0};
	fprintf(stdout, "Enter the setname: \n");
	scanf("%s", set_name);
	if(ipset_session_data_set(session, IPSET_SETNAME, set_name) < 0){
		fprintf(stderr, "%d: Failed to set ipset name\n", __LINE__);
		return;
	}
	if(ipset_cmd(session, IPSET_CMD_FLUSH, 0) < 0){
		fprintf(stderr, "Flush failed\n");
	} else {
		fprintf(stdout, "Flush success\n");
	}
}

void handle_ipset_check(struct ipset_session *session){
	char set_name[32] = {0};
	char ipaddr[32] = {0};
	fprintf(stdout, "Enter the setname: \n");
	scanf("%s", set_name);
	fprintf(stdout, "Enter the ipaddr: \n");
	scanf("%s", ipaddr);
	if(ipset_session_data_set(session, IPSET_SETNAME, set_name) < 0){
		fprintf(stderr, "%d: Failed to set ipset name\n", __LINE__);
		return;
	}
	const struct ipset_type *type = NULL;
	type = ipset_type_get(session, IPSET_CMD_TEST);
	if(type == NULL){
		fprintf(stderr, "%d: Failed to set type\n", __LINE__);
		return;
	}

	if(ipset_parse_elem(session, type->last_elem_optional, ipaddr) < 0){
		fprintf(stderr, "%d: Failed to parse elem\n", __LINE__);
		return;
	}
	int result = 0;
	result = ipset_cmd(session, IPSET_CMD_TEST, 0);
	if(result < 0){
		fprintf(stderr, "%d: Failed to test check\n", __LINE__);
		return;
	}

	fprintf(stdout, "Success\n");
}

int main(int argc, char **argv){
	int option = 0; 

	ipset_load_types();
	fprintf(stdout, "Types success\n");

	session = ipset_session_init(NULL, NULL);
	if(!session){
		printf("Failed to init session\n");
		return -1;
	}

	fprintf(stdout, "Session success\n");

	signal(SIGINT, my_signal_handler);
	signal(SIGTERM, my_signal_handler);
	
	while(1){
		fprintf(stdout, "Enter your option: \n");
		fprintf(stdout, "%d - create\n", NAV_IPSET_CREATE);
		fprintf(stdout, "%d - destory\n", NAV_IPSET_DESTROY);
		fprintf(stdout, "%d - add\n", NAV_IPSET_ADD);
		fprintf(stdout, "%d - delete\n", NAV_IPSET_DEL);
		fprintf(stdout, "%d - flush\n", NAV_IPSET_FLUSH);
		fprintf(stdout, "%d - check\n", NAV_IPSET_CHECK);
		scanf("%d", &option);
		switch(option){
			case NAV_IPSET_CREATE:
				handle_ipset_create(session);
				break;
				
			case NAV_IPSET_DESTROY:
				handle_ipset_destroy(session);
				break;

			case NAV_IPSET_ADD:
			case NAV_IPSET_DEL:
				handle_ipset_add_del(session, option);
				break;
			case NAV_IPSET_FLUSH:
				handle_ipset_flush(session);
				break;

			case NAV_IPSET_CHECK:
				handle_ipset_check(session);
				break;
		}
		printf("\n\n");
	}

	ipset_session_fini(session);
	return 0;
}
