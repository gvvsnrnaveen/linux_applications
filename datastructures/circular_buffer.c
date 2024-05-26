#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct node {
	int value;
	struct node *next;
};

struct buffer {
	struct node *p;
	struct node *head;
	struct node *tail;
	int buffer_size;
};

void initialize_circular_buffer(struct buffer *b, int buffer_size){
	int i = 0;
	struct node *temp, *ptr;
	if(buffer_size < 0)
		return;

	b->buffer_size = buffer_size;
	
	for(i=0; i<buffer_size; i++){
		temp = (struct node*)malloc(sizeof(struct node));
		temp->value = 0;
		temp->next = NULL;
		if(i == 0){
			b->p = temp;
		}
		if(ptr != NULL){
			ptr->next = temp;
		}
		ptr = temp;
	}
	temp->next = b->p;
	b->head = b->p;
	b->tail = b->p;

}

void print_elements_from_start(struct buffer *b){
	if(b == NULL)
		return;
	
	struct node *ptr = b->p;
	if(ptr == NULL)
		return;

	int i = 0;
	while(ptr != NULL && ((i++) < b->buffer_size)){
		printf("Element: %d\n", ptr->value);
		ptr = ptr->next;
	}
	printf("\n\n");
}

void print_elements(struct buffer *b){
	if(b == NULL)
		return;
	if(b->p == NULL)
		return;
	while(b->tail != b->head){
		printf("Ele: %d\n", b->tail->value);
		b->tail = b->tail->next;
	}
	printf("\n\n");
}

void insert_element(struct buffer *b, int value){
	if(b == NULL)
		return;
	b->head->value = value;
	b->head = b->head->next;
	if(b->head == b->tail)
		b->tail = b->tail->next;
}

void delete_element(struct buffer *b){
	if(b->head == b->tail){
		printf("circular buffer empty\n");
		return;
	}
	printf("Deleted: %d\n", b->tail->value);
	b->tail = b->tail->next;
}

int main(int argc, char **argv){
	struct buffer b;
	int i = 0;

	initialize_circular_buffer(&b, 10);

	for(i=0; i<15; i++){
		insert_element(&b, i);
	}

	print_elements_from_start(&b);


	delete_element(&b);
	delete_element(&b);
	delete_element(&b);
	delete_element(&b);

	print_elements(&b);

	return 0;
}
