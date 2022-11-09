
// ===================================================================================
//  Assignment: 2 
//  Milestone : 4
// ===================================================================================
//  Student Name  : Arman Valaee Asr
//  Student ID    : 139550206
//  Student Email : avalaee-asr@myseneca.ca
//  Course Section: ZCC
// ===================================================================================


#ifndef TICKET_H_
#define TICKET_H_

#include "accountTicketingUI.h"
#include "commonHelpers.h"
#include "account.h"


struct Message
{
	char type;
	char sname[31];
	char details[151];
};

struct Ticket
{
	int ticketno;
	int ticketaccno;
	int status;
	char subject[31];
	int counter;
	struct Message msg[20];
};

//1 Gets Ticket number
int getTicketNo(struct AccountTicketingData acc[], const struct Account* logged);

//2 Opens apropriate ticket
void openTicket(struct AccountTicketingData acc[], int ticketno);

//3 Prompts customer to add the required information when creating a new ticket
void newTicket(struct AccountTicketingData acc[], const struct Account* logged, int index);

//4 Gets an integer and checks if it is available inside Tickets
int findTicketIndexByTicktNum(int ticktno, const struct AccountTicketingData acc[], int prompt);

//5 Remove an account and its active tickets
int removeAccount(struct AccountTicketingData acc[], const struct Account* loggedacc, int index);

//6 Add a new message in a ticket
void newMessage(struct AccountTicketingData acc[], const struct Account* loggedacc, int ticktIndex);

//7 Close a ticket and returns 1 if the ticket get closed successfuly. Returns 0 if it doesn't close the ticket
int closeTicket(struct AccountTicketingData acc[], const struct Account* loggedacc, int ticktIndex);

//8 This function will show the ticket management menu for the agent and prompts user for the menu options
void manageTicketMenu(struct AccountTicketingData acc[], const struct Account* loggedacc, int ticktIndex);

//9 This function will create a new ticket for customer
void createNewTicket(struct AccountTicketingData acc[], const struct Account* loggedacc);

//10 Gets a ticket number from user, First check its availibility, then checks if the logged in user can modify it or not
int modifyTicketNo(struct AccountTicketingData acc[], const struct Account* loggedacc, int ticktno);

//11 This function will show the Ticket modifying menu for costumer and prompts user for menu options
void modifyTicketMenu(struct AccountTicketingData acc[], const struct Account* loggedacc, int ticktno);

//12 Free up all the tickets and it members of the recent deleted account struct
void freeupTickets(struct AccountTicketingData acc[], int index);

//13 Reads tickets data from tickets.txt file
int loadTickets(struct Ticket* tickt, int MaxSize);

//14 Saves the current state of ticket array to the tickets.txt (Recreates the file)
int updateTickets(struct Ticket* tickt, int MaxSize);

//15 Archives all closed tickets of a recently removed account in tickets_arc.txt
void archivesTickets(struct AccountTicketingData acc[], int index);

//16 Free up all the closed tickets and it members
void freeupClosedTickets(struct AccountTicketingData acc[]);

//17 Archives all closed tickets
int archivesClosedTickets(struct AccountTicketingData acc[]);

//18 Counts the number of archived Tickets in tickets_arc.txt file
int archivedTicketsCounter(int MaxSize, int* msgRecords);

#endif // !TICKET_H_
