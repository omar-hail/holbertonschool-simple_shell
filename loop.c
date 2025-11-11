#include "shell.h"

/**
 * trim_input - Removes leading and trailing spaces or tabs from a line
 * @line: Input string to be trimmed
 *
 * Return: Pointer to the first non-space character
 */
char *trim_input(char *line)
{
	int i = 0, end;

	while (line[i] == ' ' || line[i] == '\t')
		i++;

	line += i;
	end = strlen(line) - 1;

	while (end >= 0 && (line[end] == ' ' || line[end] == '\t'))
	{
		line[end] = '\0';
		end--;
	}

	return (line);
}

/**
 * shell_loop - Main loop of the shell
 * @argv: Program name (used for error messages)
 *
 * Return: Last command status
 */
int shell_loop(char **argv)
{
	char *line = NULL, *cmd;
	size_t len = 0;
	ssize_t nread;
	int cmd_count = 0, last_status = 0;

	(void)argv;

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

		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		cmd = trim_input(line);
		if (cmd[0] == '\0')
			continue;

		if (handle_builtin(cmd))
			continue;

		cmd_count++;
		last_status = execute_command(cmd, argv, cmd_count);
	}

	free(line);
	return (last_status);
}

