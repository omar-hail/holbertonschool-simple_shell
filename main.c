#include "shell.h"

/**
 * main - Entry point for the simple shell program
 * @argc: Argument count (unused)
 * @argv: Argument vector (used for program name)
 *
 * Return: Exit status from the shell loop
 */
int main(int argc, char **argv)
{
	int status;

	(void)argc; /* Unused variable */

	status = shell_loop(argv);
	return (status);
}
