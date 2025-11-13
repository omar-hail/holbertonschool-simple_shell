#include "shell.h"

/**
 * shell_loop - main loop of the shell
 * @prog_name: name of the shell program (argv[0])
 *
 * Return: 0 on success
 */
int shell_loop(char *prog_name)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **args;

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

		if (nread > 1 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		args = split_line(line);
		if (!args || !args[0])
		{
			free(args);
			continue;
		}

		if (check_builtin(args))
		{
			free(args);
			continue;
		}

		if (execute_command(args, prog_name) == -1)
			print_error(prog_name, args[0]);

		free(args);
	}

	free(line);
	return (0);
}
