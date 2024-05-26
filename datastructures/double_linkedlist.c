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
	struct node *prev;
	struct node *next;
};

void insert_element(struct node **p, int value){
	struct node *ptr = (struct node*)malloc(sizeof(struct node));
	ptr->value = value;
	
	if(*p == NULL){
		ptr->prev = NULL;
		ptr->next = NULL;
		*p = ptr;
	} else {
		struct node *temp = *p;
		while (temp->next != NULL){
			temp = temp->next;
		}
		temp->next = ptr;
		ptr->prev = temp;
	}
}

void delete_element(struct node **p, int value){
	struct node *ptr, *temp;
	if(*p == NULL)
		return;
	ptr = *p;
	while (ptr != NULL){
		if(ptr->value == value){
			if(ptr->prev == NULL){
				// First element
				*p = ptr->next;
				(*p)->prev = NULL;
				free(ptr);
			} else {
				if(ptr->next != NULL)
					ptr->next->prev = ptr->prev;
				ptr->prev->next = ptr->next;
				free(ptr);
			}
			break;
		}
		ptr = ptr->next;
	}
}

void print_elements(struct node *p){
	struct node *prev;
	if(p == NULL)
		return; 
	printf("Printing forward path: \n");
	while(p != NULL){
		printf("Element: %d\n", p->value);
		prev = p;
		p = p->next;
	}
	printf("\n");

	p = prev;
	printf("Printing reverse path: \n");
	while(p != NULL){
		printf("Element: %d\n", p->value);
		p = p->prev;
	}
	printf("\n");
}

int main(int argc, char **argv){
	struct node *ll; 
	int i = 0;
	for(i = 0; i < 10; i++){
		insert_element(&ll, i);
	}

	print_elements(ll);

	delete_element(&ll, 9);

	printf("Printing after deleting\n");
	print_elements(ll);

	return 0;
}
