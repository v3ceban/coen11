#include "list.h"

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