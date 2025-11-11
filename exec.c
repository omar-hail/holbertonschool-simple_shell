#include "shell.h"

/**
 * check_executable_in_dir - Build full path and check if executable exists
 * @dir: Directory to check in
 * @cmd: Command name
 *
 * Return: Newly allocated string with full path if found, NULL otherwise
 */
char *check_executable_in_dir(char *dir, char *cmd)
{
	char *full_path;
	size_t len_dir = strlen(dir), len_cmd = strlen(cmd);

	full_path = malloc(len_dir + len_cmd + 2);
	if (!full_path)
		return (NULL);

	strcpy(full_path, dir);
	full_path[len_dir] = '/';
	strcpy(full_path + len_dir + 1, cmd);

	if (access(full_path, X_OK) == 0)
		return (full_path);

	free(full_path);
	return (NULL);
}

/**
 * find_in_path - Search for a command in the system PATH
 * @cmd: Command to locate
 *
 * Return: Full path to the command if found, NULL otherwise
 */
char *find_in_path(char *cmd)
{
	char *path = NULL, *path_copy, *token, *found_path = NULL;
	int i;

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path = environ[i] + 5;
			break;
		}
	}
	if (!path || path[0] == '\0')
		return (NULL);

	path_copy = malloc(strlen(path) + 1);
	if (!path_copy)
		return (NULL);
	strcpy(path_copy, path);

	token = strtok(path_copy, ":");
	while (token)
	{
		found_path = check_executable_in_dir(token, cmd);
		if (found_path)
		{
			free(path_copy);
			return (found_path);
		}
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
