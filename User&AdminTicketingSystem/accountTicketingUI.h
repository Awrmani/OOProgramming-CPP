
// ===================================================================================
//  Assignment: 2 
//  Milestone : 4
// ===================================================================================
//  Student Name  : Arman Valaee Asr
//  Student ID    : 139550206
//  Student Email : avalaee-asr@myseneca.ca
//  Course Section: ZCC
// ===================================================================================


#ifndef ACCOUNT_TICKETING_UI_H_
#define ACCOUNT_TICKETING_UI_H_

#include <stdio.h>
#include <ctype.h>
#include <string.h>
//


struct AccountTicketingData
{
	struct Account* accounts;	// array of accounts
	const int ACCOUNT_MAX_SIZE; // maximum elements for account array

	struct Ticket* tickets;	    // array of tickets
	const int TICKET_MAX_SIZE;  // maximum elements for ticket array
};
#include "commonHelpers.h"
#include "ticket.h"
#include "account.h"

//1 Displays Account Summary Header
void displayAccountSummaryHeader();

//2 Displays Account Details Header
void displayAccountDetailHeader();

//3 Display Account Summary of an account array
void displayAccountSummaryRecord(const struct Account* acc);

//4 Display Account details of an account array
void displayAccountDetailRecord(const struct Account* acc);

//5 Our main prgram to run the menus as much as needed
void applicationStartup(struct AccountTicketingData* acc);

//6 Shows Login Menu and prommpts for option
int menuLogin(const struct AccountTicketingData* acc);

//7 Shows Agent Menu and prommpts for option
void menuAgent(struct AccountTicketingData* acc, const struct Account* loggedacc);

//8 Shows Customer Menu and prompt for option
void menuCustomer(struct AccountTicketingData* acc, const struct Account* loggedacc);

//9 Gets an integer and checks if it is available inside Account struct
int findAccountIndexByAcctNum(int accno, const struct AccountTicketingData* acc, int prompt);

//10 Displays account summary header and records of all members of account array
void displayAllAccountSummaryRecords(const struct AccountTicketingData* acc);

//11 Displays account details header and details of all members of account array
void displayAllAccountDetailRecords(const struct AccountTicketingData* acc);

//12 Pause execution until user enters the enter key
void pauseExecution(void);

//13 Displays Customer's tickets list header
void displayCustomerTicketHeader();

//14 Displays Customer's tickets list
void displayCustomerTicketList(struct AccountTicketingData* acc, const struct Account* loggedacc);

//15 Displays Agent's tickets list header
void displayAgentTicketHeader();

//16 Displays Agent's new tickets list
void displayAgentNewTicketList(struct AccountTicketingData* acc);

//17 Displays Agent's active tickets list
void displayAgentActiveTicketList(struct AccountTicketingData* acc);

//18 Displays Agent's closed tickets list
void displayAgentClosedTicketList(struct AccountTicketingData* acc);

//19 Displays Agent's Menu
void displayAgentMenu(const struct Account* loggedacc);

//20 Displays Customer's Menu
void displayCustomerMenu(const struct Account* loggedacc);

//21 Add a new account
void addNewAccount(struct AccountTicketingData* acc);

#endif // !ACCOUNT_TICKETING_UI_H_
