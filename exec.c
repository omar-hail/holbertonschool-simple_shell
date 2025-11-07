#include "shell.h"

int execute_command(char *line, char **argv)
{
	pid_t pid;
	int status;
	char *args[64];
	char *token;
	int i = 0;

	token = strtok(line, " \t");
	if (token == NULL)
		return (0);

	while (token != NULL && i < 63)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " \t");
	}
	args[i] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror(argv[0]);
		return (1);
	}

	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
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
