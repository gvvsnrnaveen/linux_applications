#include<iostream>
#include "shm_manager.h"
struct mydata {
	int a;
	int b;
	int c;
};

int main(int argc, char **argv){
	int result = 0;
	struct mydata *obj;
	naveen::SHMManager *shmManager = new naveen::SHMManager("/mysharedmemory");
	obj = (struct mydata*) shmManager->readFromShm(sizeof(struct mydata));
	if(!obj){
		std::cout << "failed to read from shared memory" << std::endl;
		goto cleanup;
	}
	std::cout <<"read from shared memory: " << obj->a << ", " << obj->b << ", " << obj->c << std::endl;
	free(obj);
cleanup:
	delete shmManager;
	return 0;
}
