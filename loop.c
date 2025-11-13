#include "shell.h"

/**
 * read_line - reads a line from stdin
 * @line: pointer to buffer
 * @len: pointer to length
 *
 * Return: number of characters read, or -1 on EOF
 */
ssize_t read_line(char **line, size_t *len)
{
	ssize_t nread;

	nread = getline(line, len, stdin);
	if (nread == -1 && isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n", 1);

	return (nread);
}

/**
 * process_line - process and execute input line
 * @line: input string
 * @prog_name: program name
 */
void process_line(char *line, char *prog_name)
{
	char **args;

	if (line[0] == '\0')
		return;

	args = split_line(line);
	if (!args || !args[0])
	{
		free(args);
		return;
	}

	if (check_builtin(args))
	{
		free(args);
		return;
	}

	if (execute_command(args, prog_name) == -1)
		print_error(prog_name, args[0]);

	free(args);
}

/**
 * shell_loop - main loop of the shell
 * @prog_name: name of the shell program
 *
 * Return: 0 on success
 */
int shell_loop(char *prog_name)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		nread = read_line(&line, &len);
		if (nread == -1)
			break;

		if (nread > 1 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		process_line(line, prog_name);
	}

	free(line);
	return (0);
}
