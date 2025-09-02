/*****************************************************************
 //  NAME:        Andrew Bushong
 //
 //  HOMEWORK:    3b
 //
 //  CLASS:       ICS 212
 //
 //  INSTRUCTOR:  Ravi Narayan
 //
 //  DATE:        November 1, 2024
 //
 //  FILE:        database.c 
 //
 //  DESCRIPTION:
 //   This file contains the user_interface functions. Manages a linked list 
 //   And provides functions for manipulating the linked list.
 //   
 //
 //
 ****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"
#include "database.h"
extern int debugmode;
/****************************************************************
//
//  Function name:  addRecord
//
//  Description: Adds a record to the linked list.
//
//  Parameters: struct record** rec: pointer to the start of the linked list
//              int accNum: account number of the new account
//              char name[ ]: name to be put on the record
//              char address[ ]: address to be put on record.
//
//  Return values: 0: success
//                -1: There is an error and record was not added.
//
//
****************************************************************/
int addRecord (struct record ** rec, int accNum, char name[ ], char address[ ])
{
    struct record* current;
    struct record* temp;
    struct record* prev; 
    int search;
    
    current = *rec;
    temp = NULL;
    prev = NULL;
    search = 1;

    if (debugmode == 1)
    {
        printf("\nThe add function was called with values:\n");  
        printf("accNum: %d\n",accNum);
        printf("Name: %s\nAddress: %s\n", name, address);
    }

    if (*rec == NULL)
    {
        *rec = (struct record *)malloc(sizeof(struct record));
        strcpy((**rec).name, name);
        (**rec).accountno = accNum;
        strcpy((**rec).address, address);
        (**rec).next = NULL;
        return 0;
    }
    while (search == 1)
    {
        if (accNum == (*current).accountno)
        {
            printf("This account number already exists.\n");
            return 0;
        }
        else if (current != NULL && accNum < (*current).accountno)
        {
            if (current == *rec)
            {
                temp = *rec;
                *rec = (struct record *)malloc(sizeof(struct record));
                strcpy((**rec).name, name);
                (**rec).accountno = accNum;
                strcpy((**rec).address, address);
                (**rec).next = temp;
                return 0;
            }
            else
            {   
                temp = (struct record *)malloc(sizeof(struct record));
                strcpy((*temp).name, name);
                (*temp).accountno = accNum;
                strcpy((*temp).address, address);
                (*temp).next = current;
                (*prev).next = temp;
                return 0;     
            }
        }
        else if ((*current).next == NULL && search == 1)
        {
            temp = (struct record *)malloc(sizeof(struct record));
            strcpy((*temp).name, name);
            (*temp).accountno = accNum;
            strcpy((*temp).address, address);
            (*temp).next = NULL;
            (*current).next = temp;
            return 0;
        }
        else 
        {
            prev = current;
            current = (*current).next;
        }
    }
    
    return -1;
}
/****************************************************************
//  Function name:  printAllRecords
//
//  Description: Prints all records in the linked list.
//  
//  Parameters: struct record* rec: pointer to the start of the linked list
//  
//  Return values: void
//
//
***************************************************************/
void printAllRecords(struct record * rec)
{
    struct record* current;
    current = rec;

    if (debugmode == 1)
    {
        printf("\nThe printAllRecords function was called\n");
    }
    printf("\n ------------------------------------\n");
    while (current != NULL)
    {
        printf("Account Number: %d\n", (*current).accountno);
        printf("Name: %s\n", (*current).name);
        printf("Address: %s\n", (*current).address);
        printf("\n ------------------------------------\n");
        current = (*current).next;
    }
}
/****************************************************************
//  Function name:  findRecord
//
//  Description: Finds a record by account number and prints its information
//  
//  Parameters: struct record* rec: pointer to the start of the linked list
//              int accNum: Account number that needs to be found
//  
//  Return values: 0: Account number was found and the record is printed
//                 1: account number was not found
//
//
**************************************************************/
int findRecord (struct record * rec, int accNum)
{
    struct record* temp;
    if (debugmode == 1)
    {
        printf("\nThe findRecord function was called with values:\naccNum: %d\n", accNum);
    }

    temp = rec;

    while (temp != NULL)
    {
        if ((*temp).accountno == accNum)
        {
            printf("Account Number: %d\n", (*temp).accountno);
            printf("Name: %s", (*temp).name);
            printf("Address: %s", (*temp).address);
            return 0;
        }
        temp = (*temp).next;
    }
    printf("Account Number not found\n");
    
    return -1;
}
/****************************************************************
//  Function name:  deleteRecord
//
////  Description: Deletes a record from the linked list.
////  
////  Parameters: struct record** rec: pointer to the start of the linked list
//              int accNum: account number of the account to be deleted.
////
////  Return values: 0: successfully deleted record
//                  -1: error finding record.
////
////
**************************************************************/
int deleteRecord(struct record ** rec, int accNum)
{
    struct record* current;
    struct record* prev;
    current = *rec;
    prev = NULL;

    if (debugmode == 1)
    {
        printf("\nThe deleteRecord function was called with values:\naccNum:: %d\n", accNum);
    }
    
    while (current != NULL)
    {
        if (accNum == (*current).accountno)
        {
            if (current == *rec)
            {
                *rec = (*current).next;
            }
            else 
            {
                (*prev).next = (*current).next;
            }
            free(current);
            printf("Account Number %d was deleted.\n", accNum);
            return 0;
        }
        else 
        {
            prev = current;
            current = (*current).next;
        }
    }
    printf("The account number was not found.\n");
    return -1;
}
/****************************************************************
//    Function name:  writefile
//
////  Description: Stores all of the record information into the a file.
////  
////  Parameters: struct record* rec: pointer to the start of the linked list
//                char recInfo[ ]: name of the file
////  
////  Return values: 0: successfully wrote records to file.
////
////
*************************************************************/
int writefile(struct record * rec, char recInfo[ ])
{
    FILE *file;
    struct record* current;
    file = fopen(recInfo, "w");
    current = rec;

    while (current != NULL)
    {
        fprintf(file, "%d\n", (*current).accountno);
        fprintf(file, "%s\n", (*current).name);
        fprintf(file, "%s\n\n", (*current).address);
        current = (*current).next;
    }
    fclose(file);

    if (debugmode == 1)
    {
        printf("Records have been saved to file\n");
    }
    return 0;
}
/****************************************************************
//    Function name:  readFile
//
////  Description: Reads information from a file and adds them to a linked list
////  
////  Parameters: struct record** rec: pointer to a pointer of the start of the linked list
//                char recInfo[ ]: name of file..
////  
////  Return values: 0: Information from files were successfully added to linked list.
////
////
*************************************************************/
int readfile(struct record ** rec, char recInfo[ ])
{
    FILE *file;
    int accNum;
    char line[45];
    char name[25];
    char address[45];
    int read;

    file = fopen(recInfo, "r");

    if (file == NULL)
    {
        return 0;
    }
    
    while (fscanf(file, "%d\n", &accNum) != EOF)
    {
        fgets(name, sizeof(name), file);
        name[strcspn(name, "\n")] = '\0';
        address[0] = '\0';
        read = 1;
        while (read)
        {
            if (fgets(line, sizeof(line), file) == NULL)
            {
                read = 0;
            }
            else
            {
                line[strcspn(line, "\n")] = '\0';
                if (line[0] == '\0')
                {
                    read = 0;
                }
                else
                {
                    strcat(address, line);
                    strcat(address, "\n");
                }
            }
        }
        addRecord(rec, accNum, name, address);
    }
    fclose(file);
   
    if (debugmode == 1)
    {
        printf("Records have been added from save file.\n");
    }
    return 0;
}
/****************************************************************
//  Function name:  cleanup
//
////  Description: Deallocates the memory used to store linked list.
////  
////  Parameters: struct record** rec: pointer to the start of the linked list
////  
////  Return values: void
////
////
***************************************************************/
void cleanup(struct record ** rec) 
{
    struct record* current;
    struct record* next;
    current = *rec;
    while (current != NULL) 
    {
        next = (*current).next;
        free(current);
        current = next;
    }

    if (debugmode == 1)
    {
        printf("cleanup was called\n");
    }
}
