/*

Lab: 3
Spring 2023
Name: Vladimir Ceban

*/

// Includes
#include <stdio.h>
#include <string.h>

// Defines
#define SIZE 10

int main(void);
void empty_stdin(void);

void insert(void);
void show_all(void);
void show_by_hours(int);
int check_duplicate(char[SIZE]);
void delete(char[SIZE]);

// Global variables
int flightCount = 0;
char codes[SIZE][SIZE];
int hours[SIZE];
int minutes[SIZE];

// Functions
void insert(void)
{
	int hour, minute, flagCode, flagHour, flagMinute;
	char code[SIZE];
	flagCode = flagHour = flagMinute = 0;

	printf("Please, enter the code of the flight:\n");
	if (scanf("%s", code) != 1)
	{
		empty_stdin();
		printf("Error: you can enter only one string of characters at a time. Please try again.\n");
		return;
	}
	else if (strlen(code) <= 0 || strlen(code) >= SIZE)
	{
		empty_stdin();
		printf("Error: code can be from 1 to 9 characters. Please try again.\n");
		return;
	}
	else if (check_duplicate(code) != 0)
	{
		empty_stdin();
		printf("Error: codes can't duplicate. Please try again.\n");
		return;
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
		printf("Error: hour should be a single integer. Please try again.\n");
		return;
	}
	else if (hour < 0 || hour > 23)
	{
		empty_stdin();
		printf("Error: hour can be an integer from 0 to 23. Please try again.\n");
		return;
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
		printf("Error: minute should be a single integer. Please try again.\n");
		return;
	}
	else if (minute < 0 || minute > 59)
	{
		empty_stdin();
		printf("Error: minute can be an integer from 0 to 59. Please try again.\n");
		return;
	}
	else
	{
		empty_stdin();
		flagMinute = 1;
	}

	if (flagCode == 1 && flagHour == 1 && flagMinute == 1)
	{
		int i, position;
		int time = (hour * 60) + minute;
		// if there are not flights scheduled yet - schedule to 1st position
		if (flightCount == 0)
		{
			position = 0;
		}
		else
		{
			for (i = 0; i < SIZE; i++)
			{
				if (time < hours[i] * 60 + minutes[i])
				{
					// position is set to first element that is smaller
					position = i;
					break;
				}
				else
				{
					// position is set to the first empty element
					if (strlen(codes[i]) == 0)
					{
						position = i;
						break;
					}
				}
			}
			// sort arrays with respect to position
			for (i = SIZE - 1; i > position; i--)
			{
				// copy elements from x-1 to x, where x starts at the end of the array
				strcpy(codes[i], codes[i - 1]);
				hours[i] = hours[i - 1];
				minutes[i] = minutes[i - 1];
			}
		}
		// place data into arrays
		strcpy(codes[position], code);
		hours[position] = hour;
		minutes[position] = minute;
		flightCount++;
		printf("Sucess: your flight was scheduled.\n");
	}
	return;
}
void show_all(void)
{
	int i;
	if (flightCount > 0)
	{
		for (i = 0; i != flightCount; i++)
		{
			if (strlen(codes[i]) > 0)
			{
				printf("%d. Code: %s Time: %d:%02d\n", i + 1, codes[i], hours[i], minutes[i]);
			}
		}

		printf("Returning to main menu...\n");
		return;
	}
	else
	{
		printf("Error: the schedule is empty. Please schedule a flight first.\n");
		return;
	}
}
void show_by_hours(int hour)
{
	int i;
	int flag = 0;

	for (i = 0; i != flightCount; i++)
	{
		if (hours[i] == hour)
		{
			printf("%d. Code: %s Time: %d:%02d\n", i + 1, codes[i], hours[i], minutes[i]);
			flag++;
		}
	}

	if (flag < 1)
	{
		printf("Error: no flights are scheduled for this hour. Please try again.\n");
	}

	printf("Returning to main menu...\n");
	return;
}
void empty_stdin(void) // helper function to avoid repeating error messages on wrong inputs
{
	int c = getchar();

	while (c != '\n' && c != EOF)
	{
		c = getchar();
	}
}
int check_duplicate(char code[SIZE])
{
	int i;
	int flag = 0;
	for (i = 0; i < SIZE; i++)
	{
		if (strcmp(codes[i], code) == 0)
		{
			flag++;
		}
	}

	return flag;
}
void delete(char code[SIZE])
{
	int cancelRequest, i;

	for (i = 0; i < SIZE; i++)
	{
		if (strcmp(codes[i], code) == 0)
		{
			cancelRequest = i;
			break;
		}
		else
		{
			cancelRequest = -1;
		}
	}
	if (cancelRequest >= 0)
	{
		for (i = cancelRequest; i < SIZE; i++)
		{
			strcpy(codes[i], codes[i + 1]);
			hours[i] = hours[i + 1];
			minutes[i] = minutes[i + 1];
		}
		flightCount--;
		printf("Success. Flight %s was canceled.\n", code);
		return;
	}
	else
	{
		printf("Error: there is no such flight scheduled yet. Please try again.\n");
		return;
	}
}

// Main
int main(void)
{
	int option;

	printf("Welcome to the Flighty Flighters Inc flight scheduling system. Please choose one of these options:\n\n1. Add a flight to the schedule\n2. Show all scheduled flights\n3. Show all flights scheduled for a specific hour\n4. Delete a flight with code\n\n0. Quit\n");

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
			}
			else
			{
				printf("Error: the schedule is full. Please try again tomorrow.\n");
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
				empty_stdin();
				printf("Error: the schedule is empty. Please schedule a flight first.\n");
			}
			else
			{
				printf("Please enter the hour you would like to search for:\n");
				if (scanf("%d", &hour) != 1)
				{
					empty_stdin();
					printf("Error: hour should be a single integer. Please try again.\n");
				}
				else if (hour < 0 || hour > 23)
				{
					printf("Error: hour can be an integer from 0 to 23. Please try again\n");
				}
				else
				{
					empty_stdin();
					show_by_hours(hour);
				}
			}
			break;

		case 4:
			empty_stdin();
			char code[SIZE];
			printf("Please enter an alpha-numeric flight code (1 to 9 characters) you'd like to delete:\n");
			if (flightCount < 1)
			{
				empty_stdin();
				printf("The schedule is empty. Please schedule a flight first.\n");
			}
			else
			{
				if (scanf("%s", code) != 1)
				{
					empty_stdin();
					printf("Error: you can enter only one code at a time. Please try again.\n");
				}
				else if (strlen(code) <= 0 || strlen(code) >= SIZE)
				{
					printf("Error: Code can be from 1 to 9 characters. Please try again.\n");
				}
				else
				{
					empty_stdin();
					delete (code);
				}
			}
			break;

		case 0:
			empty_stdin();
			printf("Goodbye!\n");
			return 0;

		default:
			empty_stdin();
			printf("Error: invalid menu option.\n");
		}
	}
}
