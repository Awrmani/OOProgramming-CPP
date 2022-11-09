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
#include <string.h>
#include <stdio.h>
//----------------------------
#include "accountTicketingUI.h"

//1 Displays Account Summary Header
void displayAccountSummaryHeader()
{
	printf("Acct# Acct.Type Birth\n");
	printf("----- --------- -----\n");
}

//2 Displays Account Details Header
void displayAccountDetailHeader()
{
	printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
	printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
}

//3 Display Account Summary of an account array
void displayAccountSummaryRecord(const struct Account* acc)
{
	printf("%05d %-9s %5d\n", acc->accountno, acc->type == 'C' ? "CUSTOMER" : "AGENT", acc->demo.birthyear);
}

//4 Display Account details of an account array
void displayAccountDetailRecord(const struct Account* acc)
{
	int i = 0;
	char psswd[9] = { 0 };
	for (i = 0; i < 8; i++)
	{
		psswd[i] = (i % 2) ? '*' : acc->userlg.password[i];
	}
	printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s %8s\n", acc->accountno, acc->type == 'C' ? "CUSTOMER" : "AGENT",
		acc->demo.birthyear, acc->demo.hhincome, acc->demo.country, acc->userlg.sname, acc->userlg.lname, psswd);
}

//5 Our main prgram to run the menus as much as needed
void applicationStartup(struct AccountTicketingData* acc)
{
	int indexno;
	char resume;
	do
	{
		indexno = menuLogin(acc);
		if (indexno != -1 && indexno != -2)
		{
			if (acc->accounts[indexno].type == 'C')
				menuCustomer(acc, &acc->accounts[indexno]);
			else
				menuAgent(acc, &acc->accounts[indexno]);
		}
		else if (indexno != -2)
		{
			printf("Are you sure you want to exit? ([Y]es|[N]o): ");
			resume = getCharOption("yYnN");
			if (resume == 'n' || resume == 'N')	//Don't exit
			{
				indexno = -3;
				printf("\n");
			}
		}
	} while (indexno != -1);
	printf("\n");
	printf("==============================================\n");
	printf("Account Ticketing System - Terminated\n");
	printf("==============================================\n\n");
}

//6 Shows Login Menu and prommpts for option
int menuLogin(const struct AccountTicketingData* acc)
{
	printf("==============================================\n");
	printf("Account Ticketing System - Login\n");
	printf("==============================================\n");
	printf("1) Login to the system\n");
	printf("0) Exit application\n");
	printf("----------------------------------------------\n\n");
	printf("Selection: ");
	int menu, index = -2;
	menu = getIntFromRange(0, 1);
	if (menu)
		index = logingIn(acc);
	else
		index = -1;

	if (index != -2)
		printf("\n");

	return index;
}

//7 Shows Agent Menu and prommpts for option
void menuAgent(struct AccountTicketingData* acc, const struct Account* loggedacc)
{
	int menu = -1;
	while (menu)
	{
		displayAgentMenu(loggedacc);
		menu = getIntFromRange(0, 12);
		if (menu == 1)
		{
			addNewAccount(acc);
		}
		else if (menu == 2)
		{
			int index2 = findAccountIndexByAcctNum(0, acc, 1);
			if (index2 > -1)
			{
				printf("\n");
				updateAccount(&acc->accounts[index2]);
			}
			else
			{
				printf("\nERROR: Access Denied.\n\n");
				pauseExecution();
			}
		}
		else if (menu == 3)
		{
			int index3 = findAccountIndexByAcctNum(0, acc, 1);
			if (removeAccount(acc, loggedacc, index3) == 1)
			{
				archivesTickets(acc, index3);
				archivesAccount(acc, index3);
			}
		}
		else if (menu == 4)
		{
			printf("\n");
			displayAllAccountSummaryRecords(acc);
		}
		else if (menu == 5)
		{
			printf("\n");
			displayAllAccountDetailRecords(acc);
		}
		else if (menu == 6)
		{
			printf("\n");
			int ticket = 1;
			while (ticket != -2)
			{
				displayAgentTicketHeader();
				displayAgentNewTicketList(acc);
				ticket = getTicketNo(acc, loggedacc);
				if (ticket != -1 && ticket != -2)
					openTicket(acc, ticket);
			}
		}
		else if (menu == 7)
		{
			printf("\n");
			int ticket = 1;
			while (ticket != -2)
			{
				displayAgentTicketHeader();
				displayAgentActiveTicketList(acc);
				ticket = getTicketNo(acc, loggedacc);
				if (ticket != -1 && ticket != -2)
					openTicket(acc, ticket);
			}
		}
		else if (menu == 8)
		{
			printf("\n");
			int ticket = 1;
			while (ticket != -2)
			{
				displayAgentTicketHeader();
				displayAgentClosedTicketList(acc);
				ticket = getTicketNo(acc, loggedacc);
				if (ticket != -1 && ticket != -2)
					openTicket(acc, ticket);
			}
		}
		else if (menu == 9)
		{
			int i, error = 0, ticktIndex = -1;
			printf("\nEnter ticket number: ");
			int ticktno = getPositiveInteger();
			for (i = 0; i < acc->TICKET_MAX_SIZE && !error; i++)
			{
				if (ticktno == acc->tickets[i].ticketno)
				{
					error = 1;
					ticktIndex = i;
				}
			}
			if (error)
				manageTicketMenu(acc, loggedacc, ticktIndex);
		}
		else if (menu == 10)
		{
			printf("\nAre you sure? This action cannot be reversed. ([Y]es|[N]o): ");
			char ans = getCharOption("YN");
			if (ans == 'Y')
			{
				int record = archivesClosedTickets(acc);
				printf("\n*** %d tickets archived ***\n\n", record);
				pauseExecution();
			}
		}
		else if (menu == 11)
		{
			int accRecords = archivedAccountsCounter(acc->ACCOUNT_MAX_SIZE);
			printf("\nThere are %d account(s) currently archived.\n\n", accRecords);
			pauseExecution();
		}
		else if (menu == 12)
		{
			int msgRecords = 0;
			int ticktRecords = archivedTicketsCounter(acc->TICKET_MAX_SIZE, &msgRecords);
			printf("\nThere are %d ticket(s) and a total of %d message(s) archived.\n\n", ticktRecords, msgRecords);
			pauseExecution();
		}
		else
		{
			int accRecords = updateAccounts(acc->accounts, acc->ACCOUNT_MAX_SIZE);
			int ticktRecords = updateTickets(acc->tickets, acc->TICKET_MAX_SIZE);
			printf("\nSaving session modifications...\n");
			printf("   %d account saved.\n", accRecords);
			printf("   %d tickets saved.\n", ticktRecords);
			printf("### LOGGED OUT ###\n");
			printf("\n");
		}
	}
}

//8 Shows Customer Menu and prompt for option
void menuCustomer(struct AccountTicketingData* acc, const struct Account* loggedacc)
{
	int menu = -1;
	while (menu)
	{
		displayCustomerMenu(loggedacc);
		menu = getIntFromRange(0, 4);
		if (menu == 1)
		{
			printf("\n");
			displayAccountDetailHeader();
			displayAccountDetailRecord(loggedacc);
			printf("\n");
			pauseExecution();
		}
		else if (menu == 2)
		{
			createNewTicket(acc, loggedacc);
		}
		else if (menu == 3)
		{
			printf("\nEnter ticket number: ");
			int ticktno = getPositiveInteger();
			int error = modifyTicketNo(acc, loggedacc, ticktno);
			if (error == 1)
			{
				modifyTicketMenu(acc, loggedacc, ticktno);
			}
		}
		else if (menu == 4)
		{
			printf("\n");
			int ticket = 1;
			while (ticket != -2)
			{
				displayCustomerTicketHeader();
				displayCustomerTicketList(acc, loggedacc);
				ticket = getTicketNo(acc, loggedacc);
				if (ticket != -1 && ticket != -2)
					openTicket(acc, ticket);
			}
		}
		else
		{
			int record = updateTickets(acc->tickets, acc->TICKET_MAX_SIZE);
			printf("\nSaving session modifications...\n");
			printf("   %d tickets saved.\n", record);
			printf("### LOGGED OUT ###\n\n");
		}
	}
	return;
}

//9 Gets an integer and checks if it is available inside Account struct
int findAccountIndexByAcctNum(int accno, const struct AccountTicketingData* acc, int prompt)
{
	int i;
	int flag = 0;
	int indexno = -1;
	if (prompt)
	{
		printf("\nEnter the account#: ");
		accno = getPositiveInteger();
	}
	for (i = 0; i < acc->ACCOUNT_MAX_SIZE && !flag; i++)
	{
		if (acc->accounts[i].accountno == accno)
		{
			flag = 1;
		}
	}
	indexno = (flag) ? i - 1 : -1;
	return indexno;
}

//10 Displays account summary header and records of all members of account array
void displayAllAccountSummaryRecords(const struct AccountTicketingData* acc)
{
	int i, flag = 0;
	for (i = 0; i < acc->ACCOUNT_MAX_SIZE && !flag; i++)
		if (acc->accounts[i].accountno > 0)
		{
			displayAccountSummaryHeader();
			flag = 1;
		}
	for (i = 0; i < acc->ACCOUNT_MAX_SIZE; i++)
		if (acc->accounts[i].accountno > 0)
		{
			displayAccountSummaryRecord(&acc->accounts[i]);
		}
	printf("\n");
	pauseExecution();
}

//11 Displays account details header and details of all members of account array
void displayAllAccountDetailRecords(const struct AccountTicketingData* acc)
{
	int i, flag = 0;
	for (i = 0; i < acc->ACCOUNT_MAX_SIZE && !flag; i++)
		if (acc->accounts[i].accountno > 0)
		{
			displayAccountDetailHeader();
			flag = 1;
		}
	for (i = 0; i < acc->ACCOUNT_MAX_SIZE; i++)
		if (acc->accounts[i].accountno > 0)
		{
			displayAccountDetailRecord(&acc->accounts[i]);
		}
	printf("\n");
	pauseExecution();
}

//12 Pause execution until user enters the enter key void 
void pauseExecution(void)
{
	printf("<< ENTER key to Continue... >>");
	clearStandardInputBuffer();
	putchar('\n');
}

//13 Displays Customer's tickets list header
void displayCustomerTicketHeader()
{
	printf("------ ------ ------------------------------ --------\n");
	printf("Ticket Status Subject                        Messages\n");
	printf("------ ------ ------------------------------ --------\n");
}

//14 Displays Customer's tickets list
void displayCustomerTicketList(struct AccountTicketingData* acc, const struct Account* loggedacc)
{
	int i;
	for (i = 0; i < acc->TICKET_MAX_SIZE; i++)
	{
		if (acc->tickets[i].ticketaccno == loggedacc->accountno)
			printf("%06d %-6s %-30s    %2d\n", acc->tickets[i].ticketno, acc->tickets[i].status == 1 ? "ACTIVE" : "CLOSED",
				acc->tickets[i].subject, acc->tickets[i].counter);
	}
	printf("------ ------ ------------------------------ --------\n\n");
}

//15 Displays Agent's tickets list header
void displayAgentTicketHeader()
{
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
	printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
}

//16 Displays Agent's new tickets list
void displayAgentNewTicketList(struct AccountTicketingData* acc)
{
	int i;
	for (i = 0; i < acc->TICKET_MAX_SIZE; i++)
	{
		if (acc->tickets[i].status == 1 && acc->tickets[i].counter == 1)
		{
			printf("%06d %5d %-15s %-6s %-30s    %2d\n", acc->tickets[i].ticketno, acc->tickets[i].ticketaccno, acc->tickets[i].msg[0].sname,
				acc->tickets[i].status == 1 ? "ACTIVE" : "CLOSED", acc->tickets[i].subject, acc->tickets[i].counter);
		}
	}
	printf("------ ----- --------------- ------ ------------------------------ --------\n\n");
}
//17 Displays Agent's active tickets list
void displayAgentActiveTicketList(struct AccountTicketingData* acc)
{
	int i;
	for (i = 0; i < acc->TICKET_MAX_SIZE; i++)
	{
		if (acc->tickets[i].status == 1)
		{
			printf("%06d %5d %-15s %-6s %-30s    %2d\n", acc->tickets[i].ticketno, acc->tickets[i].ticketaccno, acc->tickets[i].msg[0].sname,
				acc->tickets[i].status == 1 ? "ACTIVE" : "CLOSED", acc->tickets[i].subject, acc->tickets[i].counter);
		}
	}
	printf("------ ----- --------------- ------ ------------------------------ --------\n\n");
}

//18 Displays Agent's closed tickets list
void displayAgentClosedTicketList(struct AccountTicketingData* acc)
{
	int i;
	for (i = 0; i < acc->TICKET_MAX_SIZE; i++)
	{
		if (acc->tickets[i].status == 0 && acc->tickets[i].counter)
		{
			printf("%06d %5d %-15s %-6s %-30s    %2d\n", acc->tickets[i].ticketno, acc->tickets[i].ticketaccno, acc->tickets[i].msg[0].sname,
				acc->tickets[i].status == 1 ? "ACTIVE" : "CLOSED", acc->tickets[i].subject, acc->tickets[i].counter);
		}
	}
	printf("------ ----- --------------- ------ ------------------------------ --------\n\n");
}

//19 Displays Agent's Menu
void displayAgentMenu(const struct Account* loggedacc)
{
	printf("AGENT: %s (%05d)\n", loggedacc->userlg.sname, loggedacc->accountno);
	printf("==============================================\n");
	printf("Account Ticketing System - Agent Menu\n");
	printf("==============================================\n");
	printf(" 1) Add a new account\n");
	printf(" 2) Modify an existing account\n");
	printf(" 3) Remove an account\n");
	printf(" 4) List accounts: summary view\n");
	printf(" 5) List accounts: detailed view\n");
	printf("----------------------------------------------\n");
	printf(" 6) List new tickets\n");
	printf(" 7) List active tickets\n");
	printf(" 8) List closed tickets\n");
	printf(" 9) Manage a ticket\n");
	printf("10) Archive closed tickets\n");
	printf("----------------------------------------------\n");
	printf("11) View archived account statistics\n");
	printf("12) View archived tickets statistics\n");
	printf("----------------------------------------------\n");
	printf("0) Logout\n\n");
	printf("Selection: ");
}

//20 Displays Customer's Menu
void displayCustomerMenu(const struct Account* loggedacc)
{
	printf("CUSTOMER: %s (%05d)\n", loggedacc->userlg.sname, loggedacc->accountno);
	printf("==============================================\n");
	printf("Customer Main Menu\n");
	printf("==============================================\n");
	printf("1) View your account detail\n");
	printf("2) Create a new ticket\n");
	printf("3) Modify an active ticket\n");
	printf("4) List my tickets\n");
	printf("----------------------------------------------\n");
	printf("0) Logout\n\n");
	printf("Selection: ");
}

//21 Add a new account
void addNewAccount(struct AccountTicketingData* acc)
{
	int index1 = findAccountIndexByAcctNum(0, acc, 0);

	if (index1 < 0)
	{
		printf("\nERROR: Account listing is FULL, call ITS Support!\n\n");
		pauseExecution();
	}
	else
	{
		printf("\n");
		int i, max = 0;
		for (i = 0; i < acc->ACCOUNT_MAX_SIZE; i++)
		{
			if (acc->accounts[i].accountno > max)
				max = acc->accounts[i].accountno;
		}
		acc->accounts[index1].accountno = max + 1;
		getAccount(&acc->accounts[index1]);
		getUserLogin(&acc->accounts[index1].userlg);
		getDemographic(&acc->accounts[index1].demo);
		printf("*** New account added! ***\n\n");
		pauseExecution();
	}
}