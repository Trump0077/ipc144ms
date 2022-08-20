/*
*****************************************************************************
                        Assignment 1 - Milestone 1
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

#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include "core.h"

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
        scanf("%c%c", &c, &nl);
        if (!(nl=='\n' && index(s,c)))
        {
            printf("ERROR: Character must be one of [%s]: ", s);
            scan_error = 1;
        }
    } while (scan_error);
    return *(idx(s, c));
}
void inputCString(char* s, int low, int high)
{
    char line[1000] = { 0 };
    int length, invalid_input = 0;
    do {
        scanf("%[^\n]", line);
        length = len(line);
        if (low == high && low != length)
            printf("ERROR: String length must be exactly %d chars: ", low);
        else
        {
            if (length > high)
                printf("ERROR: String length must be no more than %d chars: ", high);
            else 
            {
                if (length < low)
                    printf("ERROR: String length must be between 5 and 6 chars: ", low, high);
                else
                    invalid_input = 1;
            }
        }
        clearInputBuffer();
    } while (!invalid_input);
    cpy(s, line);
    return;
}
void displayFormattedPhone(const char* p)
{
    regex_t regex;
    if (p)
    {
        if (!regcomp(&regex, "[0-9]{10}", REG_EXTENDED | REG_NOSUB))
        {
            if (!regexec(&regex, p, 0, NULL, 0))
            {
                printf("(%c%c%c)%c%c%c-%c%c%c%c", p[0], p[1], p[2], p[3],
                    p[4], p[5], p[6], p[7], p[8], p[9]);
            }
            else
                printf("(___)___-____");
        }
    }
    return;
}
void cpy(char* to, const char* fm)
{
    int i;
    for (i = 0; fm[i] != 0; i++)
        to[i] = fm[i];
    to[i] = 0;
    return;
}
const char* idx(const char* p, char c)
{
    int i; 
    for (i = 0; p[i] != 0; i++)
        if (p[i] == c) break;
    return p[i] ? p + i : 0;
}
int len(const char* s)
{
    int i;
    for (i = 0; s[i] != 0; i++);
    return i;
}