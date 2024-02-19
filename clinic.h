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

// SAFE-GUARD:
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.
#ifndef CLINIC_H
#define CLINIC_H

//////////////////////////////////////
// Module macro's (usable by any file that includes this header)
//////////////////////////////////////

// Display formatting options (Provided to student)
// !!! DO NOT MODIFY THESE MACRO'S !!!
#define FMT_FORM 1
#define FMT_TABLE 2

// C Strings: array sizes
#define NAME_LEN 15
#define PHONE_DESC_LEN 4
#define PHONE_LEN 10

// MS#3 Additional macro's:
// ToDo:
#define MAX_PETS 20         // same macro in a1ms3.c
#define MAX_APPOINTMENTS 50 // same macro in a1ms3.c

//////////////////////////////////////
// Structures
//////////////////////////////////////

// Data type: Phone
struct Phone
{
    char description[PHONE_DESC_LEN + 1];
    char number[PHONE_LEN + 1];
};

// Data type: Patient
struct Patient
{
    int patientNumber;
    char name[NAME_LEN];
    struct Phone phone;
};

// ------------------- MS#3 -------------------
/*
 appoint->date.year, appoint->date.month, appoint->date.day);

    appoint->time.hour, appoint->time.min,

           */
// Data type: Time
struct Time
{
    int hour;
    int min;
};

// Data type: Date
struct Date
{
    int year;
    int month;
    int day;
};

// Data type: Appointment
struct Appointment
{
    struct Time time;
    struct Date date;
    int patientNum;
};

// ClinicData type: Provided to student
// !!! DO NOT MODIFY THIS DATA TYPE !!!
struct ClinicData
{
    struct Patient *patients;
    int maxPatient;
    struct Appointment *appointments;
    int maxAppointments;
};

//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// Display's the patient table header (table format)
void displayPatientTableHeader(void);

// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient *patient, int fmt);

// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date *date, int isAllRecords);

// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient *patient,
                         const struct Appointment *appoint,
                         int includeDateField);

//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// Menu: Main
void menuMain(struct ClinicData *data);

// Menu: Patient Management
void menuPatient(struct Patient patient[], int max);

// Menu: Patient edit
void menuPatientEdit(struct Patient *patient);

// Menu: Appointment Management
void menuAppointment(struct ClinicData *data);

// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt);

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max);

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max);

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max);

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max);

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData *data);
// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData *data);

// Add an appointment record to the appointment array
void addAppointment(struct Appointment *appointments, int maxAppointments, struct Patient *patients, int maxPatient);

// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment *appointments, int maxAppointments, struct Patient *patients, int maxPatient);

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max);

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max);

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max);

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
                                 const struct Patient patient[], int max);

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient *patient);

// Get user input for phone contact information
void inputPhoneData(struct Phone *phone);

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
// Sources (and I asked on Stack Overflow for help):
// https://intro2c.sdds.ca/E-Secondary-Storage/text-files
// https://stackoverflow.com/questions/75968613/how-do-i-read-rows-from-a-txt-file-with-missing-data-and-print-them/75972677#75972677
int importPatients(const char *datafile, struct Patient patients[], int max);

// Import appointment data from file into an Appointment array (returns # of records read)
// Sources (and I asked on Stack Overflow for help):
// https://intro2c.sdds.ca/E-Secondary-Storage/text-files
// https://stackoverflow.com/questions/75968613/how-do-i-read-rows-from-a-txt-file-with-missing-data-and-print-them/75972677#75972677
int importAppointments(const char *datafile, struct Appointment appoints[], int max);

//////////////// MY OWN ADDITIONAL FUNCTIONS ////////////////

// sort appointments by date and time
void showAppointmentsByDate(struct ClinicData *data, int month, int day, int year);

// checks if appointment array is empty; Needed when user wants to add new appointment
int isAppointmentArrayEmpty(struct Appointment *appointments, int maxAppointments);

// determine number of days in a month (consider leap years)
int findDaysInMonth(int mon, int yr);

// checks if appointment time is available
int checkAppointmentAvailability(struct Appointment *appointments, int yr, int mon, int day, int hr, int min, int maxAppointments);

// Updates appointment file when user adds appointment in system
// Source of code: https://intro2c.sdds.ca/E-Secondary-Storage/text-files
void writeToAppointmentFile(const char *datafile, int max, int patNum, int yr, int mon, int day, int hr, int min);

// remove appointment in file using index of line
// function inspired by Stack Overflow user, "user3115056": https://stackoverflow.com/questions/20716785/how-do-i-delete-a-specific-line-from-text-file-in-c
void removeAppointmentFromFile(const char *datafile, int max, int patNum, int yr, int mon, int day);

// checks if phone number is 10 digits long
void verifyPhoneNumber(struct Phone *phone);

#endif // !CLINIC_H