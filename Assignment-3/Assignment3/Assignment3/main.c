//
//  main.c
//  Assignment3
//
//  Created by Andrew Leinbach on 4/2/13.
//  Copyright (c) 2013 Andrew Leinbach. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct email {
    char From[61];
    char Date[12];
    char Subject[81];
    char Body[10001];
    struct email *next;
} email;

void Insertline(char *, FILE *);

int main(int argc, const char * argv[])
{
    /*testing for arguments*/
    //if (argc != 3) {
    //    printf("\n%s needs 2 input files!!\n", argv[0]);
    //    return 0;
    //}
        
    /*declare variables*/
    FILE *messages, *queries;
    email *newemail, *top;
    char ch, temp[101], temp2[61];
    int number, i, total = 0;
    
    /*open files*/
    //messages = fopen(argv[1], "r");
    //queries = fopen(argv[2], "r");
    
    messages = fopen("/Users/andrewleinbach/Desktop/messagesfile.txt", "r");
    queries = fopen("/Users/andrewleinbach/Desktop/queriesfile.txt", "r");
    
    
    /*messages processing*/
    while (fscanf(messages, "%c", &ch) != EOF) {
        newemail = (email*)malloc(sizeof(email));
        
        /*Get FROM information*/
        while (ch != ' ') {
            fscanf(messages, "%c", &ch);
        }
        
        Insertline(newemail->From, messages);
        
        
        /*Get DATE information*/
        fscanf(messages, "%c", &ch);
        while (ch != ' ') {
            fscanf(messages, "%c", &ch);
        }
        
        Insertline(newemail->Date, messages);
        
        /*Get Subject information*/
        fscanf(messages, "%c", &ch);
        while (ch != ' ') {
            fscanf(messages, "%c", &ch);
        }
        
        Insertline(newemail->Subject, messages);
        
        /*get BODY information*/
        fscanf(messages, "%c", &ch);
        while (ch != '\n') {
            fscanf(messages, "%c", &ch);
        }
        
        fgets(temp, 100, messages);
        while (strcmp(temp, "----------\n") !=0) {
            strcat(newemail->Body, temp);
            fgets(temp, 100, messages);
        }
        
        /*add to stack*/
        newemail->next = top;
        top = newemail;
        
        /*count messages*/
        total++;
        
        }
    
    fclose(messages);
    
    
    /*queries processing*/
    while (fgets(temp, 100, queries) != NULL) {
        
        i = 0;
        while (temp[i] != ' ' && temp[i] != '\0') {
            i++;
        }
        if (temp[i] == ' ') {
            temp[i] = '\0';
            
            i++;
            number = 0;
            while (temp[i] != '\n') {
                temp2[number] = temp[i];
                i++;
                number++;
            }
            temp2[number] = '\0';
        }
    
        
        
        newemail = top;
        
        
        /*LIST-MESSAGES-BY-DATE*/
        if (strcmp(temp,"LIST-MESSAGES-BY-DATE\n") == 0) {
            printf("LIST-MESSAGES-BY-DATE:\n");
            
            if (newemail == NULL) {
                printf("NO MESSAGES TO LIST\n");
            }
            while (newemail != NULL) {
                printf("%s---%s---%s\n",newemail->From,newemail->Subject,newemail->Date);
                newemail = newemail->next;
            }
        }
        
        /*LIST-MESSAGES-FROM*/
        else if (strcmp(temp,"LIST-MESSAGES-FROM") == 0) {
            
            if (newemail == NULL) {
                printf("NO MESSAGES TO LIST\n");
            }
            
            else {
            
                printf("LIST-MESSAGES-FROM %s:\n", temp2);
                i = 0;
                while (newemail != NULL) {
                
                    if (strcmp(temp2,newemail->From) == 0) {
                        i++;
                        printf("%s---%s---%s\n",newemail->From,newemail->Subject,newemail->Date);
                    }
                    newemail = newemail->next;
                }
            
                if (i == 0) {
                    printf("NO MESSAGES FROM %s\n",temp2);
                }
            }
            
        }
        
        /*DISPLAY-MESSAGE*/
        else if (strcmp(temp,"DISPLAY-MESSAGE") == 0) {
            number = atoi(temp2);
            
            if (number <= total) {
                printf("MESSAGE %d:\n", number);
                for (i = 1; i < number; i++) {
                    newemail = newemail->next;
                }
                printf("%s", newemail->Body);
            }
            
            else {
                printf("LESS THAN %d TOTAL MESSAGES\n", number);
            }
            
        }
        
        /*DELETE-LAST-MESSAGE*/
        else if (strcmp(temp,"DELETE-LAST-MESSAGE\n") == 0) {
            printf("DELETE-LAST-MESSAGE:\n");
            
            if (top != NULL) {
                top = top->next;
                free(newemail);
                printf("DELETED MESSAGE\n");
                total--;
            }
            
            else {
                printf("THERE ARE NO MESSAGES TO DELETE\n");
            }
            
        }
        
        else {
            printf("UNRECOGNIZED QUERY\n");
        }
        
        printf("\n");
    }
    
    fclose(queries);
    
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