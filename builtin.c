#include "shell.h"

/**
 * handle_builtin - checks and executes built-in commands
 * @cmd: input command
 *
 * Return: 1 if a built-in command was executed, 0 otherwise
 */
int handle_builtin(char *cmd)
{
	int i;

	/* Built-in: exit */
	if (strcmp(cmd, "exit") == 0)
	{
		exit(0);
	}

	/* Built-in: env */
	if (strcmp(cmd, "env") == 0)
	{
		for (i = 0; environ[i]; i++)
		{
			write(STDOUT_FILENO, environ[i], strlen(environ[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		return (1);
	}

	return (0);
}

