/*
*****************************************************************************
                        Assignment 1 - Milestone 2
Full Name  :Jiaheng Wang
Student ID#:180562217
Email      :jwang522@myseneca.ca
Section    :NNN

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

//
// Copy your work done from Milestone #1 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
// - Also copy the commented "sections" to help with finding functions quickly!
//

// As demonstrated in the course notes: 
// https://intro2c.sdds.ca/D-Modularity/input-functions#clearing-the-buffer 
// Clear the standard input buffer 
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}
// Wait for user to input the "enter" key to continue 
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}
int inputInt()
{
    char nl;
    int val;
    do {
        scanf("%d%c", &val, &nl);
        if (nl != '\n')
        {
            printf("Error! Input a whole number: ");
            clearInputBuffer();
        }
    } while (nl != '\n');
    return val;
}
int inputIntPositive()
{
    int n;
    do {
        n = inputInt();
        if (n <= 0)
            printf("ERROR! Value must be > 0: ");
    } while (n <= 0);
    return n;
}
int inputIntRange(int min, int max)
{
    int n;
    do {
        n = inputInt();
        if (n<min && n>max)
            printf("ERROR! Value must be between %d and %d inclusive: ", min, max);
    } while (n<min && n>max);
    return n;
}
char inputCharOption(const char* s)
{
    char c, nl;
    int scan_error;
    do {
        scan_error = 0;
        scanf(" %c%c", &c, &nl);
       
        if (strchr(s, c))
            scan_error = 0;
        else
        {
            printf("ERROR: Character must be one of [%s]: ", s);
            scan_error = 1;
        }
    } while (scan_error);
    return c;
}
void inputCString(char* s, int low, int high)
{
    char line[1000] = { 0 };
    int length, invalid_input = 0;
    do {
        scanf("%[^\n]", line);
        length = strlen(line);
        if (low == high && low != length)
            printf("ERROR: String length must be exactly %d chars: ", low);
        else
        {
            if (length > high)
                printf("ERROR: String length must be no more than %d chars: ", high);
            else
            {
                if (length < low)
                    printf("ERROR: String length must be between %d and %d chars: ", low, high);
                else
                    invalid_input = 1;
            }
        }
        clearInputBuffer();
    } while (!invalid_input);
    strcpy(s, line);
    return;
}
void displayFormattedPhone(const char* p)
{
    int i;
    int badNum = 0;
    if (p == NULL || strlen(p) != 10)
        printf("(___)___-____ ");
    else
    {
        for (i = 0; i < 10; i++)
            if (!(p[i] >= '0' && p[i] <= '9'))
                badNum = 1;
        if (!badNum)
            printf("%s ", p);
        else
            printf("(___)___-____ ");
    }
    return;
}
