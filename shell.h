#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

int is_empty(char *s);
char **split_line(char *line);
char *find_path(char *cmd);

#endif /* SHELL_H */
