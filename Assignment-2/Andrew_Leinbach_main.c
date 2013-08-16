/* Filename: Andrew_Leinbach_main.c
 Author: Andrew Leinbach
 Date Written: 3/1/2013
 Description: the main function for Assignment 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Andrew_Leinbach_tree_lib.h"

int main()
{
    bin_tree bin1;
    FILE *file_ptr;
    
    file_ptr = fopen("input.txt", "r");
    
    bin1 = read_strings(file_ptr);
    print_tree(bin1.root, bin1.max_depth);
    
    fclose(file_ptr);
    return 0;
    
}
