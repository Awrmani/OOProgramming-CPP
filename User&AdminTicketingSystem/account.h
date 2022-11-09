
// ===================================================================================
//  Assignment: 2 
//  Milestone : 4
// ===================================================================================
//  Student Name  : Arman Valaee Asr
//  Student ID    : 139550206
//  Student Email : avalaee-asr@myseneca.ca
//  Course Section: ZCC
// ===================================================================================



#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include "commonHelpers.h"
#include "ticket.h"
#include "accountTicketingUI.h"


struct Demographic
{
	int birthyear;
	double hhincome;
	char country[31];
};

struct UserLogin
{
	char sname[31];
	char lname[11];
	char password[9];
};

struct Account
{
	int accountno;
	char type;
	struct UserLogin userlg;
	struct Demographic demo;
};

//Functions
//1 Function to get user input for a new "Account"
void getAccount(struct Account* acc);

//2 Function to get user input for a new "UserLogin"
void getUserLogin(struct UserLogin* usr);

//3 Function to get user input for a new "Demographic"
void getDemographic(struct Demographic* dem);

//4 Update the members of Account structure
void updateAccount(struct Account* acc);

//5 Update the members of UserLogin structure
void updateUserLogin(struct UserLogin* user);

//6 Update the members of Demographic structure
void updateDemographic(struct Demographic* demo);

//7 Uppercase the characters of a string 
void upperCase(char str[]);

//8 Gets password
void getPass(char str[]);

//9 Free up all the members of the recent deleted account struct
void freeupAccount(struct AccountTicketingData acc[], int index);

//10 Reads accounts data from accounts.txt file
int loadAccounts(struct Account acc[], int MaxSize);

//11 Saves the current state of Accounts struct array to the accounts.txt (Recreates the file)
int updateAccounts(struct Account acc[], int MaxSize);

//12 Archives record of the recently closed account in accounts_arc.txt
void archivesAccount(struct AccountTicketingData acc[], int index);

//13 Counts the number of archived accounts in accounts_arc.txt file
int archivedAccountsCounter(int MaxSize);

//14 Takes login information from user before loging in. Cancel after 3 attempts
int logingIn(const struct AccountTicketingData* acc);

#endif // !ACCOUNT_H_