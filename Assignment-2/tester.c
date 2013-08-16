//
//  tester.c
//  
//
//  Created by Andrew Leinbach on 3/1/13.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree_node {
    char *data;
    struct tree_node *left_ptr;
    struct tree_node *right_ptr;
} tree_node;


tree_node* read_strings(FILE *file_ptr);
tree_node* create_node(char *word);
void insert_node(tree_node *root, tree_node *new_node);
void print_tree(tree_node *root);

int main () {
    
    printf("hello world");
    
    tree_node* root;
    FILE *file_ptr, *g;
    
    g = fopen("input.txt", "w");
    
    fprintf(g, "5 apple\n");
    fprintf(g, "10 watermelon\n");
    fprintf(g, "6 banana\n");
    fprintf(g, "5 peach\n");
    fprintf(g, "3 fig\n");
    fprintf(g, "5 melon\n");
    fprintf(g, "4 pear\n");
    fprintf(g, "0\n");
    fclose(g);
    
    
    file_ptr = fopen("input.txt", "r");
    
    root = read_strings(file_ptr);
    print_tree(root);
    
    fclose(file_ptr);
    return 0;
}

tree_node* read_strings(FILE *file_ptr)
{
    tree_node *root = NULL, *new_node = NULL;
    int x;
    char *word;
    
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
        fscanf(file_ptr, " %d", &x);
    }
    return root;
}

tree_node* create_node(char *word)
{
    tree_node * new_node;
    
    new_node = (tree_node*) malloc(sizeof(tree_node));
    new_node->data = word;
    new_node->left_ptr = NULL;
    new_node->right_ptr = NULL;
    
    return new_node;
    
}

void insert_node(tree_node *root,tree_node *new_node)
{
    if (strcmp(root->data, new_node->data) <= 0) {
        if (root->left_ptr == NULL) {
            root->left_ptr = new_node;
            return;
        }
        else {
            insert_node(root->left_ptr, new_node);
        }
    }
    else {
        if (root->right_ptr == NULL) {
            root->right_ptr = new_node;
            return;
        }
        else {
            insert_node(root->right_ptr, new_node);
        }
    }
    
}

void print_tree(tree_node *root)
{
    if (root->left_ptr != NULL) {
        print_tree(root->left_ptr);
    }
    
    printf("%s\n", root->data);
    
    if (root->right_ptr != NULL) {
        print_tree(root->right_ptr);
    }
}
