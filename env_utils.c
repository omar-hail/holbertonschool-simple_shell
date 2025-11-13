#include "shell.h"

/**
 * _getenv - gets the value of an environment variable
 * @name: name of the variable
 *
 * Return: pointer to the value (inside environ), or NULL if not found
 */
char *_getenv(const char *name)
{
	int i = 0;
	int len;

	if (!name)
		return (NULL);

	len = _strlen((char *)name);

	while (environ[i])
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
		i++;
	}

	return (NULL);
}

/**
 * print_environment - prints the environment variables
 */
void print_environment(void)
{
	int i = 0;

	while (environ[i])
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
