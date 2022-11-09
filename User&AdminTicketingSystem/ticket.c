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
#include "ticket.h"

//1 Gets Ticket number
int getTicketNo(struct AccountTicketingData acc[], const struct Account* logged)
{
	int tick = 1, i;
	int stop = 1, tickIndex = -1;
	printf("Enter the ticket number to view the messages or\n");
	printf("0 to return to previous menu: ");
	do
	{
		tick = getInteger();
		if (tick < 0)
			printf("ERROR: Value must be positive or zero: ");

	} while (tick < 0);
	for (i = 0; i <= acc->TICKET_MAX_SIZE && stop; i++)
	{
		if (acc->tickets[i].ticketno == tick)
		{
			tickIndex = i;
			stop = 0;
		}
	}
	if (!tick)
	{
		tickIndex = -2;
		printf("\n");
	}
	else if (!stop && acc->tickets[tickIndex].ticketaccno != logged->accountno && logged->type == 'C')
	{
		tickIndex = -1;
		printf("\nERROR: Invalid ticket number - you may only access your own tickets.\n\n");
		pauseExecution();
	}
	else if (tickIndex == -1)
	{
		printf("\nERROR: Invalid ticket number.\n\n");
		pauseExecution();
	}

	return tickIndex;
}

//2 Opens apropriate ticket
void openTicket(struct AccountTicketingData acc[], int tickIndex)
{
	int i;
	printf("\n================================================================================\n");
	printf("%06d (%s) Re: %s\n", acc->tickets[tickIndex].ticketno, acc->tickets[tickIndex].status == 1 ? "ACTIVE" : "CLOSED", acc->tickets[tickIndex].subject);
	printf("================================================================================\n");
	int pause = 1;
	for (i = 0; i < acc->tickets[tickIndex].counter; i++)
	{
		pause = 1;
		printf("%s (%s):\n", acc->tickets[tickIndex].msg[i].type == 'C' ? "CUSTOMER" : "AGENT", acc->tickets[tickIndex].msg[i].sname);
		printf("   %s\n\n", acc->tickets[tickIndex].msg[i].details);
		if ((i + 1) % 5 == 0 && i != acc->tickets[tickIndex].counter)
		{
			pause = 0;
			pauseExecution();
		}
	}
	if (pause)
		pauseExecution();
}

//3 Prompts customer to add the required information when creating a new ticket
void newTicket(struct AccountTicketingData acc[], const struct Account* logged, int index)
{
	printf("New Ticket (Ticket#:%06d)\n", acc->tickets[index].ticketno);
	printf("----------------------------------------\n");
	printf("Enter the ticket SUBJECT (30 chars. maximum): ");
	getCString(acc->tickets[index].subject, 1, 30);
	printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
	getCString(acc->tickets[index].msg[0].details, 1, 150);
	printf("\n*** New ticket created! ***\n\n");
	acc->tickets[index].status = 1;
	acc->tickets[index].ticketaccno = logged->accountno;
	acc->tickets[index].counter = 1;
	strcpy(acc->tickets[index].msg[0].sname, logged->userlg.sname);
	acc->tickets[index].msg[0].type = logged->type;
}


//4 Gets an integer and checks if it is available inside Tickets, If available, gives its index number.
int findTicketIndexByTicktNum(int ticktno, const struct AccountTicketingData acc[], int prompt)
{
	int i;
	int flag = 0;
	int indexno = -1;
	if (prompt)
	{
		printf("\nEnter the account#: ");
		ticktno = getPositiveInteger();
	}
	for (i = 0; i < acc->TICKET_MAX_SIZE && !flag; i++)
	{
		if (acc->tickets[i].ticketno == ticktno)
		{
			flag = 1;
		}
	}
	indexno = (flag) ? i - 1 : -1;
	return indexno;
}

//5 Remove an account and its active tickets
int removeAccount(struct AccountTicketingData acc[], const struct Account* loggedacc, int index)
{
	char userInput = ' ';
	int result = 0;

	if (index > -1 && acc->accounts[index].accountno == loggedacc->accountno)
	{
		printf("\nERROR: You can't remove your own account!\n\n");
		pauseExecution();
	}
	else if (index > -1)
	{
		displayAccountDetailHeader();
		displayAccountDetailRecord(&acc->accounts[index]);
		printf("\nAre you sure you want to remove this record? ([Y]es|[N]o): ");
		userInput = getCharOption("YN");
		if (userInput == 'Y')
		{
			result = 1;
			printf("\n*** Account Removed! ***\n\n");
			pauseExecution();
		}
		else
		{
			printf("\n*** No changes made! ***\n\n");
			pauseExecution();
		}
	}
	else
	{
		printf("\nERROR: Access Denied.\n\n");
		pauseExecution();
	}

	return result;
}

//6 Add a new message in a ticket
void newMessage(struct AccountTicketingData acc[], const struct Account* loggedacc, int ticktIndex)
{
	if (acc->tickets[ticktIndex].counter == 20)
		printf("\nERROR: Message limit has been reached, call ITS Support!\n");
	else if (acc->tickets[ticktIndex].status == 0)
		printf("\nERROR: Ticket is closed - new messages are not permitted.\n");
	else
	{
		int count = acc->tickets[ticktIndex].counter;
		printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
		getCString(acc->tickets[ticktIndex].msg[count].details, 1, 150);
		strcpy(acc->tickets[ticktIndex].msg[count].sname, loggedacc->userlg.sname);
		acc->tickets[ticktIndex].msg[count].type = loggedacc->type;
		acc->tickets[ticktIndex].counter++;
	}
}

//7 Close a ticket and returns 1 if the ticket get closed successfuly. Returns 0 if it doesn't close the ticket
int closeTicket(struct AccountTicketingData acc[], const struct Account* loggedacc, int ticktIndex)
{
	int result = 0;
	if (acc->tickets[ticktIndex].status == 1)
	{
		printf("\nAre you sure you CLOSE this ticket? ([Y]es|[N]o): ");
		char input = getCharOption("YN");
		if (input == 'Y')
		{
			acc->tickets[ticktIndex].status = 0;
			if (acc->tickets[ticktIndex].counter < 20)
			{
				printf("\nDo you want to leave a closing message? ([Y]es|[N]o): ");
				char input1 = getCharOption("YN");
				if (input1 == 'Y')
				{
					int count = acc->tickets[ticktIndex].counter;
					printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
					getCString(acc->tickets[ticktIndex].msg[count].details, 1, 150);
					strcpy(acc->tickets[ticktIndex].msg[count].sname, loggedacc->userlg.sname);
					acc->tickets[ticktIndex].msg[count].type = loggedacc->type;
					acc->tickets[ticktIndex].counter++;
				}
			}
			printf("\n*** Ticket closed! ***\n");
			result = 1;
		}
	}
	else
		printf("\nERROR: Ticket is already closed!\n");
	return result;
}

//8 This function will show the ticket management menu for the agent and prompts user for the menu options
void manageTicketMenu(struct AccountTicketingData acc[], const struct Account* loggedacc, int ticktIndex)
{
	int menu1 = -1;
	while (menu1)
	{
		printf("\n----------------------------------------\n");
		printf("Ticket %06d - Update Options\n", acc->tickets[ticktIndex].ticketno);
		printf("----------------------------------------\n");
		printf("Status  : %s\n", acc->tickets[ticktIndex].status == 1 ? "ACTIVE" : "CLOSED");
		printf("Subject : %s\n", acc->tickets[ticktIndex].subject);
		printf("Acct#   : %d\n", acc->tickets[ticktIndex].ticketaccno);
		printf("Customer: %s\n", acc->tickets[ticktIndex].msg[0].sname);
		printf("----------------------------------------\n");
		printf("1) Add a message\n");
		printf("2) Close ticket\n");
		printf("3) Re-open ticket\n");
		printf("0) Done\n");
		printf("Selection: ");
		menu1 = getIntFromRange(0, 3);
		if (menu1 == 1)
		{
			newMessage(acc, loggedacc, ticktIndex);
		}
		else if (menu1 == 2)
		{
			closeTicket(acc, loggedacc, ticktIndex);
		}
		else if (menu1 == 3)
		{
			if (acc->tickets[ticktIndex].status == 0)
			{
				printf("\nAre you sure you RE-OPEN this closed ticket? ([Y]es|[N]o): ");
				char input = getCharOption("YN");
				if (input == 'Y')
				{
					acc->tickets[ticktIndex].status = 1;
					printf("\n*** Ticket re-opened! ***\n");
				}
			}
			else
				printf("\nERROR: Ticket is already active!\n");
		}
		else
			printf("\n");
	}
}

//9 This function will create a new ticket for customer
void createNewTicket(struct AccountTicketingData acc[], const struct Account* loggedacc)
{
	int index1 = findTicketIndexByTicktNum(0, acc, 0);

	if (index1 < 0)
	{
		printf("\nERROR: Ticket listing is FULL, call ITS Support!\n\n");
		pauseExecution();
	}
	else
	{
		printf("\n");
		int i, max = 0;
		for (i = 0; i < acc->TICKET_MAX_SIZE; i++)
		{
			if (acc->tickets[i].ticketno > max)
				max = acc->tickets[i].ticketno;
		}
		acc->tickets[index1].ticketno = max + 1;
		newTicket(acc, loggedacc, index1);
		pauseExecution();
	}
}

//10 Gets a ticket number from user, First check its availibility, then checks if the logged in user can modify it or not
int modifyTicketNo(struct AccountTicketingData acc[], const struct Account* loggedacc, int ticktno)
{
	int error = 0, i;
	for (i = 0; i < acc->TICKET_MAX_SIZE && !error; i++)
	{
		if (ticktno == acc->tickets[i].ticketno)
		{
			if (acc->tickets[i].ticketaccno == loggedacc->accountno)
			{
				if (acc->tickets[i].status == 1)
					error = 1;
				else
				{
					error = 3;
					printf("\nERROR: Ticket is closed - changes are not permitted.\n\n");
					pauseExecution();
				}
			}
			else
			{
				error = 2;
				printf("\nERROR: Invalid ticket number - you may only modify your own ticket.\n\n");
				pauseExecution();
			}
		}
	}
	if (error == 0)
	{
		error = 4;
		printf("\nERROR: Invalid ticket number.\n\n");
		pauseExecution();
	}
	return error;
}

//11 This function will show the Ticket modifying menu for costumer and prompts user for menu options
void modifyTicketMenu(struct AccountTicketingData acc[], const struct Account* loggedacc, int ticktno)
{
	int menu1 = -1;
	while (menu1)
	{
		int ticktIndex = findTicketIndexByTicktNum(ticktno, acc, 0);
		printf("\n----------------------------------------\n");
		printf("Ticket %06d - Update Options\n", ticktno);
		printf("----------------------------------------\n");
		printf("Status  : %s\n", acc->tickets[ticktIndex].status == 1 ? "ACTIVE" : "CLOSED");
		printf("Subject : %s\n", acc->tickets[ticktIndex].subject);
		printf("----------------------------------------\n");
		printf("1) Modify the subject\n");
		printf("2) Add a message\n");
		printf("3) Close ticket\n");
		printf("0) Done\n");
		printf("Selection: ");
		menu1 = getIntFromRange(0, 3);
		if (menu1 == 1)
		{
			printf("\nEnter the revised ticket SUBJECT (30 chars. maximum): ");
			getCString(acc->tickets[ticktIndex].subject, 1, 30);
		}
		else if (menu1 == 2)
		{
			newMessage(acc, loggedacc, ticktIndex);
		}
		else if (menu1 == 3)
		{
			int result = closeTicket(acc, loggedacc, ticktIndex);
			if (result)
			{
				printf("\n");
				pauseExecution();
				menu1 = 0;
			}
		}
		else
		{
			printf("\n");
			pauseExecution();
		}
	}
}

//12 Free up all the tickets and it members of the recent deleted account struct
void freeupTickets(struct AccountTicketingData acc[], int index)
{
	int i;
	for (i = 0; i < acc->TICKET_MAX_SIZE; i++)
	{
		if (acc->accounts[index].accountno == acc->tickets[i].ticketaccno)
		{

			acc->tickets[i].counter = 0;
			acc->tickets[i].ticketno = 0;
			acc->tickets[i].ticketaccno = 0;
			acc->tickets[i].status = 0;
			strcpy(acc->tickets[i].subject, "");
			int j;
			for (j = 0; j < 20; j++)
			{
				strcpy(acc->tickets[i].msg[j].details, "");
				strcpy(acc->tickets[i].msg[j].sname, "");
				acc->tickets[i].msg[j].type = ' ';
			}
		}
	}
}

//13 Reads tickets data from tickets.txt file
int loadTickets(struct Ticket* tickt, int MaxSize)
{
	FILE* fp = NULL;
	int i = 0, j;

	fp = fopen("tickets.txt", "r");

	if (fp != NULL)
	{
		//80599|20020|1|No power/does not turn on|1|C|Shrimpy Shrimp|The unit won't turn on - please help.|
		//60001|30004|1|Frequent Disconnects|5|C|Betty Boop|Every time I go near the microwave the unit disconnects.|A|Will Smith|Don't go near the microwave.
		//|A|Will Smith|It will radiate waves which will interrupt the unit.|C|Betty Boop|But I use the microwave a lot.|A|Will Smith|You cook too much!|
		while (i < MaxSize &&
			fscanf(fp, "%d|%d|%d|%30[^|]|%d|", &tickt[i].ticketno, &tickt[i].ticketaccno, &tickt[i].status, tickt[i].subject, &tickt[i].counter) == 5)
		{
			for (j = 0; j < tickt[i].counter; j++)
				fscanf(fp, "%c|%30[^|]|%150[^|]|", &tickt[i].msg[j].type, tickt[i].msg[j].sname, tickt[i].msg[j].details);
			i++;
		}
		fclose(fp);
	}
	else
		printf("Failed to open tickets.txt file\n");

	return i;  //Number of the loaded records.
}

//14 Saves the current state of ticket array to the tickets.txt (Recreates the file)
int updateTickets(struct Ticket* tickt, int MaxSize)
{
	FILE* fp = NULL;
	int i = 0, j;
	int records = 0;

	fp = fopen("tickets.txt", "w");

	if (fp != NULL)
	{
		//80599|20020|1|No power/does not turn on|1|C|Shrimpy Shrimp|The unit won't turn on - please help.|
		while (i < MaxSize)
		{
			if (tickt[i].ticketno != 0)
			{
				fprintf(fp, "%d|%d|%d|%s|%d|", tickt[i].ticketno, tickt[i].ticketaccno, tickt[i].status, tickt[i].subject, tickt[i].counter);
				for (j = 0; j < tickt[i].counter; j++)
				{
					fprintf(fp, "%c|%s|%s|", tickt[i].msg[j].type, tickt[i].msg[j].sname, tickt[i].msg[j].details);
					if (j == tickt[i].counter - 1)
						fprintf(fp, "\n");
				}
				records++;
			}
			i++;
		}
		fclose(fp);
	}
	else
		printf("Failed to open tickets.txt file\n");

	return records; //Number of the saved records.
}

//15 Archives all closed tickets of a recently removed account in tickets_arc.txt
void archivesTickets(struct AccountTicketingData acc[], int index)
{
	FILE* fp = NULL;
	int i = 0, j;
	int records = 0;

	fp = fopen("tickets_arc.txt", "a");

	if (fp != NULL)
	{
		//80599|20020|1|No power/does not turn on|1|C|Shrimpy Shrimp|The unit won't turn on - please help.|
		while (i < acc->TICKET_MAX_SIZE)
		{
			if (acc->tickets[i].status == 0 && acc->tickets[i].ticketaccno == acc->accounts[index].accountno && acc->tickets[i].ticketno != 0)
			{
				fprintf(fp, "%d|%d|%d|%s|%d|", acc->tickets[i].ticketno, acc->tickets[i].ticketaccno, acc->tickets[i].status, acc->tickets[i].subject, acc->tickets[i].counter);
				for (j = 0; j < acc->tickets[i].counter; j++)
				{
					fprintf(fp, "%c|%s|%s|", acc->tickets[i].msg[j].type, acc->tickets[i].msg[j].sname, acc->tickets[i].msg[j].details);
					if (j == acc->tickets[i].counter - 1)
						fprintf(fp, "\n");
				}
				records++;
			}
			i++;
		}
		fclose(fp);
		freeupTickets(acc, index);
	}
	else
		printf("Failed to open tickets_arc.txt file\n");
}

//16 Free up all the closed tickets and it members
void freeupClosedTickets(struct AccountTicketingData acc[])
{
	int i;
	for (i = 0; i < acc->TICKET_MAX_SIZE; i++)
	{
		if (acc->tickets[i].status == 0 && acc->tickets[i].ticketno != 0)
		{

			acc->tickets[i].counter = 0;
			acc->tickets[i].ticketno = 0;
			acc->tickets[i].ticketaccno = 0;
			acc->tickets[i].status = 0;
			strcpy(acc->tickets[i].subject, "");
			int j;
			for (j = 0; j < 20; j++)
			{
				strcpy(acc->tickets[i].msg[j].details, "");
				strcpy(acc->tickets[i].msg[j].sname, "");
				acc->tickets[i].msg[j].type = ' ';
			}
		}
	}
}

//17 Archives all closed tickets
int archivesClosedTickets(struct AccountTicketingData acc[])
{
	FILE* fp = NULL;
	int i = 0, j;
	int records = 0;

	fp = fopen("tickets_arc.txt", "a");

	if (fp != NULL)
	{
		//80599|20020|1|No power/does not turn on|1|C|Shrimpy Shrimp|The unit won't turn on - please help.|
		while (i < acc->TICKET_MAX_SIZE)
		{
			if (acc->tickets[i].status == 0 && acc->tickets[i].ticketno != 0)
			{
				fprintf(fp, "%d|%d|%d|%s|%d|", acc->tickets[i].ticketno, acc->tickets[i].ticketaccno, acc->tickets[i].status, acc->tickets[i].subject, acc->tickets[i].counter);
				for (j = 0; j < acc->tickets[i].counter; j++)
				{
					fprintf(fp, "%c|%s|%s|", acc->tickets[i].msg[j].type, acc->tickets[i].msg[j].sname, acc->tickets[i].msg[j].details);
					if (j == acc->tickets[i].counter - 1)
						fprintf(fp, "\n");
				}
				records++;
			}
			i++;
		}
		fclose(fp);
		freeupClosedTickets(acc);
	}
	else
		printf("Failed to open tickets_arc.txt file\n");

	return records; //Number of the archived records.
}

//18 Counts the number of archived Tickets in tickets_arc.txt file
int archivedTicketsCounter(int MaxSize, int* msgRecords)
{
	FILE* fp = NULL;
	int i = 0, j = 0;
	int tmp1, tmp2, tmp3, tmp5;
	char tmp4[31], tmp6, tmp7[31], tmp8[151];
	int counter = 0;

	fp = fopen("tickets_arc.txt", "r");

	if (fp != NULL)
	{
		//80599|20020|1|No power/does not turn on|1|C|Shrimpy Shrimp|The unit won't turn on - please help.|
		//60001|30004|1|Frequent Disconnects|5|C|Betty Boop|Every time I go near the microwave the unit disconnects.|A|Will Smith|Don't go near the microwave.
		//|A|Will Smith|It will radiate waves which will interrupt the unit.|C|Betty Boop|But I use the microwave a lot.|A|Will Smith|You cook too much!|
		while (i < MaxSize && fscanf(fp, "%d|%d|%d|%30[^|]|%d|", &tmp1, &tmp2, &tmp3, tmp4, &tmp5) == 5)
		{
			j = 0;
			i++;
			while (j < 20 && fscanf(fp, "%c|%30[^|]|%150[^|]|", &tmp6, tmp7, tmp8) == 3)
			{
				j++;
				counter++;		//Number of archived messages counted.
			}
		}
		*msgRecords = counter;
		fclose(fp);
	}
	else
		printf("Failed to open tickets_arc.txt file\n");

	return i;  //Number of archived tickets counted.
}