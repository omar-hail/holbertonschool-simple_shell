#include "shell.h"

/**
 * _strlen - returns length of a string
 * @s: string
 *
 * Return: length of string
 */
int _strlen(char *s)
{
	int i = 0;

	while (s && s[i])
		i++;

	return (i);
}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: 0 if equal, positive or negative otherwise
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;

	return (s1[i] - s2[i]);
}

/**
 * _strdup - duplicates a string
 * @s: string to duplicate
 *
 * Return: new allocated string, or NULL
 */
char *_strdup(const char *s)
{
	char *dup;
	int len = 0, i;

	if (!s)
		return (NULL);

	while (s[len])
		len++;

	dup = malloc(len + 1);
	if (!dup)
		return (NULL);

	for (i = 0; i < len; i++)
		dup[i] = s[i];

	dup[i] = '\0';
	return (dup);
}
