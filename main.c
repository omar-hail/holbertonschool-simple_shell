#include "shell.h"

int last_status = 0;
int should_exit = 0;

/**
 * main - Entry point of the simple shell
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: exit status of last command
 */
int main(int argc, char **argv)
{
	(void)argc;

	shell_loop(argv[0]);
	return (last_status);
}
