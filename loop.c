#include "shell.h"

/**
 * main - simple UNIX command interpreter
 * Return: Always 0
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    pid_t pid;
    int status;
    char *argv[2];

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "#cisfun$ ", 9);

        nread = getline(&line, &len, stdin);
        if (nread == -1) /* EOF (Ctrl+D) */
        {
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);
            break;
        }

        /* إزالة \n */
        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        if (line[0] == '\0')
            continue;

        argv[0] = line;
        argv[1] = NULL;

        pid = fork();
        if (pid == 0)
        {
            if (execve(argv[0], argv, environ) == -1)
                perror("./shell");
            exit(EXIT_FAILURE);
        }
        else if (pid < 0)
        {
            perror("fork");
        }
        else
        {
            waitpid(pid, &status, 0);
        }
    }
    free(line);
    return (0);
}

