#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 600
#define _ENV_VAR_GIVE_UP 1000

extern char **environ;

typedef struct
{
    char *name;
    char *value;
} env_var;

static int find_equals (const char * s)
{
    int i = 0;
    while (1) {
	if (s[i] == '=') {
	    return i;
	}
	if (s[i] == '\0') {
	    return -1;
	}
	i++;
    }
}

static void split_env_var(const char *variable, env_var *ev)
{
    int equals_pos;
    int env_var_len;

    equals_pos = find_equals(variable);
    if (equals_pos == -1)
    {
        printf("error: could not parse environment\r\n");
    }
    env_var_len = strlen(variable);
    ev->name = strndup(variable, equals_pos);
    if (ev->name == 0)
    {
        printf("error: out of memory\r\n");
    }
    ev->value =
        strndup(variable + equals_pos + 1, env_var_len - equals_pos - 1);
    if (ev->value == 0)
    {
        printf("error: out of memory\r\n");
    }
}

static int count_env_vars()
{
    int i;
    for (i = 0; i < _ENV_VAR_GIVE_UP; i++)
    {
        if (environ[i] == 0)
        {
            return i;
        }
    }
    return 0;
}

static void get_environment(env_var *env_vars, int n_env_vars)
{
    int i = 0;
    for (i = 0; i < n_env_vars; i++)
    {
        split_env_var(environ[i], env_vars + i);
    }
}

int main(int argc, char *argv[])
{
    int x = 0;
    int c = 0;
    char *name;
    char *value;
    int error = 0;

    printf("Opdracht voorbeeldexamen set environment variables\r\n");

    if (argc == 2)
    {
        int i = 0;
        name = strtok(argv[1], "=");
        value = strtok(NULL, "="); // this will return the text between de first and secconde equal sine or in this case, the text between the first equal sine en the end of the string
        error = 0;
    }
    else if (argc == 3)
    {
        name = argv[1];
        value = argv[2];
        error = 0;
    }
    else
    {
        printf("error");
        error = 1;
    }

    if (!error)
    {
        int i;
        int n_env_vars;
        env_var *env_vars;

        setenv(name, value, 1);
        char *result = getenv(name);

        n_env_vars = count_env_vars();
        env_vars = calloc(n_env_vars, sizeof(env_var)); // allocate env_Var struct array for all env vars
        if (!env_vars)
        {
            printf("error: out of memory\r\n");
        }
        get_environment(env_vars, n_env_vars); // get all env variables

        printf("name: value\r\n");
        for (i = 0; i < n_env_vars; i++)
        {
            printf("%s: %s\r\n", env_vars[i].name, env_vars[i].value);
        }
    }

    return 0;
}