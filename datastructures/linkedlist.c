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
#include <string.h>

struct node {
	int value;
	struct node *next;
};

struct node* insert_element_at_head(struct node **p, int value){
	struct node *ptr = (struct node*)malloc(sizeof(struct node));
	ptr->value = value;
	ptr->next = *p;
	*p = ptr;
}

void insert_elements(struct node **p, int value){
	struct node *ptr = (struct node*)malloc(sizeof(struct node));
	ptr->value = value;
	ptr->next = NULL;
	if(*p == NULL){
		*p = ptr;
	} else {
		struct node *temp = *p;
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = ptr;
	}
}

void delete_element(struct node **p, int value){
	struct node *ptr, *prev;
	if(*p == NULL)
		return;
	if((*p)->value == value){
		ptr = *p;
		*p = (*p)->next;
		free(ptr);
		return ;
	}
	ptr = *p;
	prev = ptr;
	while(ptr->next != NULL){
		if(ptr->value == value){
			prev->next = ptr->next;
			free(ptr);
			break;
		}
		prev = ptr;
		ptr = ptr->next;
	}
}

void delete_all_elements(struct node **p){
	struct node *temp;
	while(*p != NULL){
		temp = *p;
		*p = (*p)->next;
		free(temp);
	}
}

void print_elements(struct node *p){
	while(p != NULL){
		printf("element: %d\n", p->value);
		p = p->next;
	}
	printf("================================\n");
}

int main(int argc, char **argv){
	struct node *ll = NULL;
	int i = 0;
	for(i = 0; i < 10; i++){
		insert_elements(&ll, i * 10);
	}
	
	print_elements(ll);

	delete_element(&ll, 40);

	print_elements(ll);

	insert_element_at_head(&ll, 100);

	print_elements(ll);

	delete_all_elements(&ll);

	print_elements(ll);

	for(i = 0; i < 10; i++){
		insert_elements(&ll, i);
	}
	for(i = 0; i < 10; i++){
		insert_element_at_head(&ll, i);
	}
	print_elements(ll);

	delete_all_elements(&ll);

	return 0;
}
