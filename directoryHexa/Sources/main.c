#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#define MAXLEN 600

void readFile(char *name)
{
  int x = 0;
  int c = 0;
  FILE *f;
  f = fopen(name, "r");
  if (f != NULL)
  {
    x = 0;
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
    printf("error: failed to open file %s\r\n", name);
  }
  if ((x % 10) != 0)
    printf("\r\n");
  fclose(f);
}

int main(int argc, char *argv[])
{
  int x = 0;
  int c = 0;
  DIR *d;
  FILE *f;
  struct dirent *dp;
  char *dirName;

  printf("Opdracht voorbeeldexamen read directory hexadecimaal\r\n");

  if (argc == 2)
  {
    dirName = argv[1];

    d = opendir(dirName);
    if (d != NULL)
    {
      while ((dp = readdir(d)) != NULL)
      {
        if (dp->d_type == DT_REG)
        {
          char path[100];
          snprintf(path, 100, "%s%s", dirName, dp->d_name);
          printf(path);
          printf("\n\r");
          readFile(path);
        }
      }
    }
    else
    {
      printf("error: Failed to open directory\n\r");
    }
  }
  else
  {
    printf("error: command does not contain a directory path\r\n");
  }

  return 0;
}