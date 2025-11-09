#include "shell.h"

static char *find_in_path(char *cmd)
{
	char *path = NULL;
	char *path_copy;
	char *token;
	char *full_path;
	size_t len_cmd, len_dir;
	int i;

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path = environ[i] + 5;
			break;
		}
	}

	if (!path)
		return (NULL);

	path_copy = malloc(strlen(path) + 1);
	if (!path_copy)
		return (NULL);
	strcpy(path_copy, path);

	len_cmd = strlen(cmd);
	token = strtok(path_copy, ":");
	while (token)
	{
		len_dir = strlen(token);
		full_path = malloc(len_dir + 1 + len_cmd + 1);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		strcpy(full_path, token);
		full_path[len_dir] = '/';
		strcpy(full_path + len_dir + 1, cmd);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

int execute_command(char *line, char **argv)
{
	pid_t pid;
	int status;
	char *args[64];
	char *token;
	int i = 0;
	char *cmd_path = NULL;
	int has_slash = 0;

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

	if (strchr(args[0], '/'))
	{
		has_slash = 1;
		if (access(args[0], X_OK) != 0)
		{
			perror(argv[0]);
			return (1);
		}
	}
	else
	{
		cmd_path = find_in_path(args[0]);
		if (!cmd_path)
		{
			perror(argv[0]);
			return (1);
		}
	}

	pid = fork();
	if (pid == -1)
	{
		perror(argv[0]);
		if (cmd_path)
			free(cmd_path);
		return (1);
	}

	if (pid == 0)
	{
		if (has_slash)
		{
			if (execve(args[0], args, environ) == -1)
			{
				perror(argv[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (execve(cmd_path, args, environ) == -1)
			{
				perror(argv[0]);
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}

	if (cmd_path)
		free(cmd_path);

	return (0);
}

