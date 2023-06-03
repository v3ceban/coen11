// Infludes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

// defines
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

// Extern globals
extern Flight *head;
extern pthread_mutex_t mutex;

// Functions declaration
// main
int main(int, char *[SIZE]);
void empty_stdin(void);
// list.c
void insert(Flight *);
void show_all(void);
void show_by_hours(int);
int check_duplicate(char[SIZE]);
void deletebycode(char[SIZE]);
void delete_all_flights(Flight *);
// file.c
int save_to_file(char *);
int read_file(char *);
void *autoSave(void *);
void read_binFile(char *);