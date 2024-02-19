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
#include <string.h> // string library
#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

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

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// ONE: get integer
int inputInt()
{
    int integerInput;
    char c;

    do
    {
        scanf("%d%c", &integerInput, &c);
        if (c == '\n')
        {
            return integerInput;
        }
        else
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    } while (c != '\n');
    return integerInput;
}

// TWO: get POSITIVE integer
int inputIntPositive()
{
    int positiveInput;

    do
    {
        scanf("%d", &positiveInput);
        if (positiveInput > 0)
        {
            return positiveInput;
        }
        else
        {
            clearInputBuffer();
            printf("ERROR! Value must be > 0: ");
        }
    } while (positiveInput <= 0);
    return positiveInput;
}

// THREE: get integer BETWEEN a range
int inputIntRange(int lower, int upper)
{
    int numInput;
    char c;
    {
        do
        {
            scanf("%d%c", &numInput, &c);
            if (numInput >= lower && numInput <= upper && c == '\n')
            {
                return numInput;
            }
            else if ((numInput < lower || numInput > upper) && c == '\n')
            {
                printf("ERROR! Value must be between %d and %d inclusive: ", lower, upper);
            }
            else if (c != '\n')
            {
                clearInputBuffer();
                printf("Error! Input a whole number: ");
            }
        } while (!(numInput >= lower && numInput <= upper && c == '\n'));
    }
    return numInput;
}

// FOUR: get a char that's also in given arr
char inputCharOption(const char stringArr[])
{
    int flag = 0;
    char input[3];

    do
    {
        scanf("%s", input);
        clearInputBuffer();

        int i;
        for (i = 0; stringArr[i] != '\0'; i++)
        {
            if (input[i] == stringArr[i] && strlen(input) == 1)
            {
                flag = 1;
            }
        }

        if (flag != 1 || strlen(input) != 1)
        {
            printf("ERROR: Character must be one of [");
            int j;
            for (j = 0; stringArr[j] != '\0'; j++)
            {
                printf("%c", stringArr[j]);
            }
            printf("]: ");
        }

    } while (flag != 1);

    return input[0];
}

// FIVE: validate string of given length
void inputCString(char *cstringValue, int min, int max)
{

    int flag = 0;
    do
    {
        char string[MAX_INPUT_LENGTH];
        scanf("%31[^\n]", string); // get string thats up to 31 chars long, including spaces
        clearInputBuffer();
        int counter = 0;
        int j;
        for (j = 0; string[j] != '\0'; j++)
        {
            counter++; // count length of string input
        }

        if (counter >= min && counter <= max)
        {
            int i;
            for (i = 0; string[i] != '\0'; i++)
            {
                *(cstringValue + i) = string[i]; // assign string to pointer
            }
            *(cstringValue + strlen(string)) = '\0';
            counter = 0;
            flag = 1;
        }
        else if (min == max && (counter != min || counter != max))
        {
            printf("ERROR: String length must be exactly %d chars: ", max);
        }

        else if (min != max && counter < min && counter < max)
        {
            printf("ERROR: String length must be between %d and %d chars: ", min, max);
        }
        else if (min != max && counter > min && counter > max)

        {
            printf("ERROR: String length must be no more than %d chars: ", max);
        }

    } while (flag == 0);
}

// SIX: validate phone number
void displayFormattedPhone(const char *phoneNum)
{
    if (phoneNum != NULL)
    {
        int counter = 0;
        int flag = 0;
        int i;
        for (i = 0; *(phoneNum + i) != '\0'; i++)
        {
            counter++;
            if (!(((int)*(phoneNum + i)) - 48 >= 0 && ((int)*(phoneNum + i)) - 48 <= 9))
            {
                flag = 1;
            }
        }

        if (counter != 10 || flag == 1)
        {
            printf("(___)___-____");
        }
        else
        {
            printf("(%c%c%c)%c%c%c-%c%c%c%c", *(phoneNum + 0), *(phoneNum + 1), *(phoneNum + 2), *(phoneNum + 3), *(phoneNum + 4), *(phoneNum + 5), *(phoneNum + 6), *(phoneNum + 7), *(phoneNum + 8), *(phoneNum + 9));
        }
    }
    else
    {
        printf("(___)___-____");
    }
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////