/*

Lab: 2
Spring 2023
Name: Vladimir Ceban

*/

// Includes
#include <stdio.h>

// Defines
#define SIZE 10

int main(void);
void empty_stdin(void);
int insert(void);
int show_all(void);
int show_by_hours(int);
void printMenu(void);

// Global variables
int flightCount = 0;
int codes[SIZE];
int hours[SIZE];
int minutes[SIZE];

// Functions
int insert(void)
{
	int code, hour, minute, flagCode, flagHour, flagMinute;
	flagCode = flagHour = flagMinute = 0;

	printf("Please, enter the code of the flight:\n");
	if (scanf("%d", &code) != 1)
	{
		empty_stdin();
		printf("Error. Please, only enter digits from 0 to 9. Returning to main menu...\n");
		return 1;
	}
	else if (code < 0)
	{
		empty_stdin();
		printf("Error. Please, only enter digits from 0 to 9. Returning to main menu...\n");
		return 1;
	}
	else
	{
		empty_stdin();
		flagCode = 1;
	}

	printf("Please, enter the hour of the flight's departure:\n");
	if (scanf("%d", &hour) != 1)
	{
		empty_stdin();
		printf("Error. Please, only enter digits from 0 to 9. Returning to main menu...\n");
		return 1;
	}
	else if (hour < 0 || hour > 23)
	{
		empty_stdin();
		printf("Error. Hour can be a number from 0 to 23. Returning to main menu...\n");
		return 1;
	}
	else
	{
		empty_stdin();
		flagHour = 1;
	}

	printf("Please, enter the minute of the flight's departure:\n");
	if (scanf("%d", &minute) != 1)
	{
		empty_stdin();
		printf("Error. Please, only enter digits from 0 to 9. Returning to main menu...\n");
		return 1;
	}
	else if (minute < 0 || minute > 59)
	{
		empty_stdin();
		printf("Error. Minute can be a number from 0 to 59. Returning to main menu...\n");
		return 1;
	}
	else
	{
		empty_stdin();
		flagMinute = 1;
	}

	if (flagCode == 1 && flagHour == 1 && flagMinute == 1)
	{
		codes[flightCount] = code;
		hours[flightCount] = hour;
		minutes[flightCount] = minute;
		flightCount++;
		printf("Thank you! Your flight was scheduled. Returning to main menu...\n");
	}
	return 0;
}
int show_all(void)
{
	int i;
	if (flightCount > 0)
	{
		for (i = 0; i != flightCount; i++)
		{
			if (codes[i] > 0)
			{
				printf("%d. Code: %d Time: %d:%02d\n", i + 1, codes[i], hours[i], minutes[i]);
			}
		}

		printf("Returning to main menu...\n");
		return 0;
	}
	else
	{
		printf("The schedule is empty. Please schedule a flight first. Returning to the main menu...\n");
		return 1;
	}
}
int show_by_hours(int hour)
{
	int i;
	int flag = 0;

	if (hour < 0 || hour > 23)
	{
		printf("Error. Hour can be a number from 0 to 23. Returning to main menu...\n");
		return 1;
	}
	else
	{
		for (i = 0; i != flightCount; i++)
		{
			if (hours[i] == hour)
			{
				printf("%d. Code: %d Time: %d:%02d\n", i + 1, codes[i], hours[i], minutes[i]);
				flag++;
			}
		}

		if (flag < 1)
		{
			printf("Sorry, there are not flights scheduled for this hour. Returning to the main menu...\n");
		}

		printf("Returning to main menu...\n");
		return 0;
	}
}
void empty_stdin(void) // helper function to avoid repeating error messages on wrong inputs
{
	int c = getchar();

	while (c != '\n' && c != EOF)
	{
		c = getchar();
	}
}
void printMenu(void)
{
	printf("\nPlease choose one of these options:\n\n1. Add a flight to the schedule\n2. Show all scheduled flights\n3. Show all flights scheduled for a specific hour\n\n0. Quit\n");
}

// Main
int main(void)
{
	int option;

	printf("Welcome to the Flighty Flighters Inc flight scheduling system.\n");
	printMenu();

	while (1)
	{
		if (scanf("%d", &option) != 1)
		{
			printf("Error: invalid menu option. Aborting...\n");
			return 1;
		}

		switch (option)
		{
		case 1:
			empty_stdin();
			if (flightCount < SIZE)
			{
				insert();
				printMenu();
			}
			else
			{
				printf("Sorry, the schedule is full.\n");
			}
			break;

		case 2:
			empty_stdin();
			show_all();
			break;

		case 3:
			empty_stdin();
			int hour;
			if (flightCount < 1)
			{
				printf("The schedule is empty. Please schedule a flight first. Returning to the main menu...\n");
			}
			else
			{
				printf("Please enter the hour you would like to search for:\n");
				if (scanf("%d", &hour) != 1)
				{
					empty_stdin();
					printf("Error. Hour can be a number from 0 to 23. Returning to main menu...\n");
					printMenu();
				}
				else
				{
					empty_stdin();
					show_by_hours(hour);
				}
			}
			break;

		case 0:
			empty_stdin();
			printf("Exiting... Goodbye!\n");
			return 0;

		default:
			empty_stdin();
			printf("Error: invalid menu option. Returning to main menu...\n");
			printMenu();
		}
	}
}
