#include "shell.h"

/**
 * print_error - prints error message like sh
 * @prog: program name (argv[0])
 * @cmd: command that was not found
 */
void print_error(char *prog, char *cmd)
{
	write(STDERR_FILENO, prog, _strlen(prog));
	write(STDERR_FILENO, ": 1: ", 5);
	write(STDERR_FILENO, cmd, _strlen(cmd));
	write(STDERR_FILENO, ": not found\n", 12);
}
