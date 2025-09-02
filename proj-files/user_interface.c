/*****************************************************************
//
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
//  FILE:        user_interface.c
//
//  DESCRIPTION:
//   Captures user input to send to functions in database.c
//   
****************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "database.h"
#include "record.h"
void getaddress(char address[ ], int size);
int debugmode;
/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   Captures user input to send to functions in
//                 database.c
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//
//  Return values:  0 : success
//                 
//
****************************************************************/

int main(int argc, char* argv[])
{
    struct record * start = NULL;
    char choice[45];
    int accNumber;
    char name[25];
    char address[45];
    int alphCheck;

    if ((argc == 2) && (strcmp(argv[1],"debug") == 0)) 
    {
        debugmode = 1;
        printf("Debug mode\n");
    }
    else if (argc == 1) 
    {
        debugmode = 0;
    }
    else
    {
        printf("Invalid command");
        exit(0);
    }
    
    readfile(&start, "savedRecs.txt");
    printf("Hello, choose one of the menu options below:\n");
    printf("add: Add a record.\n");
    printf("printall: Print all existing records\n");
    printf("find: Find a record.\n");
    printf("delete: Delete a record by account number.\n");
    printf("quit: Exit program.\n");

    while(1)
    {
        printf("Choose an option: ");
        scanf("%s", choice);
        if (strncmp(choice, "add", strlen(choice)) == 0 && strlen(choice) <= strlen("add"))
        {
            printf("Enter account number:\n");
            alphCheck = scanf("%d", &accNumber);
            while (accNumber <= 0 || alphCheck != 1)
            {
                printf("Account number must be a positive integer:\n");
                while(getchar() != '\n');
                alphCheck = scanf("%d", &accNumber);
            }
            while(getchar() != '\n');
            printf("Enter name:\n");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';
            getaddress(address, 45);
            addRecord(&start, accNumber, name, address); 
        } 
        else if (strncmp(choice, "quit", strlen(choice)) == 0 && strlen(choice) <= strlen("quit"))
        {
            writefile(start, "savedRecs.txt");
            cleanup(&start);
            exit(0);
        }
        else if (strncmp(choice, "printall", strlen(choice)) == 0 && strlen(choice) <= strlen("printall"))
        {
            printAllRecords(start);
        }
        else if (strncmp(choice, "find", strlen(choice)) == 0 && strlen(choice) <= strlen("find"))
        {
            printf("Enter the account number that you would like to find:\n");
            alphCheck = scanf("%d",&accNumber);
            while (accNumber <= 0 || alphCheck != 1)
            {
                printf("Account number must be a positive integer:\n");
                while(getchar() != '\n');
                alphCheck = scanf("%d", &accNumber);
            }
            while(getchar() != '\n');
            findRecord(start, accNumber);
        }
        else if (strncmp(choice, "delete", strlen(choice)) == 0 && strlen(choice) <= strlen("delete"))
        {
            printf("Enter the account number that you would like to delete:\n");
            alphCheck = scanf("%d", &accNumber);
            while (accNumber <= 0 || alphCheck != 1)
            {
                printf("Account number must be a positive integer:\n");
                while(getchar() != '\n');
                alphCheck = scanf("%d", &accNumber);
            }
            while(getchar() != '\n');
            deleteRecord(&start,accNumber);
        }
        else
        {
            printf("Invalid menu option.\n");
        }   
    }      
    return 0;
}

/*****************************************************************
//
//  Function name:  getaddress
//
//  DESCRIPTION:   Captures an address from the user and ensures that
//                 they are able to make new lines but will capture 
//                 the input once two new lines are detected.
//                 
//
//  Parameters:    size (int) : size of char array to be modified.
//
//                 address (char*) : char array that will hold the
//                 user address.
//
//  Return values: void
//                 
//
****************************************************************/

void getaddress(char address[ ], int size) 
{
    char input[45];
    int inputSize;
    int totSize;
    int continueInp;
    totSize = 0;
    address[0] = '\0';
    continueInp = 1;

    printf("Enter address and press enter on a new line when finished.\n");
    while (continueInp == 1)
    {
        fgets(input, sizeof(input), stdin);
        
        inputSize = strlen(input);
        if (inputSize > 0 && input[inputSize - 1] == '\n')
        {
            input[inputSize - 1] = '\0';
            inputSize--;
        }
        if (strcmp(input, "") == 0)
        {
            continueInp = 0;
        }
        else
        {
            if (totSize + inputSize < size)
            {
                strcat(address, input);
                totSize += inputSize;
                strcat(address, "\n");
                totSize++;
            }
        }   
    } 
    if (totSize > 0 && address[totSize - 1] == '\n') 
    {
        address[totSize - 1] = '\0';
    }
}
