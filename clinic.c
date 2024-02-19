/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Anna Francesca Dela Cruz
Student ID#: 123123150
Email      : afgdela-cruz@myseneca.ca
Section    : NJJ

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

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
void displayPatientData(const struct Patient *patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ",
               patient->name, patient->patientNumber);
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
void displayScheduleTableHeader(const struct Date *date, int isAllRecords)
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
void displayScheduleData(const struct Patient *patient,
                         const struct Appointment *appoint,
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
// main menu
void menuMain(struct ClinicData *data)
{
    int selection;

    do
    {
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

    do
    {
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
void menuPatientEdit(struct Patient *patient)
{
    int selection;

    do
    {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ",
               patient->patientNumber, patient->name);

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
void menuAppointment(struct ClinicData *data)
{
    int selection;

    do
    {
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
            viewAllAppointments(data); // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data); // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient); // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient); // ToDo: You will need to create this function!
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
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    displayPatientTableHeader();
    int i1;
    for (i1 = 0; i1 < max; i1++)
    {

        if (patient[i1].patientNumber != 0)
        {

            printf("%d  %-15s ", patient[i1].patientNumber, patient[i1].name);
            displayFormattedPhone(patient[i1].phone.number);
            printf(" (%s)\n", patient[i1].phone.description);
        }
    }
    printf("\n");
}

/// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int searchSel;

    printf("Search Options\n==========================\n1) By patient number\n2) By phone number\n..........................\n0) Previous menu\n..........................\nSelection: ");
    scanf("%d", &searchSel);
    printf("\n");

    if (searchSel == 2)
    {
        searchPatientByPhoneNumber(patient, max);
        printf("\n");
        clearInputBuffer();
        suspend();
        searchPatientData(patient, max); // show menu again
    }
    else if (searchSel == 1)
    {
        searchPatientByPatientNumber(patient, max);
        printf("\n");
        clearInputBuffer();
        suspend();
        searchPatientData(patient, max);
    }
}

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int flag = 0;
    int i;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == 0)
        {
            int newPatientNum = nextPatientNumber(patient, max);
            patient[i].patientNumber = newPatientNum;
            inputPatient(&patient[i]);
            printf("*** New patient record added ***\n\n");
            flag = 1;
            i = max;
        }
    }

    if (i == max && flag == 0)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
}

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int patientNumber;
    printf("Enter the patient number: ");
    scanf("%d", &patientNumber);
    clearInputBuffer();
    printf("\n");
    int patientIdx = findPatientIndexByPatientNum(patientNumber, patient, max);
    if (patientIdx != -1)
    {
        // updateAppointmentFile("appointmentData.txt", max, patientNumber);
        menuPatientEdit(&patient[patientIdx]);
    }
    else
    {
        printf("ERROR: Patient record not found!\n");
    }
}

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    int patientNumber;
    printf("Enter the patient number: ");
    scanf("%d", &patientNumber);
    clearInputBuffer();
    int patientIdx = findPatientIndexByPatientNum(patientNumber, patient, max);
    char answer;
    if (patientIdx != -1)
    {
        displayPatientData(&patient[patientIdx], FMT_FORM);
        printf("\nAre you sure you want to remove this patient record? (y/n): ");
        answer = inputCharOption("yn");

        if (answer == 'y')
        {
            patient[patientIdx].patientNumber = 0;
            printf("Patient record has been removed!\n\n");
        }
        else
        {
            printf("Operation aborted.\n");
        }
    }
    else
    {
        printf("\nERROR: Patient record not found!\n\n");
    }
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData *data)
{
    // get appointment count
    int appointmentCount = importAppointments("appointmentData.txt", data->appointments, MAX_APPOINTMENTS);

    // display header
    displayScheduleTableHeader(&(data->appointments->date), 1);

    // declare variables
    int yearTotal, monthTotal, dayTotal, hourTotal;
    double minTotal, dateTotal;
    double sortedDateTotals[appointmentCount], dateTotals[appointmentCount];
    int indexesOfApts[appointmentCount];
    double temp = 0.0;

    // To sort appointments by date, first subtract dates with base date: 2020/1/1
    int baseYear = 2020, baseMonth = 1, baseDay = 1;
    int i2;
    for (i2 = 0; i2 < appointmentCount; i2++)
    {
        // For some reason, values of 10 in the appointment file were changed to 1 when importing to array; the loop corrects that
        if (data->appointments[i2].time.hour == 1)
        {
            data->appointments[i2].time.hour = 10;
        }

        // subtract each appointment date from base date and convert the sum to hours
        yearTotal = (data->appointments[i2].date.year - baseYear) * 8760;
        monthTotal = (data->appointments[i2].date.month - baseMonth) * 730;
        dayTotal = (data->appointments[i2].date.day - baseDay) * 24;
        hourTotal = data->appointments[i2].time.hour;
        minTotal = (data->appointments[i2].time.min == 30) ? 0.5 : 0;

        // add sums and store value in dateTotal
        dateTotal = yearTotal + monthTotal + dayTotal + hourTotal + minTotal;

        /* store each total in two arrays:
        dateTotals' indexes will be used later to keep track of which total/date belongs to which patient once sortedDateTotals is sorted) */
        dateTotals[i2] = dateTotal;
        sortedDateTotals[i2] = dateTotal;
    }

    // sort time difference totals from greatest to least
    // This loop was based on this tutorial: https://www.tutorialspoint.com/c-program-to-sort-an-array-of-ten-elements-in-an-ascending-order
    int i3, j3, j4, i4, i5;
    for (i3 = 0; i3 < appointmentCount; i3++)
    {
        for (j3 = i3 + 1; j3 < appointmentCount; j3++)
        {
            if (sortedDateTotals[i3] > sortedDateTotals[j3])
            {
                temp = sortedDateTotals[i3];
                sortedDateTotals[i3] = sortedDateTotals[j3];
                sortedDateTotals[j3] = temp;
            }
        }
    }

    int idxOfpatientsWithApps[appointmentCount];
    int sortedPatientNums[appointmentCount];

    // get indexes of unsorted appointment totals based on their corresponding value in sortedDateTotals
    for (j4 = 0; j4 < appointmentCount; j4++)
    {
        for (i4 = 0; i4 < appointmentCount; i4++)
        {
            if (dateTotals[j4] == sortedDateTotals[i4])
            {
                indexesOfApts[i4] = j4;
            }
        }
    }

    // rearrange patient numbers based on sorted appointment dates
    int counter = 0;
    for (i5 = 0; i5 < appointmentCount; i5++)
    {
        sortedPatientNums[counter] = data->appointments[indexesOfApts[i5]].patientNum;
        counter++;
    }

    // get the indexes of patient numbers in patient struct with values that match the patient numbers in sortedPatientNums
    int i6, j6;
    for (i6 = 0; i6 < appointmentCount; i6++)
    {
        for (j6 = 0; j6 < MAX_INPUT_LENGTH; j6++)
        {
            if (data->patients[j6].patientNumber == sortedPatientNums[i6])
            {
                idxOfpatientsWithApps[i6] = j6;
            }
        }
    }

    // diplay appointments
    int c = 0;
    while (c != appointmentCount)
    {
        displayScheduleData(&(data->patients[idxOfpatientsWithApps[c]]), &(data->appointments[indexesOfApts[c]]), 1);
        c++;
    }
    printf("\n");
};

// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData *data)
{
    int yr = 0, mon = 0, day = 0, daysInMonth = 0;

    printf("Year        : ");
    scanf("%d", &yr);
    printf("Month (1-12): ");
    mon = inputIntRange(1, 12);
    data->appointments->date.month = mon;

    // determine number of days in a month (consider leap years)
    daysInMonth = findDaysInMonth(mon, yr);

    printf("Day (1-%d)  : ", daysInMonth);
    day = inputIntRange(1, daysInMonth);
    data->appointments->date.day = day;
    printf("\n");
    displayScheduleTableHeader(&data->appointments->date, 0);

    // diplay appointments
    showAppointmentsByDate(data, mon, day, yr);

    printf("\n");
};

// Add an appointment record to the appointment array
void addAppointment(struct Appointment *appointments, int maxAppointments, struct Patient *patients, int maxPatient)
{
    int patNum, yr = 0, mon = 0, day = 0, hr = 0, min = 0, daysInMonth = 0;
    int apmntAvailable = 0;

    // checks if appointment array has room for more; If so, returns index of empty spot
    int idxOfEmptyApmnt = isAppointmentArrayEmpty(appointments, maxAppointments);

    if (idxOfEmptyApmnt != -1) // if the appointment array is not full
    {
        printf("Patient Number: ");
        scanf("%d", &patNum);

        do
        {

            printf("Year        : ");
            scanf("%d", &yr);

            printf("Month (1-12): ");
            mon = inputIntRange(1, 12);

            // determine number of days in a month (consider leap years)
            daysInMonth = findDaysInMonth(mon, yr);

            printf("Day (1-%d)  : ", daysInMonth);
            day = inputIntRange(1, daysInMonth);

            printf("Hour (0-23)  : ");
            hr = inputIntRange(0, 23);

            printf("Minute (0-59): ");
            min = inputIntRange(0, 59);

            // check if specified time is available
            apmntAvailable = checkAppointmentAvailability(appointments, yr, mon, day, hr, min, maxAppointments);

            if (apmntAvailable == 0)
            {
                printf("\nERROR: Appointment timeslot is not available!\n\n");
            }

            while (!(((hr >= 10 && hr < 14) && (min == 30 || min == 0)) || (hr == 14 && min == 0)) && apmntAvailable == 1)
            {
                // validate time input
                if (!(((hr >= 10 && hr < 14) && (min == 30 || min == 0)) || (hr == 14 && min == 0)) && apmntAvailable == 1)
                {
                    printf("ERROR: Time must be between 10:00 and 14:00 in 30 minute intervals.\n\n");
                    printf("Hour (0-23)  : ");
                    scanf("%d", &hr);

                    printf("Minute (0-59): ");
                    scanf("%d", &min);
                    clearInputBuffer();
                    apmntAvailable = checkAppointmentAvailability(appointments, yr, mon, day, hr, min, maxAppointments);
                }
            }
        } while (apmntAvailable == 0);

        // add to appointment array if available
        if (apmntAvailable == 1)
        {
            // add new apporintment to appointment struct
            appointments[idxOfEmptyApmnt].patientNum = patNum;
            appointments[idxOfEmptyApmnt].date.year = yr;
            appointments[idxOfEmptyApmnt].date.month = mon;
            appointments[idxOfEmptyApmnt].date.day = day;
            appointments[idxOfEmptyApmnt].time.hour = hr;
            appointments[idxOfEmptyApmnt].time.min = min;
            printf("\n*** Appointment scheduled! ***\n\n");

            // write new appointment to file
            writeToAppointmentFile("appointmentData.txt", maxAppointments, patNum, yr, mon, day, hr, min);
        }
    }
};

// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment *appointments, int maxAppointments, struct Patient *patients, int maxPatient)
{

    int patNum, yr = 0, mon = 0, day = 0, daysInMonth = 0, patientExists = -1;
    char answer;

    printf("Patient Number: ");
    scanf("%d", &patNum);
    clearInputBuffer();

    // verify patient exists
    patientExists = findPatientIndexByPatientNum(patNum, patients, maxPatient);

    if (patientExists != -1)
    {
        printf("Year        : ");
        scanf("%d", &yr);

        printf("Month (1-12): ");
        mon = inputIntRange(1, 12);

        // determine number of days in a month (consider leap years)
        daysInMonth = findDaysInMonth(mon, yr);

        printf("Day (1-%d)  : ", daysInMonth);
        day = inputIntRange(1, daysInMonth);
        printf("\n");

        // find index of existing patient
        int patientIdx = findPatientIndexByPatientNum(patNum, patients, maxPatient);

        if (patientIdx != -1)
        {
            displayPatientData(&patients[patientIdx], FMT_FORM);

            printf("\nAre you sure you want to remove this appointment? (y/n): ");
            scanf(" %c", &answer);
            clearInputBuffer();

            if (answer == 'y')
            {
                removeAppointmentFromFile("appointmentData.txt", maxPatient, patNum, yr, mon, day);
                printf("\nAppointment record has been removed!\n");
            }
            else
            {
                printf("Operation aborted.\n");
            }
        }
        else
        {
            printf("*** No records found ***\n\n");
        }

        printf("\n");
    }
    else
    {
        printf("\nERROR: Patient record not found!\n");
    }
};

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

/// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patientNumber;
    printf("Search by patient number: ");
    scanf("%d", &patientNumber);
    printf("\n");
    int patientIdx = findPatientIndexByPatientNum(patientNumber, patient, max);
    if (patientIdx != -1)
    {
        displayPatientData(&patient[patientIdx], FMT_FORM);
    }
    else
    {
        printf("*** No records found ***\n");
    }
}

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int flag = 0;

    char patientPhone[PHONE_LEN + 1];
    printf("Search by phone number: ");
    scanf("%s", patientPhone);
    printf("\n");
    displayPatientTableHeader();
    int i;
    for (i = 0; i < max; i++)
    {
        if (strcmp(patientPhone, patient[i].phone.number) == 0)
        {
            printf("%05d  %-15s ", patient[i].patientNumber, patient[i].name);
            displayFormattedPhone(patient[i].phone.number);
            printf(" (%s)\n", patient[i].phone.description);
            flag = 1;
        }
        else if ((strcmp(patientPhone, patient[i].phone.number) != 0) && i == max - 1 && flag == 0)
        {
            printf("\n\n*** No records found ***\n\n");
        }
    }
}

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int highestNum = 0;
    int i;
    for (i = 0; i < max; i++)
    {
        if (highestNum < patient[i].patientNumber)
        {
            highestNum = patient[i].patientNumber;
        }
    }
    return highestNum + 1;
}

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    int result = -1;
    int i;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == patientNumber)
        {
            result = i;
        }
    }
    return result;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient *patient)
{
    printf("Patient Data Input\n------------------\n");
    printf("Number: 0%d\n", patient->patientNumber);
    printf("Name  :  ");
    inputCString(patient->name, 1, 15);
    printf("\n");
    inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
void inputPhoneData(struct Phone *phone)
{
    int selection;
    printf("Phone Information\n-----------------\nHow will the patient like to be contacted?\n1. Cell\n2. Home\n3. Work\n4. TBD\nSelection: ");
    scanf("%d", &selection);
    clearInputBuffer();

    printf("\n");

    switch (selection)
    {
    case 1:
        printf("Contact: CELL\n");
        printf("Number : ");
        verifyPhoneNumber(phone);
        strcpy(phone->description, "CELL");
        break;
    case 2:
        printf("Contact: HOME\n");
        printf("Number : ");
        verifyPhoneNumber(phone);
        strcpy(phone->description, "HOME");
        break;
    case 3:
        printf("Contact: WORK\n");
        printf("Number : ");
        verifyPhoneNumber(phone);
        strcpy(phone->description, "WORK");
        break;
    case 4:
        strcpy(phone->description, "TBD");
        break;
    }
    printf("\n");
}

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

/*
- Read the data file (file name is provided in the first argument)
- Store the data to the second argument, an array of the respective struct data type
- Respect the array size specified by the 3rd argument even when the data file has more records
- Must return the total number of records read from the file and stored to the array, which may be less than the total number of records in the file
*/

// Import patient data from file into a Patient array (returns # of records read)
// Source: https://intro2c.sdds.ca/E-Secondary-Storage/text-files
// I was having trouble getting the function to work so I asked Stack Overfow users for help:
// https://stackoverflow.com/questions/75968613/how-do-i-read-rows-from-a-txt-file-with-missing-data-and-print-them/75972677#75972677
int importPatients(const char *datafile, struct Patient patients[], int max)
{
    FILE *fp = NULL;

    int counter = 0;
    char str[100];

    fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        while (fgets(str, 50, fp))
        {
            if (counter != MAX_PETS)
            {
                sscanf(str, "%d|%30[^|]|%4[^|]|%s", &patients[counter].patientNumber, patients[counter].name, patients[counter].phone.description, patients[counter].phone.number);

                counter++;
            }
        }
        fclose(fp);
    }
    return counter;
}

// Import appointment data from file into an Appointment array (returns # of records read)
// Sources: https://intro2c.sdds.ca/E-Secondary-Storage/text-files
// https://stackoverflow.com/questions/75968613/how-do-i-read-rows-from-a-txt-file-with-missing-data-and-print-them/75972677#75972677
int importAppointments(const char *datafile, struct Appointment appoints[], int max)
{
    FILE *fp = NULL;

    int counter = 0;
    char str[100];

    fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        while (fgets(str, 50, fp))
        {
            if (counter != MAX_APPOINTMENTS)
            {
                sscanf(str, "%d,%d,%d,%d,%d,%d", &appoints[counter].patientNum, &appoints[counter].date.year, &appoints[counter].date.month, &appoints[counter].date.day, &appoints[counter].time.hour, &appoints[counter].time.min);
                counter++;
            }
        }
        fclose(fp);
    }
    return counter;
}

//////////////// MY OWN ADDITIONAL FUNCTIONS ////////////////

// sort appointments by date and time (similar function to viewAllAppointments())
void showAppointmentsByDate(struct ClinicData *data, int month, int day, int year)
{
    int appointmentCount = importAppointments("appointmentData.txt", data->appointments, MAX_APPOINTMENTS);

    int yearTotal, monthTotal, dayTotal, hourTotal;
    double minTotal, dateTotal;
    double sortedDateTotals[appointmentCount], dateTotals[appointmentCount];
    int indexesOfApts[appointmentCount];
    double temp = 0.0;

    // subtract appointment dates with base date (2020/January/1)
    int baseYear = 2020, baseMonth = 1, baseDay = 1;

    // for some reason, values of 10 in the file were changed to 1 when storing in array; this loop corrects this
    int i1;
    for (i1 = 0; i1 < appointmentCount; i1++)
    {
        if (data->appointments[i1].time.hour == 1)
        {
            data->appointments[i1].time.hour = 10;
        }
        // Calculate time between appointment date and base date
        yearTotal = (data->appointments[i1].date.year - baseYear) * 8760;
        monthTotal = (data->appointments[i1].date.month - baseMonth) * 730;
        dayTotal = (data->appointments[i1].date.day - baseDay) * 24;
        hourTotal = data->appointments[i1].time.hour;
        minTotal = (data->appointments[i1].time.min == 30) ? 0.5 : 0;

        // store totals in array
        dateTotal = yearTotal + monthTotal + dayTotal + hourTotal + minTotal;

        // store each total in two arrays
        //(dateTotals' indexes will be used later to keep track of which total/date belongs to which patient once sortedDateTotals is sorted)
        dateTotals[i1] = dateTotal;
        sortedDateTotals[i1] = dateTotal;
    }

    // sort time difference totals from greatest to least
    // This loop was based on this tutorial: https://www.tutorialspoint.com/c-program-to-sort-an-array-of-ten-elements-in-an-ascending-order
    int i2, j2;
    for (i2 = 0; i2 < appointmentCount; i2++)
    {
        for (j2 = i2 + 1; j2 < appointmentCount; j2++)
        {
            if (sortedDateTotals[i2] > sortedDateTotals[j2])
            {
                temp = sortedDateTotals[i2];
                sortedDateTotals[i2] = sortedDateTotals[j2];
                sortedDateTotals[j2] = temp;
            }
        }
    }

    int idxOfpatientsWithApps[appointmentCount];
    int sortedPatientNums[appointmentCount];

    // sort indexes of original appointment data (dateTotals[]) based on their corresponding value in sortedDateTotals
    int j;
    for (j = 0; j < appointmentCount; j++)
    {
        int y;
        for (y = 0; y < appointmentCount; y++)
        {
            if (dateTotals[j] == sortedDateTotals[y])
            {
                indexesOfApts[y] = j;
            }
        }
    }

    // rearrange patient numbers based on sorted appointments
    int counter = 0, i3;
    for (i3 = 0; i3 < appointmentCount; i3++)
    {
        sortedPatientNums[counter] = data->appointments[indexesOfApts[i3]].patientNum;
        counter++;
    }

    // locate patient in patient struct by appointment and patient num
    int i4, j4;
    for (i4 = 0; i4 < appointmentCount; i4++)
    {
        for (j4 = 0; j4 < MAX_INPUT_LENGTH; j4++)
        {
            if (data->patients[j4].patientNumber == sortedPatientNums[i4])
            {
                idxOfpatientsWithApps[i4] = j4;
            }
        }
    }

    // diplay appointments of specific dates
    int c = 0;
    while (c != appointmentCount)
    {
        // finds appointments based on specified date
        if (data->appointments[indexesOfApts[c]].date.month == month && data->appointments[indexesOfApts[c]].date.day == day && data->appointments[indexesOfApts[c]].date.year == year)
        {
            displayScheduleData(&(data->patients[idxOfpatientsWithApps[c]]), &(data->appointments[indexesOfApts[c]]), 0);
        }
        c++;
    }
}

// checks if appointment array is empty; Needed when user wants to add new appointment
int isAppointmentArrayEmpty(struct Appointment *appointments, int maxAppointments)
{
    int iz, result, flag = 0;
    for (iz = 0; iz < maxAppointments; iz++)
    {
        if (appointments[iz].date.month == 0) // check if appointment array is empty
        {
            result = iz;
            flag = 1;
            iz = maxAppointments;
        }

        if (iz == maxAppointments && flag == 0)
        {
            printf("%d\n", maxAppointments);
            printf("ERROR: Patient listing is FULL!\n\n");
            result = -1;
        }
    }
    return result;
}

// determine number of days in a month (consider leap years)
int findDaysInMonth(int mon, int yr)
{
    int daysInMonth;

    if (mon == 4 || mon == 6 || mon == 9 || mon == 11)
    {
        daysInMonth = 30;
    }
    else if (mon == 2)
    {
        if (yr == 2024 || yr == 2028 || yr == 2032 || yr == 2036 || yr == 2040 || yr == 2044)
        {
            daysInMonth = 29;
        }
        else
        {
            daysInMonth = 28;
        }
    }
    else
    {
        daysInMonth = 31;
    }

    return daysInMonth;
}

// checks if appointment time is available
int checkAppointmentAvailability(struct Appointment *appointments, int yr, int mon, int day, int hr, int min, int maxAppointments)
{
    int i, result = 1, flag = 0;
    for (i = 0; i < maxAppointments; i++)
    {
        if (appointments[i].date.year == yr)
        {
            if (appointments[i].date.month == mon)
            {
                if (appointments[i].date.day == day)
                {

                    if (appointments[i].time.hour == hr)
                    {
                        if (appointments[i].time.min == min)
                        {
                            result = 0;
                            flag = 1;
                            i = maxAppointments;
                        }
                    }
                }
            }
        }
        else if (i == maxAppointments && flag == 0)
        {
            result = 1;
        }
    }

    return result;
}

// Updates appointment file when user adds appointment in system
// Source of code: https://intro2c.sdds.ca/E-Secondary-Storage/text-files
void writeToAppointmentFile(const char *datafile, int max, int patNum, int yr, int mon, int day, int hr, int min)
{

    FILE *fp = NULL;

    fp = fopen(datafile, "a");

    if (fp != NULL)
    {
        fprintf(fp, "\n%d,%d,%d,%d,%d,%d", patNum, yr, mon, day, hr, min);
        fclose(fp);
    }
    else
    {
        printf("Failed to open file\n");
    }
}

// remove appointment in file using index of line
// function inspired by Stack Overflow user, "user3115056": https://stackoverflow.com/questions/20716785/how-do-i-delete-a-specific-line-from-text-file-in-c
void removeAppointmentFromFile(const char *datafile, int max, int patNum, int yr, int mon, int day)
{
    int fpatNum, fyr, fmon, fday, fhr, fmin, counter = 0;
    int numOfLines = 0;
    char str[100];

    FILE *fp = NULL, *tempFile = NULL;

    fp = fopen(datafile, "r+");

    if (fp != NULL)
    {
        // read through lines of file and find line that matches appointment to be deleted
        while (fgets(str, 50, fp))
        {
            sscanf(str, "%d,%d,%d,%d,%d,%d", &fpatNum, &fyr, &fmon, &fday, &fhr, &fmin);
            counter++;
            if (fpatNum == patNum && fyr == yr && fmon == mon && fday == day)
            {
                break;
            }
        }
        // rewind file
        rewind(fp);

        // create temporary file to store data except deleted line/appointment
        tempFile = fopen("temp.txt", "a");

        if (tempFile != NULL)
        {

            while (fgets(str, 50, fp) && feof(fp) == 0)
            {
                if (numOfLines != counter - 1)
                {
                    sscanf(str, "%d,%d,%d,%d,%d,%d", &fpatNum, &fyr, &fmon, &fday, &fhr, &fmin);
                    fprintf(tempFile, "%d,%d,%d,%d,%d,%d\n", fpatNum, fyr, fmon, fday, fhr, fmin); // print lines from OG file to temporary file
                    numOfLines++;
                }
                else if (numOfLines == counter - 1)
                {
                    numOfLines++; // skip deleted line when copying lines fom OG file to temp file
                }
            }

            fclose(tempFile);
            fclose(fp);
        }
        else
        {
            printf("Failed to open temporary file\n");
        }
        fclose(fp);
    }
    else
    {
        printf("Failed to open original appointment file\n");
    }
    // remove original file
    remove("appointmentData.txt");

    // rename the temporary file to original file
    rename("temp.txt", "appointmentData.txt");
}

// checks if phone number is 10 digits long
void verifyPhoneNumber(struct Phone *phone)
{
    do
    {
        scanf("%s", phone->number);
        clearInputBuffer();

        if (strlen(phone->number) != 10)
        {
            printf("Invalid 10-digit number! Number: ");
        }

    } while (strlen(phone->number) != 10);
}
