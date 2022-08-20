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
#include <ctype.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            printf("<<< Feature not yet available >>>\n\n");
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! Put all the remaining function definitions below !!!
// Note: Maintain the same order/sequence as it is listed in the header file
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i;
    if (max == 0)
    {
        printf("*** No records found ***\n\n");
        suspend();
    }
    else
    {
        if (fmt != FMT_FORM)
            displayPatientTableHeader();
        for (i = 0; i < max; i++)
            if ((patient + i)->patientNumber != 0)
                displayPatientData(patient + i, fmt);
        printf("\n");
    }
    return;
}


// Search for a patient record based on patient number or phone number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientData(const struct Patient patient[], int max)
{
    int choice;
    do {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        choice = inputIntRange(0, 2);
        switch (choice)
        {
        case 1: searchPatientByPatientNumber(patient, max);
            break;
        case 2: searchPatientByPhoneNumber(patient, max);
            break;
        }
    } while (choice);
    printf("\n");
    return;
}



// Add a new patient record to the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void addPatient(struct Patient patient[], int max)
{
    int index = -1;
    int i;
    int nextNum;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == 0)
            index = i;
    }
    if (index < 0)
    {
        printf("ERROR: Patient listing is FULL!\n");
    }
    else
    {
        nextNum = nextPatientNumber(patient, max);
        patient[index].patientNumber = nextNum;
        inputPatient(patient + index);
    }
    printf("*** New patient record added ***\n\n");
    return;
}


// Edit a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void editPatient(struct Patient patient[], int max)
{
    int patient_num;
    int index = -1;
    printf("Enter the patient number: ");
    patient_num = inputIntPositive();
    printf("\n");
    index = findPatientIndexByPatientNum(patient_num, patient, max);
    if (index < 0)
        printf("ERROR: Patient record not found!\n");
    else
    {
        menuPatientEdit(patient + index);
        printf("\nPatient record updated!\n");
    }
    return;
}


// Remove a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void removePatient(struct Patient patient[], int max)
{
    int patient_num, index = -1;
    char ch;
    printf("Enter patient number: ");
    scanf("%d", &patient_num);
    index = findPatientIndexByPatientNum(patient_num, patient, max);
    if (index < 0)
    {
        printf("\nERROR: Patient record not found!\n\n");
        clearInputBuffer();
    }
    else
    {
        printf("\n");
        displayPatientData(patient + index, FMT_FORM);
        printf("\nAre you sure you want to remove this patient record? (y/n): ");
        ch = inputCharOption("yYnN");
        if (ch == 'Y' || ch == 'y')
        {
            (patient + index)->patientNumber = 0;
            printf("Patient record has been removed!\n\n");
        }
        else
        {
            printf("Operation aborted.\n\n");
        }
    }
    return;
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patient_num, index = -1;
    printf("\nSearch by patient number: ");
    scanf("%d", &patient_num);
    printf("\n");
    index = findPatientIndexByPatientNum(patient_num, patient, max);
    if (index < 0)
    {
        printf("*** No Records Found ***\n");
    }
    else
    {
        displayPatientData(patient + index, FMT_FORM);
    }
    printf("\n");
    suspend();
    return;
}

// Search and display patient records by phone number (tabular)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char phone_num[PHONE_LEN + 1];
    int valid_phone = 1;
    int i, num_displayed = 0;

    do {
        printf("\nSearch by phone number: ");
        inputCString(phone_num, PHONE_LEN, PHONE_LEN);
        printf("\n");
        for (i = 0; i < PHONE_LEN; i++)
            if (!isdigit(phone_num[i])) 
                valid_phone = 0;      
        if (!valid_phone)
            printf("Invalid phone number\n");
        else
        {
            printf("Pat.# Name            Phone#\n");
            printf("----- --------------- --------------------\n");
            for (i = 0; i < max; i++)
            {
                if (!strcmp(phone_num, patient[i].phone.number))
                {
                    displayPatientData(patient+i, FMT_TABLE);
                    num_displayed++;
                }
            }
            if (num_displayed == 0)
                printf("\n*** No records found ***\n");
        }
    } while (!valid_phone);
    printf("\n");
    suspend();
    return;
}

// Get the next highest patient number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int nextPatientNumber(const struct Patient patient[], int max)
{
    int nextNum, largest, i;
    largest = patient[0].patientNumber;
    for (i = 0; i < max; i++)
    {
        if (largest < patient[i].patientNumber)
            largest = patient[i].patientNumber;
    }
    nextNum = largest + 1;
    return nextNum;
}

// Find the patient array index by patient number (returns -1 if not found)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    int i, index;
    for (i = 0; i < max; i++)
    {
        if (patientNumber == patient[i].patientNumber)
        {
            index = i;
            break;
        }
    }
    return index;
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient -> patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 3, NAME_LEN);
    printf("\n");
    inputPhoneData(&patient->phone);
    return;
}

// Get user input for phone contact information
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPhoneData(struct Phone* phone)
{
    int choice;
    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    choice = inputIntRange(0, 4);
    switch (choice)
    {
    case 1: strcpy(phone->description, "CELL");
        break;
    case 2: strcpy(phone->description, "HOME");
        break;
    case 3: strcpy(phone->description, "WORK");
        break;
    case 4: strcpy(phone->description, "TBD");
        break;
    }
    if (choice != 4)
    {
        printf("\nContact: %s\n", phone->description);
        printf("Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN);
        printf("\n");
    }
    else
        printf("\n");
    return;
}
