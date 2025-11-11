#include "shell.h"

/**
 * main - Entry point for the simple shell program
 * @argc: Argument count (unused)
 * @argv: Argument vector
 *
 * Return: Exit status from the shell loop
 */
int main(int argc, char **argv)
{
	int status;

	(void)argc;

	status = shell_loop(argv);
	return (status);
}
