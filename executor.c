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

	(void)prog_name;

	/* find command in PATH */
	cmd_path = find_command(args[0]);
	if (!cmd_path)
		return (-1); /* command not found → NO fork */

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		free(cmd_path);
		return (0);
	}

	if (child_pid == 0)
	{
		/* in child */
		if (execve(cmd_path, args, environ) == -1)
		{
			perror(args[0]);
			free(cmd_path);
			exit(EXIT_FAILURE);
		}
	}

	/* parent waits */
	wait(NULL);
	free(cmd_path);
	return (0);
}
