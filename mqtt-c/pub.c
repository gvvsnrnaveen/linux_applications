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
#include <mosquitto.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

struct mosquitto *mqtt;

#define SERVER_URL ""
#define TOPIC "test_topic_1"
#define MESSAGE "Welcome to MQTT Programming with libmosquitto"
#define USERNAME "test_user_1"
#define PASSWORD "Ready2wrk"

void on_log_callback(struct mosquitto *mqtt, void *userdata, int level, const char *str){
	printf("log: %s\n", str);
}

void on_connect_callback(struct mosquitto *mqtt, void *data, int reason_code){
	int result = 0;
	printf("connect callback: %d\n", reason_code);

	result = mosquitto_publish(mqtt, NULL, TOPIC, strlen(MESSAGE), MESSAGE, 0, 0);
	if(result != MOSQ_ERR_SUCCESS){
		printf("Failed to publish message\n");
	} else {
		printf("message sent\n");
	}

}

void on_publish_callback(struct mosquitto *mqtt, void *data, int mid){
	printf("publish callback: %d\n", mid);
	printf("disconnecting...\n");
	mosquitto_disconnect(mqtt);
}

void on_message_callback(struct mosquitto *mqtt, void *data, const struct mosquitto_message *msg){
	printf("message callback: %s, %d, %s\n", msg->topic, msg->qos, (char*)msg->payload);
}

int main(int argc, char **argv){
	int result = 0; 

	if(strlen(SERVER_URL) == 0){
		printf("Set the server url in SERVER_URL\n");
		return -1;
	}

	mosquitto_lib_init();

	mqtt = mosquitto_new(NULL, true, NULL);
	if(!mqtt){
		printf("Failed to create new mqtt object\n");
		mosquitto_lib_cleanup();
		return -1;
	}
	printf("Mosquitto object initialized\n");

	mosquitto_log_callback_set(mqtt, on_log_callback);
	mosquitto_connect_callback_set(mqtt, on_connect_callback);
	mosquitto_publish_callback_set(mqtt, on_publish_callback);
	mosquitto_message_callback_set(mqtt, on_message_callback);

	result = mosquitto_username_pw_set(mqtt, USERNAME, PASSWORD);
	if(result != MOSQ_ERR_SUCCESS){
		printf("Failed to set username and password: %d\n", result);
		mosquitto_lib_cleanup();
		return -1;
	}
	
	result = mosquitto_tls_insecure_set(mqtt, false);
	if(result != MOSQ_ERR_SUCCESS){
		printf("Failed to set tls_insecure to false\n");
		mosquitto_lib_cleanup();
		return -1;
	}

	result = mosquitto_tls_set(mqtt, NULL, "/etc/ssl/certs", NULL, NULL, NULL);
	if(result != MOSQ_ERR_SUCCESS){
		printf("Failed to set tls certificates\n");
		mosquitto_lib_cleanup();
		return -1;
	}

	result = mosquitto_tls_opts_set(mqtt, 1, "tlsv1.3", NULL);
	if(result != MOSQ_ERR_SUCCESS){
		printf("Failed to set tls version\n");
		mosquitto_lib_cleanup();
		return -1;
	}

	result = mosquitto_connect(mqtt, SERVER_URL, 8883, 60);
	if(result != MOSQ_ERR_SUCCESS){
		printf("Failed to connect\n");
		mosquitto_lib_cleanup();
		return -1;
	}


	mosquitto_loop_forever(mqtt, -1, 1);
cleanup:
	mosquitto_disconnect(mqtt);
	mosquitto_lib_cleanup();
	return 0;
}
