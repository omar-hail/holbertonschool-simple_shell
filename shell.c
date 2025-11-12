#include "shell.h"

/**
 * is_empty - check if a string is only spaces or empty
 * @s: string to check
 * Return: 1 if empty, 0 otherwise
 */
int is_empty(char *s)
{
	int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
			return (0);
	}
	return (1);
}

/**
 * split_line - split user input into arguments
 * @line: input line
 * Return: NULL-terminated array of arguments
 */
char **split_line(char *line)
{
	int bufsize = 64, i = 0;
	char **tokens = malloc(sizeof(char *) * bufsize);
	char *token;

	if (!tokens)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\r\n");
	while (token != NULL)
	{
		tokens[i++] = token;
		if (i >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, sizeof(char *) * bufsize);
			if (!tokens)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, " \t\r\n");
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
 * main - Simple shell 0.3 (Handle PATH + no fork if not found)
 * @argc: argument count
 * @argv: argument vector
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	char *line = NULL, *cmd_path = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	int status;
	char **args;

	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (is_empty(line))
			continue;

		args = split_line(line);
		if (!args[0])
		{
			free(args);
			continue;
		}

		cmd_path = find_path(args[0]);
		if (!cmd_path)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", argv[0], args[0]);
			free(args);
			continue;
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free(args);
			free(cmd_path);
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			if (execve(cmd_path, args, environ) == -1)
				perror(argv[0]);
			free(args);
			free(cmd_path);
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			free(args);
			free(cmd_path);
		}
	}

	free(line);
	return (0);
}
