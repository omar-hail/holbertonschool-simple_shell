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
 * main - Simple shell 0.1
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

        /* إزالة '\n' من نهاية السطر */
        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        /* تجاهل المسافات أو الإدخال الفارغ */
        if (is_empty(line))
            continue;

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            char *argv[2];

            argv[0] = line;
            argv[1] = NULL;

            if (execve(argv[0], argv, environ) == -1)
                perror("./shell");
            exit(EXIT_FAILURE);
        }
        else
        {
            wait(&status);
        }
    }

    free(line);
    return (0);
}
