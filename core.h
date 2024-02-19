/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  :
Student ID#:
Email      :
Section    :

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

// SAFE-GUARD:
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

#define MAX_INPUT_LENGTH 31 // max length of string input
// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);

// ONE: get integer from keyboard
int inputInt();

// TWO: get POSITIVE integer
int inputIntPositive();

// THREE: get integer BETWEEN a range
int inputIntRange(int lower, int upper);

// FOUR: get char that's also in given arr
char inputCharOption(const char stringArr[]);

// FIVE: get string between given range
void inputCString(char *cstringValue, int min, int max);

// SIX: validate phone number
void displayFormattedPhone(const char *phoneNum);

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H
