//
//  main.c
//  Assignment-4
//
//  Created by Andrew Leinbach on 4/23/13.
//  Copyright (c) 2013 Andrew Leinbach. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct person {
    char first[13];
    char last[13];
    unsigned short int ID;
    unsigned short int Father;
    unsigned short int Mother;
    unsigned short int friends[15];
    struct person *next;
} person;

void Insertline(char *, FILE *);


int main(int argc, const char * argv[])
{
    /*testing for arguments*/
    if (argc != 3) {
        printf("\n%s needs 2 input files!!\n", argv[0]);
        return 0;
    }
    
    
    /*declare variables*/
    FILE *community, *queries;
    person *head = NULL, *newperson, *iterator, *iterator2;
    char ch, temp[28];
    unsigned short int x, y, z;
    short int i, k;
    
    /*open files*/
    //community = fopen(argv[1], "r");
    //queries = fopen(argv[2], "r");
    
    community = fopen(argv[1], "r");
    queries = fopen(argv[2], "r");
    
    
    /*gather community*/
    while (fscanf(community, "%c", &ch) != EOF) {
        newperson = (person*)malloc(sizeof(person));
        
        /*Get first*/
        while (ch != ':') {
            fscanf(community, "%c", &ch);
        }
        fscanf(community, "%c", &ch);
        
        Insertline(newperson->first, community);
        
        /*Get last*/
        fscanf(community, "%c", &ch);
        while (ch != ':') {
            fscanf(community, "%c", &ch);
        }
        fscanf(community, "%c", &ch);
        
        Insertline(newperson->last, community);
        
        /*Get ID*/
        fscanf(community, "%c", &ch);
        while (ch != ':') {
            fscanf(community, "%c", &ch);
        }
        fscanf(community, "%c", &ch);
        
        fscanf(community, "%hu", &newperson->ID);
        
        /*Get Father*/
        fscanf(community, "%c", &ch);
        while (ch != ':') {
            fscanf(community, "%c", &ch);
        }
        fscanf(community, "%c", &ch);
        
        fscanf(community, "%hu", &newperson->Father);
        
        
        /*Get Mother*/
        fscanf(community, "%c", &ch);
        while (ch != ':') {
            fscanf(community, "%c", &ch);
        }
        fscanf(community, "%c", &ch);
        
        fscanf(community, "%hu", &newperson->Mother);
        
        
        /*Get Friends*/
        fscanf(community, "%c", &ch);
        while (ch != ':') {
            fscanf(community, "%c", &ch);
        }
        fscanf(community, "%c", &ch);
        
        i = 0;
        while (ch != '\n') {
            fscanf(community, "%hu", &newperson->friends[i]);
            fscanf(community, "%c", &ch);
            i++;
            
        }
        newperson->friends[i] = 0;
        
        /*place newperson among individuals*/
        if (head == NULL) {
            head = newperson;
        }
        else if (newperson->ID <= head->ID) {
            newperson->next = head;
            head = newperson;
        }
        else {
            iterator = head;
            while (iterator->ID <= newperson->ID && iterator->next != NULL) {
                iterator2 = iterator;
                iterator = iterator->next;
                
            }
            if (iterator->ID > newperson->ID) {
                newperson->next = iterator;
                iterator2->next = newperson;
                
            }
            else {
                newperson->next = NULL;
                iterator->next = newperson;
            }
            
        }
        
        
    }
    
    fclose(community);
    
    /*Take in queries*/
    while (fscanf(queries, "%c", &ch) != EOF) {
        
        /*get command*/
        i = 0;
        temp[i] = ch;
        while (ch != ' ' && ch != '\n') {
            i++;
            fscanf(queries, "%c", &ch);
            temp[i] = ch;
        }
        temp[i] = '\0';
        
        
        /*get ID*/
        if (ch == ' ') {
            fscanf(queries, "%hu", &x);
            /*this is to get the newline character*/
            fscanf(queries, "%c", &ch);
        }
        
        /*FULL-NAME-OF*/
        if (strcmp(temp,"FULL-NAME-OF") == 0) {
            iterator = head;
            while (iterator->ID != x) {
                if (iterator->next == NULL) {
                    printf("Individual %hu does not live in the community\n", x);
                    break;
                }
                iterator = iterator->next;
            }
            
            if (iterator->ID == x) {
                printf("FULL-NAME-OF %hu: %s %s\n", x, iterator->first, iterator->last);
                
            }
            
            
        }
        
        /*MOTHER-OF*/
        else if (strcmp(temp,"MOTHER-OF") == 0) {
            iterator = head;
            while (iterator->ID != x) {
                if (iterator->next == NULL) {
                    printf("Individual %hu does not live in the community\n", x);
                    break;
                }
                iterator = iterator->next;
            }
            
            if (iterator->ID == x) {
                iterator2 = head;
                while (iterator2->ID != iterator->Mother) {
                    if (iterator2->next == NULL) {
                        printf("Individual %hu's mother does not live in the community\n", x);
                        break;
                    }
                    iterator2 = iterator2->next;
                }
                
                if (iterator2->ID == iterator->Mother) {
                    printf("MOTHER-OF %hu: %s %s\n", x, iterator2->first, iterator2->last);
                }
            }
        }
        
        /*FATHER-OF*/
        else if (strcmp(temp,"FATHER-OF") == 0) {
            iterator = head;
            while (iterator->ID != x) {
                if (iterator->next == NULL) {
                    printf("Individual %hu does not live in the community\n", x);
                    break;
                }
                iterator = iterator->next;
            }
            
            if (iterator->ID == x) {
                iterator2 = head;
                while (iterator2->ID != iterator->Father) {
                    if (iterator2->next == NULL) {
                        printf("Individual %hu's father does not live in the community\n", x);
                        break;
                    }
                    iterator2 = iterator2->next;
                }
                
                if (iterator2->ID == iterator->Father) {
                    printf("Father-OF %hu: %s %s\n", x, iterator2->first, iterator2->last);
                }
            }
        }
        
        /*HALF-SIBLINGS-OF*/
        else if (strcmp(temp,"HALF-SIBLINGS-OF") == 0) {
            iterator = head;
            while (iterator->ID != x) {
                if (iterator->next == NULL) {
                    printf("Individual %hu does not live in the community\n", x);
                    break;
                }
                iterator = iterator->next;
            }
            
            if (iterator->ID == x) {
                iterator2 = head;
                printf("HALF-SIBLINGS-OF %hu:", x);
                while (iterator2 != NULL) {
                    if (iterator2->Father == iterator->Father || iterator2->Mother == iterator->Mother) {
                        if (iterator2->ID != x) {
                            if ((iterator2->Father == iterator->Father && iterator2->Mother == iterator->Mother) == 0) {
                                printf(" %s %s", iterator2->first, iterator2->last);
                                iterator2 = iterator2->next;
                                break;
                            }
                        }
                    }
                    iterator2 = iterator2->next;
                }
                while (iterator2 != NULL) {
                    if (iterator2->Father == iterator->Father || iterator2->Mother == iterator->Mother) {
                        if (iterator2->ID != x) {
                            if ((iterator2->Father == iterator->Father && iterator2->Mother == iterator->Mother) == 0) {
                                printf(", %s %s", iterator2->first, iterator2->last);
                                
                            }
                        }
                    }
                    iterator2 = iterator2->next;
                }
                
                
                printf("\n");
            }
            
            
            
        }
        
        /*FULL-SIBLINGS-OF*/
        else if (strcmp(temp,"FULL-SIBLINGS-OF") == 0) {
            iterator = head;
            while (iterator->ID != x) {
                if (iterator->next == NULL) {
                    printf("Individual %hu does not live in the community\n", x);
                    break;
                }
                iterator = iterator->next;
            }
            
            if (iterator->ID == x) {
                iterator2 = head;
                printf("FULL-SIBLINGS-OF %hu:", x);
                while (iterator2 != NULL) {
                    if (iterator2->Father == iterator->Father && iterator2->Mother == iterator->Mother) {
                        if (iterator2->ID != x) {
                            printf(" %s %s", iterator2->first, iterator2->last);
                            iterator2 = iterator2->next;
                            break;
                        }
                    }
                    iterator2 = iterator2->next;
                }
                
                while (iterator2 != NULL) {
                    if (iterator2->Father == iterator->Father && iterator2->Mother == iterator->Mother) {
                        if (iterator2->ID != x) {
                            printf(", %s %s", iterator2->first, iterator2->last);
                        }
                    }
                    iterator2 = iterator2->next;
                }
                
                printf("\n");
            }
            
        }
        
        /*CHILDREN-OF*/
        else if (strcmp(temp,"CHILDREN-OF") == 0) {
            iterator2 = head;
            printf("CHILDREN-OF %hu:", x);
            while (iterator2 != NULL) {
                if (iterator2->Father == x || iterator2->Mother == x) {
                    printf(" %s %s", iterator2->first, iterator2->last);
                    iterator2 = iterator2->next;
                    break;
                }
                iterator2 = iterator2->next;
            }
            
            while (iterator2 != NULL) {
                if (iterator2->Father == x || iterator2->Mother == x) {
                    printf(", %s %s", iterator2->first, iterator2->last);
                }
                iterator2 = iterator2->next;
            }
            printf("\n");
            
        }
        
        /*MUTUAL-FRIENDS-OF*/
        else if (strcmp(temp,"MUTUAL-FRIENDS-OF") == 0) {
            iterator = head;
            while (iterator->ID != x) {
                if (iterator->next == NULL) {
                    printf("Individual %hu does not live in the community\n", x);
                    break;
                }
                iterator = iterator->next;
            }
            
            if (iterator->ID == x) {
                printf("MUTUAL-FRIENDS-OF %hu:", x);
                i =0;
                while (iterator->friends[i] != 0) {
                    iterator2 = head;
                    while (iterator2->ID != iterator->friends[i] && iterator2 != NULL) {
                        iterator2 = iterator2->next;
                    }
                    
                    if (iterator2->ID == iterator->friends[i]) {
                        k = 0;
                        while (iterator2->friends[k] != 0) {
                            if (iterator2->friends[k] == iterator->ID) {
                                printf(" %s %s", iterator2->first, iterator2->last);
                                break;
                            }
                            
                            k++;
                        }
                    }
                    
                    i++;
                    if (iterator2->friends[k] == iterator->ID) {
                        break;
                    }
                }
                
                while (iterator->friends[i] != 0) {
                    iterator2 = head;
                    while (iterator2->ID != iterator->friends[i] && iterator2 != NULL) {
                        iterator2 = iterator2->next;
                    }
                    
                    if (iterator2->ID == iterator->friends[i]) {
                        k = 0;
                        while (iterator2->friends[k] != 0) {
                            if (iterator2->friends[k] == iterator->ID) {
                                printf(", %s %s", iterator2->first, iterator2->last);
                                break;
                            }
                            
                            k++;
                        }
                    }
                    
                    i++;
                }
            }
            
            printf("\n");
            
            
        }
        
        /*INVERSE-FRIENDS-OF*/
        else if (strcmp(temp,"INVERSE-FRIENDS-OF") == 0) {
            iterator = head;
            printf("INVERSE-FRIENDS-OF %hu:", x);
            while (iterator != NULL) {
                i = 0;
                while (iterator->friends[i] != 0) {
                    if (iterator->friends[i] == x) {
                        printf(" %s %s", iterator->first, iterator->last);
                        break;
                    }
                    i++;
                }
                if (iterator->friends[i] == x) {
                    iterator = iterator->next;
                    break;
                }
                iterator = iterator->next;
            }
            
            while (iterator != NULL) {
                i = 0;
                while (iterator->friends[i] != 0) {
                    if (iterator->friends[i] == x) {
                        printf(", %s %s", iterator->first, iterator->last);
                        break;
                    }
                    i++;
                }
                iterator = iterator->next;
            }
            printf("\n");
            
            
        }
        
        /*WHO-HAS-MOST-MUTUAL-FRIENDS*/
        else if (strcmp(temp,"WHO-HAS-MOST-MUTUAL-FRIENDS") == 0) {
            iterator = head;
            x = 0;
            while (iterator->next != NULL) {
                i = 0;
                y = 0;
                while (iterator->friends[i] != 0) {
                    iterator2 = head;
                    while (iterator2->ID != iterator->friends[i] && iterator2 != NULL) {
                        iterator2 = iterator2->next;
                    }
                    
                    if (iterator2->ID == iterator->friends[i]) {
                        k = 0;
                        while (iterator2->friends[k] != 0) {
                            if (iterator2->friends[k] == iterator->ID) {
                                y++;
                                break;
                            }
                            
                            k++;
                        }
                    }
                    
                    i++;
                }
                if (x < y) {
                    x = y;
                    z = iterator->ID;
                }
                
                iterator = iterator->next;
            }
            
            
            iterator = head;
            while (iterator->ID != z) {
                iterator = iterator->next;
            }
            
            if (iterator->ID == z) {
                printf("WHO-HAS-MOST-MUTUAL-FRIENDS: %s %s\n", iterator->first, iterator->last);
                
            }
            
            
            
        }
        else {
            printf("INVALID INPUT");
        }
        
    }
    
    fclose(queries);
    
    /*free the list*/
	iterator = head;
	while (iterator != NULL) {
		
		iterator2 = iterator;
		iterator = iterator->next;
		free(iterator2);
	}
    
    return 0;
    
}


void Insertline(char *array, FILE * f)
{
    int i = 0;
    fscanf(f, "%c", &array[i]);
    while (array[i] != '\n') {
        i++;
        fscanf(f, "%c", &array[i]);
        
    }
    array[i] = '\0';
}
