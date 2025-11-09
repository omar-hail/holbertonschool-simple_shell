#include "shell.h"

/**
 * handle_builtin - check for built-in commands
 * @cmd: input line
 *
 * Return: 1 if shell should exit, 0 otherwise
 */
int handle_builtin(char *cmd)
{
	if (strcmp(cmd, "exit") == 0)
	{
		return (1);
	}
	return (0);
}
