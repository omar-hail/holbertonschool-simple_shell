#include "shell.h"

/**
 * main - Entry point of the simple shell
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	(void)argc;

	return (shell_loop(argv[0]));
}
