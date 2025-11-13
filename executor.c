#include "shell.h"

/**
 * execute_command - execute a command using fork + execve
 * @args: command arguments array
 * @prog_name: shell program name (argv[0])
 *
 * Return: 0 on success, -1 if command not found
 */
int execute_command(char **args, char *prog_name)
{
	pid_t child_pid;
	char *cmd_path;
	int status;

	(void)prog_name;

	/* find command in PATH or as a path */
	cmd_path = find_command(args[0]);
	if (!cmd_path)
	{
		last_status = 127; /* command not found */
		return (-1);       /* NO fork */
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		free(cmd_path);
		last_status = 1;
		return (0);
	}

	if (child_pid == 0)
	{
		if (execve(cmd_path, args, environ) == -1)
		{
			perror(args[0]);
			free(cmd_path);
			exit(EXIT_FAILURE);
		}
	}

	/* parent waits for child */
	if (wait(&status) == -1)
	{
		perror("wait");
		last_status = 1;
	}
	else
	{
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else
			last_status = 1;
	}

	free(cmd_path);
	return (0);
}
