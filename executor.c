#include "shell.h"

/**
 * run_child - executes the command in the child process
 * @cmd_path: full path of the command
 * @args: arguments array
 */
static void run_child(char *cmd_path, char **args)
{
	if (execve(cmd_path, args, environ) == -1)
	{
		perror(args[0]);
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
}

/**
 * wait_for_child - waits for child and updates last_status
 */
static void wait_for_child(void)
{
	int status;

	if (wait(&status) == -1)
	{
		perror("wait");
		last_status = 1;
	}
	else if (WIFEXITED(status))
	{
		last_status = WEXITSTATUS(status);
	}
	else
	{
		last_status = 1;
	}
}

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

	cmd_path = find_command(args[0]);
	if (!cmd_path)
	{
		last_status = 127;
		return (-1);
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
		run_child(cmd_path, args);

	wait_for_child();
	free(cmd_path);
	return (0);
}
