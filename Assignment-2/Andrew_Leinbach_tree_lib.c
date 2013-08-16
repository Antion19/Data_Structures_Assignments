/* Filename: Andrew_Leinbach_tree_lib.c
 Author: Andrew Leinbach
 Date Written: 3/1/2013
 Description: the library implementations for Assignment 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Andrew_Leinbach_tree_lib.h"

bin_tree read_strings(FILE *file_ptr)
{
    tree_node *root = NULL, *new_node = NULL;
    bin_tree out_tree;
    int x;
    char *word;
    out_tree.max_depth = 0;
    
    
    fscanf(file_ptr, " %d", &x);
    while (x) {
        word = (char*)malloc((x+1)*sizeof(char));
        fscanf(file_ptr, " %s", word);
        new_node = create_node(word);
        if (root != NULL) {
            insert_node(root, new_node);
        }
        else {
            root = new_node;
        }
        
        if (new_node->level > out_tree.max_depth) {
            out_tree.max_depth = new_node->level;
        }
        
        fscanf(file_ptr, " %d", &x);
    }
    out_tree.root = root;
    
    return out_tree;
}

tree_node* create_node(char *word)
{
    tree_node * new_node;
    
    new_node = (tree_node*) malloc(sizeof(tree_node));
    new_node->data = word;
    new_node->left_ptr = NULL;
    new_node->right_ptr = NULL;
    new_node->level = 0;
    new_node->number = 0;
    
    return new_node;
    
}

void insert_node(tree_node *root,tree_node *new_node)
{
    
    if (strcmp(root->data, new_node->data) >= 0) {
        if (root->left_ptr == NULL) {
            root->left_ptr = new_node;
            new_node->level = root->level +1;
            new_node->number = 2*root->number + 1;
            
            return;
        }
        else {
            insert_node(root->left_ptr, new_node);
        }
    }
    else {
        if (root->right_ptr == NULL) {
            root->right_ptr = new_node;
            new_node->level = root->level +1;
            new_node->number = 2*root->number + 2;
            
            return;
        }
        else {
            insert_node(root->right_ptr, new_node);
        }
    }
}

void print_tree(tree_node *root, int max_depth)
{
    printf("Root 0: %s\n", root->data);
    int i;
    
    for (i=1; i <= max_depth; i++) {
        printf("Level %d: ", i);
        find_node(root, i);
        printf("\n");
    }
    
}

void find_node(tree_node *node, int level)
{
    if (node == NULL) {
        return;
    }
    if (node->level == level) {
        printf("%d:%s ", node->number, node->data);
        return;
    }
    else {
        find_node(node->left_ptr, level);
        find_node(node->right_ptr, level);
    }
    
}
