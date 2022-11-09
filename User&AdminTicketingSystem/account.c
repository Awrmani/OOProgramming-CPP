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
#include <ctype.h>
#include <string.h>
//----------------------------
#include "account.h"

//1 Function to get user input for a new "Account"
void getAccount(struct Account* acc)
{
	printf("New Account Data (Account#:%d)\n", acc->accountno);
	printf("----------------------------------------\n");
	printf("Enter the account type (A=Agent | C=Customer): ");
	acc->type = getCharOption("AC");
	printf("\n");
}

//2 Function to get user input for a new "UserLogin"
void getUserLogin(struct UserLogin* usr)
{
	int i, error = 1;
	printf("User Login Data Input\n");
	printf("----------------------------------------\n");
	while (error)
	{
		error = 0;
		printf("Enter user login (10 chars max): ");
		getCString(usr->lname, 1, 10);
		for (i = 0; i < 11 && !error; i++)
		{
			if (usr->lname[i] == ' ')
				error = 1;
		}
		if (error)
			printf("ERROR:  The user login must NOT contain whitespace characters.\n");
	}
	printf("Enter the display name (30 chars max): ");
	getCString(usr->sname, 1, 30);
	getPass(usr->password);
	printf("\n");
}

//3 Function to get user input for a new "Demographic"
void getDemographic(struct Demographic* dem)
{
	printf("Demographic Data Input\n");
	printf("----------------------------------------\n");
	printf("Enter birth year (current age must be between 18 and 110): ");
	dem->birthyear = getIntFromRange(1911, 2003);
	printf("Enter the household Income: $");
	dem->hhincome = getPositiveDouble();
	printf("Enter the country (30 chars max.): ");
	getCString(dem->country, 1, 30);
	upperCase(dem->country);
	printf("\n");
}

//4 Update the members of Account structure
void updateAccount(struct Account* acc)
{
	int menu = -1;
	while (menu)
	{
		printf("Account: %05d - Update Options\n", acc->accountno);
		printf("----------------------------------------\n");
		printf("1) Update account type (current value: %c)\n", acc->type);
		printf("2) Login\n");
		printf("3) Demographics\n");
		printf("0) Done\n");
		printf("Selection: ");
		menu = getIntFromRange(0, 3);	//Promt for menu option
		if (menu == 1)
		{
			printf("\nEnter the account type (A=Agent | C=Customer): ");
			acc->type = getCharOption("AC");
		}
		else if (menu == 2)
		{
			printf("\n");
			updateUserLogin(&acc->userlg);
			printf("\n");
		}
		else if (menu == 3)
		{
			printf("\n");
			updateDemographic(&acc->demo);
			printf("\n");
		}
		else
		{
			printf("\n");
		}
	}
}

//5 Update the members of UserLogin structure
void updateUserLogin(struct UserLogin* user)
{
	int menu = -1;
	while (menu)
	{
		printf("User Login: %s - Update Options\n", user->lname);
		printf("----------------------------------------\n");
		printf("1) Display name (current value: %s)\n", user->sname);
		printf("2) Password\n");
		printf("0) Done\n");
		printf("Selection: ");
		menu = getIntFromRange(0, 2);	//Promt for menu option
		if (menu == 1)
		{
			printf("\nEnter the display name (30 chars max): ");
			getCString(user->sname, 1, 30);
			printf("\n");
		}
		else if (menu == 2)
		{
			printf("\n");
			getPass(user->password);
			printf("\n");
		}
	}
}

//6 Update the members of Demographic structure
void updateDemographic(struct Demographic* demo)
{
	int menu = -1;
	while (menu)
	{
		printf("Demographic Update Options\n");
		printf("----------------------------------------\n");
		printf("1) Household Income (current value: $%.2lf)\n", demo->hhincome);
		printf("2) Country (current value: %s)\n", demo->country);
		printf("0) Done\n");
		printf("Selection: ");
		menu = getIntFromRange(0, 2);	//Promt for menu option
		if (menu == 1)
		{
			printf("\nEnter the household Income: $");
			demo->hhincome = getPositiveDouble();
			printf("\n");
		}
		else if (menu == 2)
		{
			printf("\nEnter the country (30 chars max.): ");
			getCString(demo->country, 1, 30);
			upperCase(demo->country);
			printf("\n");
		}
	}
}

//7 Uppercase the characters of a string 
void upperCase(char str[])
{
	int i;
	for (i = 0; i < 31; i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
	}
	return;
}

//8 Gets password
void getPass(char str[])
{
	int i, upper = 0, lower = 0, digit = 0, symbol = 0, password = 1;
	while (password)
	{
		printf("Enter the password (must be 8 chars in length): ");
		getCString(str, 8, 8);
		for (i = 0; i < 9; i++)
		{
			if (isupper(str[i]))
				upper++;
			else if (islower(str[i]))
				lower++;
			else if (isdigit(str[i]))
				digit++;
			else if (ispunct(str[i]) && str[i] != ')' && str[i] != '(')
				symbol++;
		}
		if (upper > 1 && lower > 1 && digit > 1 && symbol > 1)
			password = 0;
		else
		{
			printf("SECURITY: Password must contain 2 of each:\n");
			printf("          Digit: 0-9\n");
			printf("          UPPERCASE character\n");
			printf("          lowercase character\n");
			printf("          symbol character: !@#$%%^&*\n");
			upper = 0;
			lower = 0;
			digit = 0;
			symbol = 0;
		}
	}
}

//9 Free up all the members of the recent deleted account struct
void freeupAccount(struct AccountTicketingData acc[], int index)
{
	acc->accounts[index].accountno = 0;
	acc->accounts[index].demo.birthyear = 0;
	acc->accounts[index].demo.hhincome = 0;
	acc->accounts[index].type = ' ';
	strcpy(acc->accounts[index].userlg.lname, "");
	strcpy(acc->accounts[index].userlg.password, "");
	strcpy(acc->accounts[index].userlg.sname, "");
	strcpy(acc->accounts[index].demo.country, "");
}

//10 Reads accounts data from accounts.txt file
int loadAccounts(struct Account acc[], int MaxSize)
{
	FILE* fp = NULL;
	int i = 0;

	fp = fopen("accounts.txt", "r");

	if (fp != NULL)
	{
		//50008~A~Will Smith~agentJ~TT*&21tt~1952~2350600.82~U.S.A.
		while (i < MaxSize &&
			fscanf(fp, "%d~%c~%30[^~]~%10[^~]~%8[^~]~%d~%lf~%30[^\n]", &acc[i].accountno, &acc[i].type, acc[i].userlg.sname,
				acc[i].userlg.lname, acc[i].userlg.password, &acc[i].demo.birthyear, &acc[i].demo.hhincome, acc[i].demo.country) == 8)
			i++;
		fclose(fp);
	}
	else
		printf("Failed to open accounts.txt file\n");

	return i;  //Number of the loaded records.
}

//11 Saves the current state of Accounts struct array to the accounts.txt (Recreates the file)
int updateAccounts(struct Account acc[], int MaxSize)
{
	FILE* fp = NULL;
	int i = 0, records = 0;

	fp = fopen("accounts.txt", "w");

	if (fp != NULL)
	{
		//50008~A~Will Smith~agentJ~TT*&21tt~1952~2350600.82~U.S.A.
		while (i < MaxSize)
		{
			if (acc[i].accountno != 0)
			{
				fprintf(fp, "%d~%c~%s~%s~%s~%d~%lf~%s\n", acc[i].accountno, acc[i].type, acc[i].userlg.sname,
					acc[i].userlg.lname, acc[i].userlg.password, acc[i].demo.birthyear, acc[i].demo.hhincome, acc[i].demo.country);
				records++;
			}
			i++;
		}
		fclose(fp);
	}
	else
		printf("Failed to open accounts.txt file\n");

	return records;  //Number of the saved records.
}

//12 Archives record of the recently closed account in accounts_arc.txt
void archivesAccount(struct AccountTicketingData acc[], int index)
{
	FILE* fp = NULL;

	fp = fopen("accounts_arc.txt", "a");

	if (fp != NULL)
	{
		//50008~A~Will Smith~agentJ~TT*&21tt~1952~2350600.82~U.S.A.
		fprintf(fp, "%d~%c~%s~%s~%s~%d~%lf~%s\n", acc->accounts[index].accountno, acc->accounts[index].type, acc->accounts[index].userlg.sname,
			acc->accounts[index].userlg.lname, acc->accounts[index].userlg.password, acc->accounts[index].demo.birthyear, acc->accounts[index].demo.hhincome, acc->accounts[index].demo.country);
		fclose(fp);
		freeupAccount(acc, index);
	}
	else
		printf("Failed to open accounts_arc.txt file\n");
}

//13 Counts the number of archived accounts in accounts_arc.txt file
int archivedAccountsCounter(int MaxSize)
{
	FILE* fp = NULL;
	int i = 0;
	int tmp1, tmp6;
	double tmp7;
	char tmp2, tmp3[31], tmp4[11], tmp5[9], tmp8[31];

	fp = fopen("accounts_arc.txt", "r");

	if (fp != NULL)
	{
		//50008~A~Will Smith~agentJ~TT*&21tt~1952~2350600.82~U.S.A.
		while (i < MaxSize &&
			fscanf(fp, "%d~%c~%30[^~]~%10[^~]~%8[^~]~%d~%lf~%30[^\n]", &tmp1, &tmp2, tmp3, tmp4, tmp5, &tmp6, &tmp7, tmp8) == 8)
			i++;
		fclose(fp);
	}
	else
		printf("Failed to open accounts_arc.txt file\n");

	return i;  //Number of archived accounts counted.
}

//14 Takes login information from user before loging in. Cancel after 3 attempts
int logingIn(const struct AccountTicketingData* acc)
{
	int i, accno, flag = 0, index = -2, attempts = 3;
	while (attempts && flag != 3)
	{
		flag = 0;
		printf("\nEnter the account#: ");
		accno = getInteger();
		for (i = 0; i < acc->ACCOUNT_MAX_SIZE && !flag; i++)
		{
			if (acc->accounts[i].accountno == accno)
			{
				flag++;
				index = i;
			}
			else
				index = -2;
		}
		char login[100];
		printf("User Login    : ");
		getCString(login, 1, 100);
		if (strcmp(acc->accounts[index].userlg.lname, login) == 0)
			flag++;
		char pass[100];
		printf("Password      : ");
		getCString(pass, 1, 100);
		if (strcmp(acc->accounts[index].userlg.password, pass) == 0)
			flag++;
		if (flag != 3)
		{
			index = -2;
			attempts--;
			printf("INVALID user login/password combination! [attempts remaining:%d]\n", attempts);
		}
	}
	if (!attempts)
	{
		index = -2;
		printf("\nERROR:  Login failed!\n\n");
		pauseExecution();
	}
	return index;
}