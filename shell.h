#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

int shell_loop(char **argv);
int execute_command(char *line, char **argv, int cmd_count);
int handle_builtin(char *cmd);

#endif /* SHELL_H */

