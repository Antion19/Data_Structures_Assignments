/* Pre-processor Directives */
#include <stdio.h>
#include <stdlib.h>

/* Filename:
	Author: Andrew Leinbach
	Date Written: 1/24/2013
	Description: a program to create a link_list of characters
   */

/*In this code I make the times when there is no
 node or when there is only one node a special case.
 I understand that there is a better way to go about it
 but I wrote this before it was taught in class and decided
 I did not really want to put in the work to change an already
 good thing.*/



/* Main Program */
int main () {
	
	/* Creates node structure */
	typedef struct node {
		char data;
		struct node *next;
	} node;
	
	
   /* List of variables */
	char ch, i;
	node *head = NULL, *new_node = NULL, *iterator = NULL, *iterator2 = NULL; 
	
	
	/* Instructions for user */
	printf("Please select one of the following options:\n");
	printf("\tPress 1 to insert an element into the list.\n");
	printf("\tPress 2 to delete an element from the list.\n");
	printf("\tPress 3 to end the program.\n");
	
	printf("\n?");
	scanf(" %c", &i);
	
	while (i != '3') {
		
		/*enters a character*/
		if (i == '1') {
			
			printf("Enter a character: ");
			scanf(" %c", &ch);
			
			if (head == NULL) {
				
				new_node = (node*)malloc(sizeof(node));
				new_node->data = ch;
				new_node->next = head;
				head = new_node;
			}
			
			else if (head->next == NULL) {
				
				if (head->data >= ch) {
				
					new_node = (node*)malloc(sizeof(node));
					new_node->data = ch;
					new_node->next = head;
					head = new_node;
				}
				
				else {
					
					new_node = (node*)malloc(sizeof(node));
					new_node->data = ch;
					new_node->next = NULL;
					head->next = new_node;
					
				}

			}
			
			else {
				
				new_node = (node*)malloc(sizeof(node));
				new_node->data = ch;
				
				
				if (head->data >= ch) {
					
					new_node->next = head;
					head = new_node;
					
				}
				
				else {
					
					iterator = head;
					while (iterator->data <= ch && iterator->next != NULL) {
						
						iterator2 = iterator;
						iterator = iterator->next;
						
					}
					
					if (iterator->data <= ch) {
						
						new_node->next = NULL;
						iterator->next = new_node;
					
					}
					
					else {
					
						new_node->next = iterator;
						iterator2->next = new_node;
					
					}
					
				}

			
			}
			
			/*Print the list*/
			iterator = head;
			printf("The list is:\n");
			while (iterator != NULL) {
				printf("%c ==> ", iterator->data);
				iterator = iterator->next;
			}
			printf("NULL\n");
			
		}
		
		/*deletes a character*/
		else if (i == '2') {
		
			printf("Enter a character to be deleted: ");
			scanf(" %c", &ch);
			
			
			if (head == NULL) {
			
				printf("No elements to delete\n");
				
			}
			
			else {
			
				if (head->next == NULL) {
				
					if (head->data == ch) {
					
						free(head);
						head = NULL;
						
						printf("%c deleted.\n", ch);
						/*Print the list*/
						printf("The list is:\n");
						iterator = head;
						while (iterator != NULL) {
							printf("%c ==> ", iterator->data);
							iterator = iterator->next;
						}
						printf("NULL\n");
						
					}
					
					else {
					
						printf("%c not found", ch);
						
					}
				}
				
				else if (head->data == ch) {
				
					
					iterator = head;
					head = head->next;
					free(iterator);
				
					printf("%c deleted.\n", ch);
					/*Print the list*/
					printf("The list is:\n");
					iterator = head;
					while (iterator != NULL) {
						printf("%c ==> ", iterator->data);
						iterator = iterator->next;
					}
					printf("NULL\n");
					
				}
				
				else {
				
					iterator = head;
					while (iterator->data != ch && iterator->next != NULL) {
					
					iterator2 = iterator;
					iterator = iterator->next;
					
					}
					
					if (iterator->data == ch) {
						
						iterator2->next = iterator->next;
						free(iterator);
						
						printf("%c deleted.\n", ch);
						/*Print the list*/
						printf("The list is:\n");
						iterator = head;
						while (iterator != NULL) {
							printf("%c ==> ", iterator->data);
							iterator = iterator->next;
						}
						printf("NULL\n");
						
					}
					
					else {
						
						printf("%c not found", ch);
						
					}
			
			
				}
			}
		}
		
		else {
			printf("Invalid input!!!");
		}
		
		printf("\n?");
		scanf(" %c", &i);
	}
	
	/*free the list*/
	iterator = head;
	while (iterator != NULL) {
		
		iterator2 = iterator;
		iterator = iterator->next;
		free(iterator2);
	}
	
	
    return 0;
}

