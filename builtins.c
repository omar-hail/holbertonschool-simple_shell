#include "shell.h"

/**
 * check_builtin - checks if command is a builtin
 * @args: command arguments
 *
 * Return: 1 if builtin executed, 0 otherwise
 */
int check_builtin(char **args)
{
	if (_strcmp(args[0], "exit") == 0)
	{
		builtin_exit();
		return (1);
	}

	if (_strcmp(args[0], "env") == 0)
	{
		builtin_env();
		return (1);
	}

	return (0);
}

/**
 * builtin_exit - exits the shell
 */
void builtin_exit(void)
{
	exit(0);
}

/**
 * builtin_env - prints the environment variables
 */
void builtin_env(void)
{
	print_environment();
}
