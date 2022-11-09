/*
Final Project Milestone 5
Module: Utils
Filename: utils.cpp
Author	Arman Valaee Asr
avalaee-asr@myseneca.ca - 139550206
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include "utils.h"
#include "Time.h"
using namespace std;
namespace sdds
{
	bool debug = false;  // made global in utils.h
	int getTime()
	{
		int mins = -1;
		if (debug) {
			Time t(0);
			cout << "Enter current time: ";
			do {
				cin.clear();
				cin >> t;   // needs extraction operator overloaded for Time
				if (!cin) {
					cout << "Invlid time, try agian (HH:MM): ";
					cin.clear();
				}
				else {
					mins = int(t);
				}
				cin.ignore(1000, '\n');
			} while (mins < 0);
		}
		else {
			time_t t = time(NULL);
			tm lt = *localtime(&t);
			mins = lt.tm_hour * 60 + lt.tm_min;
		}
		return mins;
	}

	// This function performs a fool-proof integer entry from the console.
	int getInt(const char* prompt)
	{
		int input;
		bool flag = false;
		if (prompt != nullptr)
			cout << prompt;

		do
		{
			flag = false;
			cin >> input;
			if (cin.fail())
			{
				cout << "Bad integer value, try again: ";
				flag = true;
				cin.clear();
				cin.ignore(1000, '\n');
			}
			else if (char(cin.get()) != '\n')
			{
				cout << "Enter only an integer, try again: ";
				flag = true;
				cin.ignore(1000, '\n');
			}
		} while (flag);

		return input;
	}

	// This function performs a fool-proof integer entry from the console.
	int getInt(int min, int max, const char* prompt,
		const char* errorMessage, bool showRangeAtError)
	{
		int input;
		bool flag = false;

		do
		{
			if (!flag)
				input = getInt(prompt);
			else
				input = getInt();
			flag = false;
			if (input < min || input > max) // If out of the range.
			{
				flag = true;
				if (errorMessage != nullptr)
					cout << errorMessage;
				if (showRangeAtError)
					cout << "[" << min << " <= value <= " << max << "]: ";
			}
		} while (flag);

		return input;
	}

	// Prompts the user for the entry if the prompt argument is not null.
	char* getcstr(const char* prompt, std::istream& istr, char delimiter)
	{
		char* cstr = 0;
		string str;
		if (prompt)
			cout << prompt;

		if (getline(istr, str, delimiter))
		{
			cstr = new char[str.length() + 1];
			strcpy(cstr, str.c_str());
		}
		return cstr;
	}

}