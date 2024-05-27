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
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct queue {
	void *buffer;
	void *front;
	void *rear;
	size_t element_size;
	int queue_len;
	int number_of_elements;
	bool overflow;
};

struct queue* init_queue(size_t element_size, int queue_len){
	struct queue *ptr;
	ptr = (struct queue*)malloc(sizeof(struct queue));
	if(ptr == NULL)
		return NULL;
	ptr->buffer = malloc(element_size * queue_len);
	memset(ptr->buffer, 0, element_size * queue_len);
	ptr->queue_len = queue_len;
	ptr->element_size = element_size;
	ptr->number_of_elements = 0;
	ptr->front = ptr->buffer;
	ptr->rear = ptr->buffer;
}

bool is_queue_empty(struct queue *q){
	if(q->number_of_elements == 0)
		return true;
	return false;
}

bool is_queue_full(struct queue *q){
	if(q->number_of_elements == q->queue_len)
		return true;
	return false;
}

void enqueue(struct queue *q, void *value){
	if (q == NULL)
		return;
	if(is_queue_full(q)){
		printf("Cannot insert %d as queue is full\n", *(int*)value);
		return;
	}
	if(q->number_of_elements < q->queue_len && q->overflow == 1){
		q->front = q->buffer;
		q->overflow = 0;
	}
	memcpy(q->front, value, q->element_size);
	q->front += q->element_size;
	q->number_of_elements++;
	if(q->number_of_elements >= q->queue_len){
		q->overflow = 1;
	}
}

void* dequeue(struct queue *q){
	if(q == NULL)
		return NULL;
	if(is_queue_empty(q)){
		printf("Queue is empty, cannot dequeue\n");
		return NULL;
	}
	void *ptr = NULL;
	q->number_of_elements--;
	ptr = q->rear;
	q->rear += q->element_size;
	if(q->rear >= q->buffer + q->queue_len * q->element_size)
		q->rear = q->buffer;
	return ptr;
}

void print_all_elements(struct queue *q){
	int i = 0;
	printf("Elements: ");
	for(i=0; i < q->number_of_elements; i++){
		printf("%d ", *(int*)(q->buffer + i * q->element_size));
	}
	printf("\n");
}


void destroy_queue(struct queue *q){
	free(q->buffer);
	free(q);
}

int main(int argc, char **argv){
	struct queue *q;
	int value = 0;
	int i = 0;
	void *ptr;
	q = init_queue(sizeof(int), 10);
	if(q == NULL){
		printf("Queue init failed\n");
		return -1;
	}

	printf("Is queue empty: %d, Is queue full: %d, number_of_elements: %d\n", is_queue_empty(q), is_queue_full(q), q->number_of_elements);

	printf("Inserting first set of data\n");
	for(i = 0; i < 11; i++){
		value = 10 * i;
		printf("inserting: %d\n", value);
		enqueue(q, &value);
	}
	printf("\n\n");

	printf("Is queue empty: %d, Is queue full: %d, number_of_elements: %d\n", is_queue_empty(q), is_queue_full(q), q->number_of_elements);
	printf("removing first 5 elements\n");
	for(i = 0; i < 5; i++){
		ptr = dequeue(q);
		if(ptr != NULL)
			printf("Removing: %d\n", *(int*)ptr);
	}
	printf("\n\n");

	printf("Is queue empty: %d, Is queue full: %d, number_of_elements: %d\n", is_queue_empty(q), is_queue_full(q), q->number_of_elements);

	printf("inserting second set of data\n");
	for(i = 0; i < 10; i++){
		value = 100 * i;
		printf("inserting: %d\n", value);
		enqueue(q, &value);
	}
	printf("\n\n");

	printf("Removing all data in queue\n");
	for(i = 0; i < 10; i++){
		ptr = dequeue(q);
		if(ptr != NULL)
			printf("Removing: %d\n", *(int*)ptr);
	}


	if(!is_queue_empty(q))
		print_all_elements(q);


	destroy_queue(q);
	return 0;
}
