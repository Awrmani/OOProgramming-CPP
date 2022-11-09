
// ===================================================================================
//  Assignment: 2 
//  Milestone : 4
// ===================================================================================
//  Student Name  : Arman Valaee Asr
//  Student ID    : 139550206
//  Student Email : avalaee-asr@myseneca.ca
//  Course Section: ZCC
// ===================================================================================

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
//----------------------------
#include "accountTicketingUI.h"
#include "commonHelpers.h"
#include "account.h"
#include "ticket.h"

// Uses the time.h library to obtain current year information
// Get the current 4-digit year from the system
int currentYear(void)
{
	time_t currentTime = time(NULL);
	return localtime(&currentTime)->tm_year + 1900;
}

// Empty the standard input buffer
void clearStandardInputBuffer(void)
{
	while (getchar() != '\n')
	{
		; // On purpose: do nothing 
	}
}

//1 Gets an Integar value
int getInteger(void)
{
	int value;
	char newLine = 'x';

	while (newLine != '\n')
	{
		scanf("%d%c", &value, &newLine);
		if (newLine != '\n')
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be an integer: ");
		}
	}
	return value;
}

//2 Gets a positive Integer value
int getPositiveInteger(void)
{
	int value;
	char newLine = 'x';

	while (newLine != '\n')
	{
		scanf("%d%c", &value, &newLine);
		if (newLine != '\n')
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be an integer: ");
		}
		else if (value <= 0)
		{
			newLine = 'x';
			printf("ERROR: Value must be a positive integer greater than zero: ");
		}
	}
	return value;
}

//3 Gets a double value
double getDouble(void)
{
	double value;
	char newLine = 'x';

	while (newLine != '\n')
	{
		scanf("%lf%c", &value, &newLine);
		if (newLine != '\n')
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be a double floating-point number: ");
		}
	}
	return value;
}

//4 Gets a positive double value
double getPositiveDouble(void)
{
	double value;
	char newLine = 'x';

	while (newLine != '\n')
	{
		scanf("%lf%c", &value, &newLine);
		if (newLine != '\n')
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be a double floating-point number: ");
		}
		else if (value <= 0)
		{
			newLine = 'x';
			printf("ERROR: Value must be a positive double floating-point number: ");
		}
	}
	return value;
}

//5 Get an Integer and check if it is in a range
int  getIntFromRange(int lowerbound, int upperbound)
{
	int value;
	char newLine = 'x';
	while (newLine != '\n')
	{
		scanf("%d%c", &value, &newLine);
		if (newLine != '\n')
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be an integer: ");
		}
		else if (value > upperbound || value < lowerbound)
		{
			newLine = 'x';
			printf("ERROR: Value must be between %d and %d inclusive: ", lowerbound, upperbound);
		}
	}
	return value;
}

//6 Gets a char, and checks if the character is inside the considered string
char getCharOption(const char validchar[])
{
	char input = NULL;
	char newLine = 'x';
	int flag = 0;
	while (!flag)
	{
		scanf("%c%c", &input, &newLine);
		if (newLine == '\n')
		{
			if (strchr(validchar, input) == NULL)
				printf("ERROR: Character must be one of [%s]: ", validchar);
			else
				flag = 1;
		}
		else
		{
			clearStandardInputBuffer();
			printf("ERROR: Character must be one of [%s]: ", validchar);
		}
	}
	return input;
}

//7 Gets a string between min and max length
void getCString(char Cstring[], int min, int max)
{
	int len = 0, flag = 1;
	char str[170];
	while (flag)
	{
		scanf("%[^\n]c", str);
		if (strchr(str, '\0'))
			len = strlen(str);
		if (min == max && len != min)
		{
			clearStandardInputBuffer();
			printf("ERROR: String length must be exactly %d chars: ", min);
		}
		else if (len > max)
		{
			clearStandardInputBuffer();
			printf("ERROR: String length must be no more than %d chars: ", max);
		}
		else if (len < min)
		{
			clearStandardInputBuffer();
			printf("ERROR: String length must be between %d and %d chars: ", min, max);
		}
		else
			flag = 0;
	}
	if (!flag)
		strcpy(Cstring, str);
	clearStandardInputBuffer();
	return;
}
