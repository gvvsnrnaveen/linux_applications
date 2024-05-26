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
