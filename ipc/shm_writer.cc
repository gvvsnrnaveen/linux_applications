#include<iostream>
#include "shm_manager.h"
struct mydata {
	int a;
	int b;
	int c;
};

int main(int argc, char **argv){
	int result = 0;
	struct mydata obj = {
		.a = 10000,
		.b = 500,
		.c = 100
	};
	naveen::SHMManager *shmManager = new naveen::SHMManager("/mysharedmemory");
	result = shmManager->writeToShm(&obj, sizeof(struct mydata));
	if(result < 0){
		std::cout << "failed to write to shared memory" << std::endl;
		goto cleanup;
	}
	std::cout <<"written to shared memory" << std::endl;
cleanup:
	delete shmManager;
	return 0;
}
