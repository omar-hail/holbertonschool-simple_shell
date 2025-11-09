#include "shell.h"

/**
 * shell_loop - main loop of the shell
 * @argv: program name (used for error messages)
 *
 * Return: last command status
 */
int shell_loop(char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *cmd;
	int i, end;
	int cmd_count = 0;
	int last_status = 0;

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

		/* Skip leading spaces */
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		cmd = line + i;

		/* Trim trailing spaces */
		end = strlen(cmd) - 1;
		while (end >= 0 && (cmd[end] == ' ' || cmd[end] == '\t'))
		{
			cmd[end] = '\0';
			end--;
		}

		if (cmd[0] == '\0')
			continue;

		/* Check for built-in commands (exit, env, etc.) */
		if (handle_builtin(cmd))
			continue;

		cmd_count++;
		last_status = execute_command(cmd, argv, cmd_count);
	}

	free(line);
	return (last_status);
}

