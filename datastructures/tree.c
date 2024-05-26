#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

struct tree {
	int value;
	int childs;
	struct tree *children;
};

void print_tab_spaces(int level){
	int i = 0;
	for(i = 0; i<level; i++){
		printf("\t");
	}
}

void print_tree(struct tree *t, int level){
	int i = 0;
	if(t == NULL)
		return;
	print_tab_spaces(level);
	if(level == 0)
		printf("root: %d", t->value);
	else 
		printf("node: %d", t->value);
	if(t->childs > 0){
		printf(" -> childs: ");
		for (i = 0; i<t->childs; i++){
			printf("%d ", t->children[i].value);
		}
		printf("\n");
		for(i = 0; i< t->childs; i++){
			print_tree(&t->children[i], level + 1);
		}
	} else {
		printf(" (No children)");
	}
	printf("\n");
}


struct tree* get_node(struct tree *t, int value){
	if(t == NULL)
		return NULL;
	if(t->value == value){
		return t;
	} else {
		if(t->childs > 0){
			int i = 0;
			struct tree *temp = NULL;
			for(i = 0; i < t->childs; i++) {
				temp = get_node(&(t->children[i]), value);
				if(temp != NULL){
					return temp;
				}
			}
		}
	}
	return NULL;
}

void insert_element_at_node(struct tree *t, int value){
	struct tree *ptr = NULL;
	ptr = (struct tree*)malloc(sizeof(struct tree));
	ptr->value = value;
	ptr->childs = 0; 
	ptr->children = NULL;
	if(t->childs == 0){
		t->children = ptr;
	} else {
		t->children = (struct tree*)realloc(t->children, (sizeof(struct tree) * (t->childs + 1)));
		t->children[t->childs].value = value;
	}
	t->childs++;
}

void insert_root_element(struct tree **t, int value){
	if(*t == NULL){
		struct tree *ptr = NULL;
		ptr = (struct tree*)malloc(sizeof(struct tree));
		ptr->value = value;
		ptr->childs = 0;
		ptr->children = NULL;
		*t = ptr;
	}
}


int main(int argc, char **argv){
	struct tree *t = NULL;
	struct tree *temp = NULL;

	insert_root_element(&t, 10);

	temp = get_node(t, 10);
	insert_element_at_node(temp, 20);
	insert_element_at_node(temp, 30);
	insert_element_at_node(temp, 40);
	insert_element_at_node(temp, 50);
	insert_element_at_node(temp, 60);

	
	temp = get_node(t, 30);
	insert_element_at_node(temp, 70);
	insert_element_at_node(temp, 80);
	insert_element_at_node(temp, 90);
	insert_element_at_node(temp, 100);
	insert_element_at_node(temp, 110);

	temp = get_node(t, 50);
	insert_element_at_node(temp, 120);

	temp = get_node(t, 40);
	insert_element_at_node(temp, 130);
	insert_element_at_node(temp, 140);
	insert_element_at_node(temp, 150);
	insert_element_at_node(temp, 160);
	insert_element_at_node(temp, 170);
	insert_element_at_node(temp, 180);
	insert_element_at_node(temp, 190);
	insert_element_at_node(temp, 200);

	temp = get_node(t, 100);
	insert_element_at_node(temp, 210);
	insert_element_at_node(temp, 220);
	insert_element_at_node(temp, 230);

	print_tree(t, 0);
	return 0;
}
