#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 600

int main(int argc, char *argv[])
{
    int x = 0;
    int c = 0;
    char *path;
    char *txt;

    printf("Opdracht voorbeeldexamen read seek to begin of file\r\n");

    if (argc == 3)
    {
        path = argv[1];
        txt = argv[2];
        FILE *f = fopen(path, "a+");

        if (f != NULL)
        {
            fseek(f, 0, SEEK_SET);
            fputs(txt, f);
        }
        else
        {
            printf("couldn't open file\n\r");
        }
    }
    else
    {
        printf("error: command does not contain a filepath or replacement text\r\n");
        printf("cmd => ./seekBegin path newText\r\n");
    }

    return 0;
}