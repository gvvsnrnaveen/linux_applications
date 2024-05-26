#ifndef __SHM_MANAGER_H
#define __SHM_MANAGER_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <syslog.h>

namespace naveen {

	class SHMManager {

		public:
			SHMManager(std::string sharedMemoryName);
			~SHMManager();
			int writeToShm(void* dataptr, size_t dataSize);
			void* readFromShm(size_t dataSize);
			void destroyShm();

		private:
			std::string sharedMemoryName;
	};

}

#endif

