#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

char* logfile1;
char* logfile2;
int writeInterval1;
int writeInterval2;

pthread_t thread_id1;
pthread_t thread_id2;

void* thread1(void* arg)
{ 
    time_t current_time;
    struct tm * time_info;
    char timeString[22];  // space for "dd-mm-YYYY HH:MM:SS\0"
    for(;;)
    {
        FILE *f = fopen(logfile1, "a");

        if (f != NULL)
        {
            printf("save time to logfile 1\r\n");
            time(&current_time);
            time_info = localtime(&current_time);

            strftime(timeString, sizeof(timeString), "%d/%m/%Y %H:%M:%S\n\r", time_info);
            fputs(timeString, f);
            fflush(f);
            
        }
        else
        {
            printf("couldn't open/make file\n\r");
        }
        fclose(f);
        sleep(writeInterval1);
    }
    return NULL; 
}
void* thread2(void* arg)
{ 
    time_t current_time;
    struct tm * time_info;
    char timeString[22];  // space for "dd-mm-YYYY HH:MM:SS\0"
    for(;;)
    {
        FILE *f = fopen(logfile2, "a");

        if (f != NULL)
        {
            printf("save time to logfile 2\r\n");
            time(&current_time);
            time_info = localtime(&current_time);

            strftime(timeString, sizeof(timeString), "%d/%m/%Y %H:%M:%S\n\r", time_info);
            fputs(timeString, f);
            fflush(f);
            
        }
        else
        {
            printf("couldn't open/make file\n\r");
        }
        fclose(f);
        sleep(writeInterval2);
    }
    return NULL; 
}

int main(int argc, char *argv[])
{
    if (argc == 5)
    {
        logfile1 = argv[1];
        sscanf(argv[2], "%i", &writeInterval1);
        logfile2 = argv[3];
        sscanf(argv[4], "%i", &writeInterval2);

        if (pthread_create(&thread_id1, NULL, &thread1, NULL) != 0) 
            printf("\nThread 1 can't be created."); 
        if (pthread_create(&thread_id2, NULL, &thread2, NULL) != 0) 
            printf("\nThread 2 can't be created."); 
  
        pthread_join(thread_id1, NULL); 
        pthread_join(thread_id2, NULL); 
    }
    else
    {
        printf("error: command does not contain the correct arguments\r\n");
    }

    return 0;
}