#include "shell.h"

/**
 * find_command - search for a command in the PATH
 * @command: command name (e.g. "ls", "../hbtn_ls")
 *
 * Return: full path to command, or NULL if not found
 */
char *find_command(char *command)
{
	char *env_path, *path, *dir, *full_path;
	int len;

	/* إذا فيه / في أي مكان → اعتبره مسار مباشر */
	if (strchr(command, '/') != NULL)
		return (_strdup(command));

	env_path = _getenv("PATH");
	if (!env_path)
		return (NULL);

	path = _strdup(env_path);
	if (!path)
		return (NULL);

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
