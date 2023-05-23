/*

Lab: 8
Spring 2023
Name: Vladimir Ceban

*/

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defines
#define SIZE 10
#define Flight struct flight

// define structure of Flight that has code, hour, and minute
struct flight
{
	char code[SIZE + 1];
	int hour;
	int minute;
	Flight *next;
};

int main(int, char *[SIZE]);

void empty_stdin(void);

void insert(Flight *);
void show_all(void);
void show_by_hours(int);
int check_duplicate(char[SIZE]);
void deletebycode(char[SIZE]);
int save_to_file(char *);
void delete_all_flights(Flight *);
int read_file(char *);

// Global variables
Flight *head = NULL;

// Functions
void empty_stdin(void) // helper function to avoid repeating error messages on wrong inputs
{
	int c = getchar();

	while (c != '\n' && c != EOF)
	{
		c = getchar();
	}
}

void insert(Flight *new)
{
	Flight *this, *prev;

	this = prev = head;
	while (this != NULL)
	{
		if (((new->hour * 60) + new->minute) < ((this->hour * 60) + this->minute))
		{
			break;
		}
		prev = this;
		this = this->next;
	}
	if (this == head) // either inserting in the first element or in the empty list
	{
		new->next = head;
		head = new;
	}
	else
	{
		new->next = this;
		prev->next = new;
	}
	return;
}
void show_all(void)
{
	Flight *p;
	p = head;
	int i = 1;

	if (p == NULL)
	{
		printf("Error: the schedule is empty. Please schedule a flight first.\n");
	}
	else
	{
		while (p != NULL)
		{
			printf("%d. Code: %s Time: %d:%02d\n", i, p->code, p->hour, p->minute);
			i++;
			p = p->next;
		}
	}
	printf("Returning to the main menu...\n");
	return;
}
void show_by_hours(int hour)
{
	Flight *p;
	p = head;
	int i = 1;

	if (p == NULL)
	{
		printf("Error: the schedule is empty. Please schedule a flight first.\n");
	}
	else
	{
		while (p != NULL)
		{
			if (p->hour == hour)
			{
				printf("%d. Code: %s Time: %d:%02d\n", i, p->code, p->hour, p->minute);
			}
			i++;
			p = p->next;
		}
	}
	printf("Returning to the main menu...\n");
	return;
}
int check_duplicate(char code[SIZE])
{
	int flag = 0;
	Flight *p;
	p = head;
	while (p != NULL)
	{
		if (strcmp(p->code, code) == 0)
		{
			flag++;
		}
		p = p->next;
	}
	return flag;
}
void deletebycode(char code[SIZE])
{
	Flight *this, *prev, *thisDel, *prevDel;
	this = prev = head;
	thisDel = prevDel = NULL;
	if (this == NULL)
	{
		printf("Error: the schedule is empty. Please schedule a flight first.\n");
		return;
	}
	while (this != NULL)
	{
		if (strcmp(this->code, code) == 0)
		{
			thisDel = this;
			prevDel = prev;
			printf("Flight #%s at %d:%02d is deleted\n", thisDel->code, thisDel->hour, thisDel->minute);
			break;
		}
		prev = this;
		this = this->next;
	}

	if (thisDel == head)
	{
		head = head->next;
		free(thisDel);
	}
	else
	{
		prevDel->next = thisDel->next;
		free(thisDel);
	}
	printf("Returning to the main menu...\n");
	return;
}
int save_to_file(char *fileName)
{
	FILE *file;
	Flight *this = head;
	if ((file = fopen(fileName, "w")) == NULL)
	{
		printf("Error: couldn't open the file. Please check the file permissions. Aborting...\n");
		return 1;
	}
	while (this != NULL)
	{
		fprintf(file, "Code: %s Time: %d:%02d\n", this->code, this->hour, this->minute);
		this = this->next;
	}
	fclose(file);
	printf("All flights were saved to '%s'. ", fileName);
	return 0;
}
void delete_all_flights(Flight *this)
{
	if (this == NULL)
	{
		head = NULL;
		return;
	}
	delete_all_flights(this->next);
	free(this);
}
int read_file(char *fileName)
{
	FILE *file;
	if ((file = fopen(fileName, "r")) == NULL)
	{
		printf("File '%s' doesn't exist and will be created automatically.\n\n", fileName);
		return 1;
	}
	char code[SIZE];
	int hour;
	int minute;
	while (fscanf(file, "Code: %s Time: %d:%02d\n", code, &hour, &minute) == 3)
	{
		Flight *new;
		if ((new = (Flight *)malloc(sizeof(Flight))) == (Flight *)NULL)
		{
			printf("Error: memory could not be allocated\n");
			return 2;
		}
		strcpy(new->code, code);
		new->hour = hour;
		new->minute = minute;
		insert(new);
	}
}

// Main
int main(int argc, char **argv)
{
	int option;

	if (argc < 2)
	{
		printf("Error: the file name is missing. Please try calling the program again. Aborting...\n");
		return 1;
	}
	read_file(argv[1]);

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
			break;

		case 0:
			empty_stdin();
			if (save_to_file(argv[1]) != 0)
			{
				return 1;
			}
			else
			{
				delete_all_flights(head);
				printf("Goodbye!\n");
				return 0;
			}

		default:
			empty_stdin();
			printf("Error: invalid menu option.\n");
		}
	}
}
