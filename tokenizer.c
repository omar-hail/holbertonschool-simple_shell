#include "shell.h"

/**
 * split_line - split a line into arguments
 * @line: input string
 *
 * Return: array of strings (arguments)
 */
char **split_line(char *line)
{
	char **tokens = NULL;
	char *token;
	int bufsize = 64, i = 0;

	tokens = malloc(sizeof(char *) * bufsize);
	if (!tokens)
		return (NULL);

	token = strtok(line, " \t\r\n");
	while (token)
	{
		tokens[i] = token;
		i++;

		if (i >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, sizeof(char *) * bufsize);
			if (!tokens)
				return (NULL);
		}

		token = strtok(NULL, " \t\r\n");
	}

	tokens[i] = NULL;
	return (tokens);
}
