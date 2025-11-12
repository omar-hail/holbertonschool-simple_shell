#ifndef SHELL_H
#define SHELL_H

/* ==== Standard Libraries ==== */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>

/* ==== Global Environment ==== */
extern char **environ;

/* ==== Function Prototypes ==== */
int is_empty(char *s);
char **split_line(char *line);
char *find_path(char *cmd);

/* optional for later tasks */
int shell_loop(char **argv);
int execute_command(char **args, char **argv, int cmd_count);

#endif /* SHELL_H */

