#include "list.h"

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
        pthread_mutex_lock(&mutex);
        insert(new);
        pthread_mutex_unlock(&mutex);
    }
    return 0;
}
void *autoSave(void *arg)
{
    char *fileName = (char *)arg;
    FILE *file;
    Flight *this;
    while (1)
    {
        sleep(15);
        // printf("%d. Locked\n", pthread_mutex_lock(&mutex));
        pthread_mutex_lock(&mutex);
        this = head;
        if ((file = fopen(fileName, "wb")) == NULL)
        {
            printf("Error: couldn't open temp file. Please check the file permissions. Aborting...\n");
            return NULL;
        }
        while (this != NULL)
        {
            fwrite(this, sizeof(Flight), 1, file);
            this = this->next;
        }
        printf("Saved...\n");
        fclose(file);
        // printf("%d. Unlocked\n", pthread_mutex_unlock(&mutex));
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void read_binFile(char *fileName)
{
    pthread_mutex_lock(&mutex);
    FILE *file;
    Flight *p = malloc(sizeof(Flight));
    if ((file = fopen(fileName, "rb")) == NULL)
    {
        printf("Error: couldn't open temp file. Please check the file permissions. Aborting...\n");
        free(p);
        return;
    }
    while (fread(p, sizeof(Flight), 1, file))
    {
        printf("Code: %s Time: %d:%02d\n", p->code, p->hour, p->minute);
    }
    fclose(file);
    free(p);
    pthread_mutex_unlock(&mutex);
    return;
}