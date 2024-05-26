#include "shm_manager.h"

naveen::SHMManager::SHMManager(std::string sharedMemoryName){
	this->sharedMemoryName = sharedMemoryName;
}

naveen::SHMManager::~SHMManager(){

}

int naveen::SHMManager::writeToShm(void* dataptr, size_t elementSize){
	int shmId;
	shmId = shm_open(this->sharedMemoryName.c_str(), O_CREAT | O_RDWR , S_IRWXU | S_IRWXG | S_IRWXO);
	if(shmId == -1){
		std::cout << "Failed to open the shared memory" << std::endl;
		return -1;
	}
	int result = ftruncate(shmId, elementSize);
	if(result == -1){
		std::cout << "Failed to truncate shared memory" << std::endl;
		return -1;
	}
	void* ptr;
	ptr = mmap(0, elementSize, PROT_READ | PROT_WRITE, MAP_SHARED, shmId, 0);
	if(ptr  == (void*) -1){
		std::cout << "failed to mmap shared memory" << std::endl;
		return -1;
	}
	memcpy(ptr, dataptr, elementSize);
	munmap(ptr, elementSize);
	close(shmId);
	return 0;
}

void* naveen::SHMManager::readFromShm(size_t dataSize){
	struct stat buffer;
	int status;
	char shmName[256];
	sprintf(shmName,"/dev/shm/%s", this->sharedMemoryName.c_str());
	status = stat(shmName, &buffer);
	if(status == -1){
		return NULL;
	}
	int shmId = shm_open(this->sharedMemoryName.c_str(), O_RDWR , S_IRWXU |S_IRWXG | S_IRWXO);
	if(shmId == -1){
		return NULL;
	}
	int result = ftruncate(shmId, dataSize);
	void* ptr ;
	ptr = mmap(0, dataSize,PROT_READ | PROT_WRITE,MAP_SHARED,shmId,0);
	void* info;
	info = malloc(dataSize);
	memset(info, 0, dataSize);
	memcpy(info, ptr, dataSize);
	munmap(ptr, dataSize);
	close(shmId);
	return info;
}

void naveen::SHMManager::destroyShm(){
	shm_unlink(this->sharedMemoryName.c_str());
}


