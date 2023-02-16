#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mosquitto.h>
#include <stdbool.h>
#include <string.h>
#include <json-c/json.h>
#include <time.h>

#define SERVER_URL ""
#define TOPIC "test_topic_1"
#define USERNAME "test_user_1"
#define PASSWORD "Ready2wrk"

struct mosquitto *mqtt;

void on_log_callback(struct mosquitto *mqtt, void *userdata, int level, const char *str){
	printf("message: %d, %s\n", level, str);
}

void on_connect_callback(struct mosquitto *mqtt, void *data, int reason_code){
	printf("connect callback: %d\n", reason_code);
	int result = 0;
	result = mosquitto_subscribe(mqtt, NULL, TOPIC, 0);
}

void on_subscribe_callback(struct mosquitto *mqtt, void *data, int mid, int qos, const int *granted_qos){
	printf("subscribe message id: %d\n", qos);
}

void on_message_callback(struct mosquitto *mqtt, void *obj, const struct mosquitto_message *msg){
	printf("%s, %d, %s\n", msg->topic, msg->qos, (char*)msg->payload);	
	struct json_object *main_obj = NULL;
	struct json_object *data_obj = NULL;
	main_obj = json_tokener_parse((char*)msg->payload);
	if(main_obj){
		if(json_object_object_get_ex(main_obj, "ssid", &data_obj)){
			printf("SSID: %s\n", json_object_get_string(data_obj));
		}
		json_object_put(obj);
	}
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
		printf("Failed to create mqtt object\n");
		return -1;
	}
	printf("Mosquitto object initialized\n");

	mosquitto_log_callback_set(mqtt, on_log_callback);
	mosquitto_connect_callback_set(mqtt, on_connect_callback);
	mosquitto_subscribe_callback_set(mqtt, on_subscribe_callback);
	mosquitto_message_callback_set(mqtt, on_message_callback);



	
	result = mosquitto_username_pw_set(mqtt, USERNAME, PASSWORD);
	if(result != MOSQ_ERR_SUCCESS){
		printf("Failed to set username and password\n");
		goto cleanup;
	}
	printf("username and password set\n");
	result = mosquitto_tls_insecure_set(mqtt, false);
	if(result != MOSQ_ERR_SUCCESS){
		printf("failed to set insecure flag\n");
		goto cleanup;
	}

	result = mosquitto_tls_set(mqtt, NULL, "/etc/ssl/certs", NULL, NULL, NULL);
	if(result != MOSQ_ERR_SUCCESS){
		printf("Failed to set tls\n");
		goto cleanup;
	}
	result = mosquitto_tls_opts_set(mqtt, 1, "tlsv1.3", NULL);
	if(result != MOSQ_ERR_SUCCESS){
		printf("Faield to set tls no verify\n");
		goto cleanup;
	}

	result = mosquitto_connect(mqtt, SERVER_URL, 8883, 60);
	if(result != MOSQ_ERR_SUCCESS){
		printf("Failed to connect to server\n");
		goto cleanup;
	}

	mosquitto_loop_forever(mqtt, -1, 1);

cleanup:
	mosquitto_destroy(mqtt);
	mosquitto_lib_cleanup();
	return 0;
}
