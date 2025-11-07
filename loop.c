#include "shell.h"

void shell_loop(char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *cmd;
	int i, end;

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

		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;

		cmd = line + i;

		end = strlen(cmd) - 1;
		while (end >= 0 && (cmd[end] == ' ' || cmd[end] == '\t'))
		{
			cmd[end] = '\0';
			end--;
		}

		if (cmd[0] == '\0')
			continue;

		execute_command(cmd, argv);
	}

	free(line);
}
