/*

Lab: 9
Spring 2023
Name: Vladimir Ceban

*/

// Includes
#include "list.h"

// Global variables
Flight *head = NULL;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Functions
void empty_stdin(void) // helper function to avoid repeating error messages on wrong inputs
{
	int c = getchar();

	while (c != '\n' && c != EOF)
	{
		c = getchar();
	}
}

// Main
int main(int argc, char **argv)
{
	int option;
	pthread_t autoSaveThread;
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&autoSaveThread, NULL, autoSave, argv[2]);

	if (argc < 2)
	{
		printf("Error: the file name is missing. Please try calling the program again. Aborting...\n");
		return 1;
	}
	read_file(argv[1]);

	printf("Welcome to the Flighty Flighters Inc flight scheduling system. Please choose one of these options:\n\n1. Add a flight to the schedule\n2. Show all scheduled flights\n3. Show all flights scheduled for a specific hour\n4. Delete a flight with code\n5. Show contents of auto-saved file\n\n0. Quit\n");

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
			pthread_mutex_lock(&mutex);
			Flight *new;
			int newHour, newMinute;
			char newCode[SIZE + 1];
			if ((new = (Flight *)malloc(sizeof(Flight))) == (Flight *)NULL)
			{
				printf("Error: memory could not be allocated. Aborting...\n");
				return 1;
			}
			printf("Please, enter the code of the flight:\n");
			if (scanf("%s", newCode) != 1)
			{
				empty_stdin();
				printf("Error: you can enter only one string of characters at a time. Please try again.\n");
				break;
			}
			else if (strlen(newCode) <= 0 || strlen(newCode) > SIZE)
			{
				empty_stdin();
				printf("Error: code can be from 1 to 10 characters. Please try again.\n");
				break;
			}
			else if (check_duplicate(newCode) != 0)
			{
				empty_stdin();
				printf("Error: codes can't duplicate. Please try again.\n");
				break;
			}
			printf("Please, enter the hour of the flight's departure:\n");
			empty_stdin();
			if (scanf("%d", &newHour) != 1)
			{
				empty_stdin();
				printf("Error: hour should be a single integer. Please try again.\n");
				break;
			}
			else if (newHour < 0 || newHour > 23)
			{
				empty_stdin();
				printf("Error: hour can be an integer from 0 to 23. Please try again.\n");
				break;
			}
			printf("Please, enter the minute of the flight's departure:\n");
			empty_stdin();
			if (scanf("%d", &newMinute) != 1)
			{
				empty_stdin();
				printf("Error: minute should be a single integer. Please try again.\n");
				break;
			}
			else if (newMinute < 0 || newMinute > 59)
			{
				empty_stdin();
				printf("Error: minute can be an integer from 0 to 59. Please try again.\n");
				break;
			}
			strcpy(new->code, newCode);
			new->hour = newHour;
			new->minute = newMinute;
			printf("Sucess: your flight was scheduled.\n");
			insert(new);
			pthread_mutex_unlock(&mutex);
			break;

		case 2:
			empty_stdin();
			show_all();
			break;

		case 3:
			empty_stdin();
			int hour;
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
			break;

		case 4:
			empty_stdin();
			pthread_mutex_lock(&mutex);
			char code[SIZE];
			printf("Please enter an alpha-numeric flight code (1 to 9 characters) you'd like to delete:\n");
			if (scanf("%s", code) != 1)
			{
				empty_stdin();
				printf("Error: you can enter only one code at a time. Please try again.\n");
			}
			else if (strlen(code) <= 0 || strlen(code) >= SIZE)
			{
				empty_stdin();
				printf("Error: Code can be from 1 to 9 characters. Please try again.\n");
			}
			else
			{
				empty_stdin();
				deletebycode(code);
			}
			pthread_mutex_unlock(&mutex);
			break;

		case 5:
		case 6:
			empty_stdin();
			read_binFile(argv[2]);
			break;

		case 0:
			empty_stdin();
			if (save_to_file(argv[1]) != 0)
			{
				return 1;
			}
			else
			{
				pthread_mutex_lock(&mutex);
				delete_all_flights(head);
				printf("Goodbye!\n");
				pthread_mutex_unlock(&mutex);
				return 0;
			}

		default:
			empty_stdin();
			printf("Error: invalid menu option.\n");
		}
	}
}
