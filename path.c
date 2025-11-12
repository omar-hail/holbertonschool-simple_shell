#include "shell.h"

/**
 * find_path - find full path of a command using PATH variable
 * @cmd: command name (like "ls")
 *
 * Return: full path (malloc'ed) or NULL if not found
 */
char *find_path(char *cmd)
{
	char *path_env, *path_copy, *dir, *full_path;
	size_t len;

	/* إذا كان الأمر موجودًا بشكل مباشر (مثلاً /bin/ls) */
	if (access(cmd, X_OK) == 0)
		return (strdup(cmd));

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		len = strlen(dir) + strlen(cmd) + 2;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}

		snprintf(full_path, len, "%s/%s", dir, cmd);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

