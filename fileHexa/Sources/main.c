#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 600

int main(int argc, char *argv[])
{
  int x = 0;
  int c = 0;
  char *path;

  printf("Opdracht voorbeeldexamen read file hexadecimaal\r\n");

  if (argc == 2)
  {
    path = argv[1];
    FILE *f = fopen(path, "r");

    if (f != NULL)
    {
      while (x < 20 && (c = fgetc(f)) != EOF)
      {
        x++;
        printf("0x%02X ", c);
        if ((x % 10) == 0)
          printf("\r\n");
        else if ((x % 5) == 0)
          printf("\t");
      }
    }
    else
    {
      printf("couldn't open file\n\r");
    }
    if ((x % 10) != 0)
      printf("\r\n");
  }
  else
  {
    printf("error: command does not contain a filepath\r\n");
  }

  return 0;
}