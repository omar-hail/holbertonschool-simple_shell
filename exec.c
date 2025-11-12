d
+27
-14
lines changed
Search within code
 
‎exec.c‎
+11
-8
Lines changed: 11 additions & 8 deletions
Original file line number	Diff line number	Diff line change
@@ -18,7 +18,7 @@ static char *find_in_path(char *cmd)
		}
	}

	if (!path)
	if (!path || path[0] == '\0')
		return (NULL);

	path_copy = malloc(strlen(path) + 1);
@@ -55,7 +55,7 @@ static char *find_in_path(char *cmd)
	return (NULL);
}

int execute_command(char *line, char **argv)
int execute_command(char *line, char **argv, int cmd_count)
{
	pid_t pid;
	int status;
@@ -83,16 +83,17 @@ int execute_command(char *line, char **argv)
		if (access(args[0], X_OK) != 0)
		{
			perror(argv[0]);
			return (1);
			return (127);
		}
	}
	else
	{
		cmd_path = find_in_path(args[0]);
		if (!cmd_path)
		{
			perror(argv[0]);
			return (1);
			fprintf(stderr, "%s: %d: %s: not found\n",
				argv[0], cmd_count, args[0]);
			return (127);
		}
	}

@@ -112,15 +113,15 @@ int execute_command(char *line, char **argv)
			if (execve(args[0], args, environ) == -1)
			{
				perror(argv[0]);
				exit(EXIT_FAILURE);
				exit(127);
			}
		}
		else
		{
			if (execve(cmd_path, args, environ) == -1)
			{
				perror(argv[0]);
				exit(EXIT_FAILURE);
				exit(127);
			}
		}
	}
@@ -132,6 +133,8 @@ int execute_command(char *line, char **argv)
	if (cmd_path)
		free(cmd_path);

	return (0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

