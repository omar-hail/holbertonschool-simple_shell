#include "shell.h"

int execute_command(char *line, char **argv)
{
	pid_t pid;
	int status;
	char *args[2];

	pid = fork();
	if (pid == -1)
	{
		perror(argv[0]);
		return (1);
	}

	if (pid == 0)
	{
		args[0] = line;
		args[1] = NULL;

		if (execve(line, args, environ) == -1)
		{
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}

	return (0);
}
