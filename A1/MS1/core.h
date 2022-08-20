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
// Clear the standard input buffer 
void clearInputBuffer(void);
// Wait for user to input the "enter" key to continue 
void suspend(void);
char inputCharOption(const char*);
int inputInt();
int inputIntPositive();
int inputIntRange(int, int);
void inputCString(char*, int, int);
void displayFormattedPhone(const char*);
void cpy(char*, const char*);
const char* idx(const char*, char);
int len(const char*);