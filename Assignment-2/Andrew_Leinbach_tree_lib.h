/* Filename: Andrew_Leinbach_tree_lib.h
 Author: Andrew Leinbach
 Date Written: 3/1/2013
 Description: the library header for Assignment 2
 */


#include <stdio.h>

typedef struct tree_node {
    char *data;
    struct tree_node *left_ptr;
    struct tree_node *right_ptr;
    int level;
    int number;
} tree_node;

typedef struct bin_tree {
    tree_node *root;
    int max_depth;
    
} bin_tree;


extern bin_tree read_strings(FILE *file_ptr);
extern tree_node* create_node(char *word);
extern void insert_node(tree_node *root, tree_node *new_node);
extern void print_tree(tree_node *root, int max_depth);
extern void find_node(tree_node *root, int level);
