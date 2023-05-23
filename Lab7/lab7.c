/*

Lab: 7
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

int main(void);

void empty_stdin(void);

void insert(void);
void show_all(void);
void show_by_hours(int);
int check_duplicate(char[SIZE]);
void deletebycode(char[SIZE]);
int save_to_file(void);
void delete_all_flights(void);

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

void insert(void)
{
	int hour, minute;
	char code[SIZE + 1];
	Flight *new, *this, *prev;
	if ((new = (Flight *)malloc(sizeof(Flight))) == (Flight *)NULL)
	{
		printf("Error: memory could not be allocated\n");
		return;
	}

	printf("Please, enter the code of the flight:\n");
	if (scanf("%s", code) != 1)
	{
		empty_stdin();
		printf("Error: you can enter only one string of characters at a time. Please try again.\n");
		return;
	}
	else if (strlen(code) <= 0 || strlen(code) > SIZE)
	{
		empty_stdin();
		printf("Error: code can be from 1 to 10 characters. Please try again.\n");
		return;
	}
	else if (check_duplicate(code) != 0)
	{
		empty_stdin();
		printf("Error: codes can't duplicate. Please try again.\n");
		return;
	}

	printf("Please, enter the hour of the flight's departure:\n");
	empty_stdin();
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

	printf("Please, enter the minute of the flight's departure:\n");
	empty_stdin();
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
	strcpy(new->code, code);
	new->hour = hour;
	new->minute = minute;

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

	printf("Sucess: your flight was scheduled.\n");
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
int save_to_file(void)
{
	FILE *file;
	Flight *this = head;
	int i = 1;
	if ((file = fopen("data.txt", "w")) == NULL)
	{
		printf("Error: couldn't open the file. Please check the file permissions. Aborting...\n");
		return 1;
	}
	while (this != NULL)
	{
		fprintf(file, "%d. Code: %s Time: %d:%02d\n", i, this->code, this->hour, this->minute);
		i++;
		this = this->next;
	}
	fclose(file);
	printf("All flights were saved to 'data.txt' file. ");
	return 0;
}
void delete_all_flights(void)
{
	Flight *this;
	this = head;
	while (this != NULL)
	{
		head = this->next;
		free(this);
		this = head;
	}
	return;
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
			insert();
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
			if (save_to_file() != 0)
			{
				return 1;
			}
			else
			{
				delete_all_flights();
				printf("Goodbye!\n");
				return 0;
			}

		default:
			empty_stdin();
			printf("Error: invalid menu option.\n");
		}
	}
}
