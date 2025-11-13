#include "shell.h"

/**
 * find_command - search for a command in the PATH
 * @command: command name (e.g. "ls")
 *
 * Return: full path to command, or NULL if not found
 */
char *find_command(char *command)
{
	char *path = _strdup(getenv("PATH"));
	char *dir, *full_path;
	int len;

	if (!path)
		return (NULL);

	/* if command starts with / or ./ → do not search PATH */
	if (command[0] == '/' || (command[0] == '.' && command[1] == '/'))
	{
		free(path);
		return (_strdup(command));
	}

	dir = strtok(path, ":");
	while (dir)
	{
		len = _strlen(dir) + _strlen(command) + 2;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path);
			return (NULL);
		}

		sprintf(full_path, "%s/%s", dir, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path);
	return (NULL);
}
