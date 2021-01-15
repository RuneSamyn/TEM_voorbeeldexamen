#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

char *logfile;
int number_of_threads;

pthread_t *threads = NULL;
pthread_mutex_t lock;

typedef struct
{
    //Or whatever information that you need
    int thread_nr;
    int writeInterval;
} thread_arg_struct;

void *thread_hander(void *args)
{
    thread_arg_struct *thread_struct = args;
    time_t current_time;
    struct tm *time_info;
    char timeString[22]; // space for "dd-mm-YYYY HH:MM:SS\0"
    char threadString[15];
    int thread;
    for (;;)
    {
        pthread_mutex_lock(&lock);  // lock mutex
        FILE *f = fopen(logfile, "a");

        if (f != NULL)
        {
            printf("thread %d saved time to logfile\r\n", thread_struct->thread_nr);
            time(&current_time);
            time_info = localtime(&current_time);

            strftime(timeString, sizeof(timeString), "%d/%m/%Y %H:%M:%S\n\r", time_info);
            snprintf(threadString, 15, "Thread %d, ",thread_struct->thread_nr);
            fputs(threadString, f);
            fputs(timeString, f);
            fflush(f);
        }
        else
        {
            printf("couldn't open/make file\n\r");
        }
        fclose(f);
        pthread_mutex_unlock(&lock);    // unlock mutex => an other process can now take the mutex
        sleep(thread_struct->writeInterval);
    }
    free(thread_struct);
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        int x;
        logfile = argv[1];
        printf("schrijven naar file: %s\r\n", logfile);
        number_of_threads = argc - 2;
        printf("aanmaken van %d threads\r\n", number_of_threads);
        threads = malloc(sizeof(pthread_t)*number_of_threads);

        for (x = 0; x < number_of_threads; x++)
        {   
            int writeInterval;
            thread_arg_struct *args = malloc(sizeof *args);
            if(args == NULL)
                printf("error declare args for thread\n\r");
            if(sscanf(argv[x + 2], "%i", &writeInterval) != 1)
            {
                printf("interval voor thread %d is not an integer\r\n", x+1);
            }
            args->thread_nr = x+1;
            args->writeInterval = writeInterval;
            if(pthread_create(&threads[x], NULL, &thread_hander, args)) {
                free(args);
                printf("Fout bij aanmaken thread %d\r\n", x);
                return 1;
            }
            printf("thread %d aangemaakt met intervall van %d seconden\r\n", x+1, writeInterval);
        }

        if (pthread_mutex_init(&lock, NULL) != 0)
        {
            printf("\n mutex init has failed\n");
            return 1;
        }
        
        for (x = 0; x < number_of_threads; x++)
        {
            pthread_join(threads[x], NULL); 
        }
        pthread_mutex_destroy(&lock);
    }
    else
    {
        printf("error: command does not contain the correct arguments\r\n");
    }

    return 0;
}