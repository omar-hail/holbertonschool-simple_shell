#include "shell.h"

/**
 * is_empty - check if a string is only spaces or empty
 * @s: string to check
 * Return: 1 if empty, 0 otherwise
 */
int is_empty(char *s)
{
    int i;

    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
            return (0);
    }
    return (1);
}

/**
 * parse_line - split input line into tokens
 * @line: user input
 * Return: array of arguments (NULL terminated)
 */
char **parse_line(char *line)
{
    char *token;
    char **args;
    int bufsize = 64, i = 0;

    args = malloc(sizeof(char *) * bufsize);
    if (!args)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\n");
    while (token != NULL)
    {
        args[i++] = token;

        if (i >= bufsize)
        {
            bufsize += 64;
            args = realloc(args, sizeof(char *) * bufsize);
            if (!args)
            {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
    return (args);
}

/**
 * main - Simple shell 0.2
 *
 * Return: Always 0
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    pid_t pid;
    int status;
    char **args;

    while (1)
    {
        printf("#cisfun$ ");
        fflush(stdout);

        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            printf("\n");
            break;
        }

        if (is_empty(line))
            continue;

        /* إزالة \n من نهاية السطر */
        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        args = parse_line(line);
        if (args[0] == NULL)
        {
            free(args);
            continue;
        }

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            free(args);
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            if (execve(args[0], args, environ) == -1)
                perror("./shell");
            free(args);
            exit(EXIT_FAILURE);
        }
        else
        {
            wait(&status);
            free(args);
        }
    }

    free(line);
    return (0);
}
