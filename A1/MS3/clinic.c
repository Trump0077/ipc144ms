/*
*****************************************************************************
                        Assignment 1 - Milestone 3
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
#include <stdlib.h>


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

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu (hub) for application
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
            menuAppointment(data);
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


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData* data)
{
    int i;
    struct Appointment* temp = (struct Appointment*)calloc(data->maxAppointments, 
        sizeof(struct Appointment));

    for (i = 0; i < data->maxAppointments; i++)
    {
        temp[i].patients = data->appointments[i].patients;
        temp[i].date = data->appointments[i].date;
        temp[i].time = data->appointments[i].time;
    }
    qsort(data->appointments, data->maxAppointments, sizeof(struct Appointment), (void*)compareDate);
    displayScheduleTableHeader(&(temp->date), 1);
    for (i = 0; i < data->maxAppointments; i++)
    {
        if (temp[i].patients.patientNumber != 0)
        {
            int index = findPatientIndexByPatientNum(temp[i].patients.patientNumber, 
                data->patients, data->maxPatient);
            displayScheduleData(&data->patients[index], &temp[i], 1);
        }
    }
    putchar('n');
    return;
}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data)
{
    int year, month, day;
    int i;
    printf("Year        : ");
    year = inputIntPositive();
    printf("Month (1-12): ");
    month = inputIntRange(1, 12);
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
    {
        printf("Day (1-29)  : ");
        day = inputIntRange(1, 29);
    }
    else
    {
        printf("Day (1-28)  : ");
        day = inputIntRange(1, 28);
    }
    printf("\n");
    struct Date inputDate;
    inputDate.year = year;
    inputDate.month = month;
    inputDate.day = day;
    displayScheduleTableHeader(&inputDate, 0);
    struct Appointment* temp = (struct Appointment*)calloc(data->maxAppointments, 
        sizeof(struct Appointment));
    for (i = 0; i < data->maxAppointments; i++)
    {
        temp[i].patients = data->appointments[i].patients;
        temp[i].date = data->appointments[i].date;
        temp[i].time = data->appointments[i].time;
    }
    qsort(data->appointments, data->maxAppointments, sizeof(struct Appointment), (void *)compareDate);

    for (i = 0; i < data->maxAppointments; i++)
    {
        if (temp[i].patients.patientNumber != 0
            && temp[i].date.year == inputDate.year
            && temp[i].date.month == inputDate.month
            && temp[i].date.day == inputDate.day)
        {
            int index = findPatientIndexByPatientNum(temp[i].patients.patientNumber, 
                data->patients, data->maxPatient);
            displayScheduleData(&data->patients[index], &temp[i], 0);
        }
    }
    printf("\n");
    return;
}

// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment* apt, int maxapt, struct Patient* pat, int maxpat)
{
    int patientNum;
    int year, month, day, hour, min;
    int i;
    int avaliable = 0;
    int full = 1;

    for (i = 0; i < maxapt; i++)
    {
        if (apt[i].patients.patientNumber < 1)
        {
            full = 0;
            break;
        }
    }
    if (full == 1)
        printf("ERROR: Appointment listing is FULL!\n");
    printf("Patient Number: ");
    patientNum = inputIntPositive();
    int index = findPatientIndexByPatientNum(patientNum, pat, maxpat);
    if (index == -1)
        printf("ERROR: Patient record not found!\n");  
    while (1)
    {
        printf("Year        : ");
        year = inputIntPositive();
        printf("Month (1-12): ");
        month = inputIntRange(1, 12);
        if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
        {
            printf("Day (1-29)  : ");
            day = inputIntRange(1, 29);
        }
        else
        {
            printf("Day (1-28)  : ");
            day = inputIntRange(1, 28);
        }
        printf("Hour (0-23)  : ");
        hour = inputIntRange(0, 23);
        printf("Minute (0-59): ");
        min = inputIntRange(0, 59);
        for (i = 0; i < maxapt; i++)
        {
            if (apt[i].date.year == year &&
                apt[i].date.month == month &&
                apt[i].date.day == day &&
                apt[i].time.hour == hour &&
                apt[i].time.min == min)
            {
                printf("\nERROR: Appointment timeslot is not available!\n");
                avaliable = 0;
                break;
            }
            avaliable = 1;
        }
        if (avaliable == 0)
            continue;
        while (1)
        {
            int input = hour * 60 + min;
            if (input % INTERVAL != 0 || input < START_HOUR * 60 + START_MIN ||
                input > END_HOUR * 60 + END_MIN)
            {
                printf("ERROR: Time must be between %02d:%02d and %02d:%02d in %d minute intervals.\n",
                    START_HOUR, START_MIN, END_HOUR, END_MIN, INTERVAL);
                printf("Hour (0-23)  : ");
                hour = inputIntRange(0, 23);
                printf("Minute (0-59): ");
                min = inputIntRange(0, 59);
                avaliable = 0;
            }
            else
            {
                avaliable = 1;
                break;
            }
        }
        if (avaliable == 1) break;
    }
    for (i = 0; i < maxapt; i++)
    {
        if (apt[i].patients.patientNumber < 1)
        {
            apt[i].patients.patientNumber = patientNum;
            apt[i].date.year = year;
            apt[i].date.month = month;
            apt[i].date.day = day;
            apt[i].time.hour = hour;
            apt[i].time.min = min;
            break;
        }
    }
    printf("\n*** Appointment scheduled! ***\n\n");
    return;
}

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* apt, int maxapt, struct Patient* pat, int maxpat)
{
    int patientNum;
    int year, month, day;
    int i;

    printf("Patient Number: ");
    patientNum = inputIntPositive();
    int index = findPatientIndexByPatientNum(patientNum, pat, maxpat);
    if (index == -1)
    {
        printf("ERROR: Patient record not found!\n");
        return;
    }
    printf("Year        : ");
    year = inputIntPositive();
    printf("Month (1-12): ");
    month = inputIntRange(1, 12);
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
    {
        printf("Day (1-29)  : ");
        day = inputIntRange(1, 29);
    }
    else
    {
        printf("Day (1-28)  : ");
        day = inputIntRange(1, 28);
    }
    putchar('n');
    printf("Name  : %s\n", pat[index].name);
    printf("Number: %05d\n", pat[index].patientNumber);
    printf("Phone : ");
    displayFormattedPhone(pat[index].phone.number);
    printf(" (%s)\n", pat[index].phone.description);
    printf("Are you sure you want to remove this appointment (y,n): ");
    char answer;
    answer = inputCharOption("yn");
    if (answer == 'n')
    {
        printf("Operation aborted.n");
    }
    else
    {
        for (i = 0; i < maxapt; i++)
        {
            if (apt[i].patients.patientNumber == patientNum &&
                apt[i].date.year == year &&
                apt[i].date.month == month &&
                apt[i].date.day == day)
            {
                apt[i].patients.patientNumber = 0;
                break;
            }
        }
        printf("\n*** Appointment record has been removed! ***\n");
    }
    printf("\n");
    return;
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
            if ((phone_num[i])<'0' || (phone_num[i])>'9')
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
                    displayPatientData(patient + i, FMT_TABLE);
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 3, NAME_LEN);
    printf("\n");
    inputPhoneData(&patient->phone);
    return;
}

// Get user input for phone contact information
// (Copy your code from MS#2)
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



//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int n = 0;

    FILE* fp;
    fp = fopen(datafile, "r");
    if (fp != NULL)
    {
        while (fscanf(fp, "%d|%[^|]|%[^|]|%[^n]",
            &patients[n].patientNumber,
            patients[n].name,
            patients[n].phone.description,
            patients[n].phone.number) != EOF)
        {
            n++;
            if (n >= max) break;
        }
    }
    else
    {
        printf("Failed to open file %s!!!\n", datafile);
        printf("Program is exiting...\n");
    }
    return n;
}


// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* datafile, struct Appointment appointments[], int max)
{
    int n = 0;

    FILE* fp;
    fp = fopen(datafile, "r");
    if (fp != NULL)
    {
        while (fscanf(fp, "%d,%d,%d,%d,%d,%d",
            &appointments[n].patients.patientNumber,
            &appointments[n].date.year,
            &appointments[n].date.month,
            &appointments[n].date.day,
            &appointments[n].time.hour,
            &appointments[n].time.min) != EOF)
        {
            n++;
            if (n >= max) break;
        }
    }
    else
    {
        printf("Failed to open file %s!!!\n", datafile);
        printf("Program is exiting...\n");
    }
    return n;
}

int compareDate(struct Appointment* apt1, struct Appointment* apt2)
{
    if (apt1->date.year < apt2->date.year) return -1;
    if (apt1->date.year > apt2->date.year) return 1;

    if (apt1->date.month < apt2->date.month) return -1;
    if (apt1->date.month > apt2->date.month) return 1;

    if (apt1->date.day < apt2->date.day) return -1;
    if (apt1->date.day > apt2->date.day) return 1;

    if (apt1->time.hour < apt2->time.hour) return -1;
    if (apt1->time.hour > apt2->time.hour) return 1;

    if (apt1->time.min< apt2->time.min) return -1;
    if (apt1->time.min > apt2->time.min) return 1;

    return 0;
}


