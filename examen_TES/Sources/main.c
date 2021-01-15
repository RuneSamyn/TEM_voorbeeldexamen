#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int counter;

int main(int argc, char *argv[])
{
    char* logfile;
    int writeInterval;
    time_t current_time;
    struct tm * time_info;
    char timeString[22];  // space for "dd-mm-YYYY HH:MM:SS\0"

    if (argc == 3)
    {
        logfile = argv[1];
        sscanf(argv[2], "%i", &writeInterval);
        FILE *f = fopen(logfile, "a");

        if (f != NULL)
        {
            for (;;)
            {
                printf("save time to file\r\n");
                time(&current_time);
                time_info = localtime(&current_time);

                strftime(timeString, sizeof(timeString), "%d/%m/%Y %H:%M:%S\n\r", time_info);
                fputs(timeString, f);
                fflush(f);
                sleep(writeInterval);
            }
            
        }
        else
        {
            printf("couldn't open/make file\n\r");
        }
        fclose(f);
    }
    else
    {
        printf("error: command does not contain the correct arguments\r\n");
    }

    return 0;
}