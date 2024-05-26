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

struct node {
	int value;
	struct node *left;
	struct node *right;
};

struct node* insert_node(struct node *node, int value){
	if(node == NULL){
		node = (struct node*)malloc(sizeof(struct node));
		node->value = value;
		node->left = NULL;
		node->right = NULL;
		return node;
	}
	if(value < node->value){
		// left side
		node->left = insert_node(node->left, value);
	} else {
		// right side
		node->right = insert_node(node->right, value);
	}
	return node;
}

void print_binary_tree(struct node *node, char *node_pos, int parent_value, int level){
	if(node == NULL)
		return;
	if(level == 0)
		printf("%s node value: %d\n", node_pos, node->value);
	else
		printf("%s value of %d: %d\n", node_pos, parent_value, node->value);
	if(node->left != NULL){
		print_binary_tree(node->left, "left", node->value, ++level);
	}
	if(node->right != NULL){
		print_binary_tree(node->right, "right", node->value, ++level);
	}
}

int get_binary_tree_height(struct node *node){
	if(node == NULL)
		return 0;
	else {
		int left_height = get_binary_tree_height(node->left);
		int right_height = get_binary_tree_height(node->right);
		if(left_height > right_height){
			return left_height + 1; 
		} else {
			return right_height + 1;
		}
	}
}

void print_inorder_traversal(struct node *node){
	if(node == NULL)
		return;
	print_inorder_traversal(node->left);
	printf("%d ", node->value);
	print_inorder_traversal(node->right);
}

void print_preorder_traversal(struct node *node){
	if(node == NULL)
		return;
	printf("%d ", node->value);
	print_preorder_traversal(node->left);
	print_preorder_traversal(node->right);
}

void print_postorder_traversal(struct node *node){
	if(node == NULL)
		return;
	print_postorder_traversal(node->left);
	print_postorder_traversal(node->right);
	printf("%d ", node->value);
}

void delete_all_elements(struct node *node){
	if(node == NULL)
		return;
	//printf("Deleting: %d\n", node->value);
	delete_all_elements(node->left);
	delete_all_elements(node->right);
	free(node);
}


int main(int argc, char **argv){

	struct node *tree = NULL;
	int i = 0;
	int values[] = {8,4,12,2,1,3,6,5,7,10,9,11,14,13,15};
	int level = 0;
	int tree_height = 0;
	for(i = 0 ; i < sizeof(values)/sizeof(int); i++){
		tree = insert_node(tree, values[i]);
	}

	tree_height = get_binary_tree_height(tree);
	printf("tree height: %d\n", tree_height);

	print_binary_tree(tree, "root", 0, 0);

	printf("Inorder traversal: ");
	print_inorder_traversal(tree);
	printf("\n");
	
	printf("Preorder traversal: ");
	print_preorder_traversal(tree);
	printf("\n");

	printf("Postorder traversal: ");
	print_postorder_traversal(tree);
	printf("\n");

	printf("Deleting all elements\n");
	delete_all_elements(tree);
	return 0;
}
