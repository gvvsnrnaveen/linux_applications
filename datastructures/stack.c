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

struct stack {
	void *buffer;
	size_t element_size;
	unsigned int stack_len;
	unsigned int number_of_elements;
	void *stack_ptr;
};

struct stack* init_stack(size_t element_size, unsigned int stack_len){
	struct stack* p = malloc(sizeof(struct stack));
        if(p == NULL)
		return NULL;

	// allocate stack buffer
	p->buffer = malloc(element_size * stack_len);
	if(p == NULL){
		return NULL;
	}
	memset(p->buffer, 0, element_size * stack_len);

	// store the element_size, stack_len and point the stack_ptr to start of buffer
	p->element_size = element_size;
	p->stack_len = stack_len;
	p->stack_ptr = p->buffer;
	p->number_of_elements = 0;
	return p;
}

void push_element(struct stack *s, void *element){
	if(s == NULL)
		return;

	memcpy(s->stack_ptr, element, s->element_size);
	s->number_of_elements++;
	if(s->number_of_elements < s->stack_len){
		s->stack_ptr += s->element_size;
	} else {
		printf("Stack full\n");
	}
}

void* pop_element(struct stack *s){
	if(s == NULL)
		return NULL;
	if(s->number_of_elements == 0){
		printf("Stack empty\n");
		return NULL;
	}
	{
		void *ptr;
		ptr = s->stack_ptr; 
		s->number_of_elements--;
		if(s->number_of_elements != 0)
			s->stack_ptr -= s->element_size;
		return ptr;
	}
}

void print_stack_elements(struct stack *p){
	if(p == NULL)
		return;
	if(p->stack_ptr == p->buffer){
		printf("Stack empty\n");
	}
	{
		int i = 0, j = 0;
		void *ptr = p->buffer;
		for(i = 0; i < p->number_of_elements; i++){
			for(j=0; j<p->element_size; j++){
				printf("0x%02x ", *(unsigned char*)(ptr + j));
			}
			printf("\n");
			ptr += p->element_size;
		}
	}
}

int main(int argc, char **argv){
	struct stack *s;
	void *ptr; 
	int i = 0;
	s = init_stack(sizeof(int), 10);
	if(s == NULL){
		printf("Failed to create stack\n");
		return -1;
	}

	for(i=0; i<10; i++){
		printf("inserting: %d\n", i);
		push_element(s, &i);
	}

	printf("Printing\n");
	print_stack_elements(s);


	while((ptr = pop_element(s)) != NULL){
		printf("popped: %d\n", *(int*)(ptr));
	}

	printf("Printing\n");
	print_stack_elements(s);
	return 0;
}
