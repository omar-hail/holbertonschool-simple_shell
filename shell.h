#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

/* main loop */
int shell_loop(char *prog_name);

/* tokenizer */
char **split_line(char *line);

/* path handling */
char *find_command(char *command);

/* executor */
int execute_command(char **args, char *prog_name);

/* builtins */
int check_builtin(char **args);
void builtin_exit(void);
void builtin_env(void);

/* env utils */
void print_environment(void);

/* string utils */
int _strcmp(char *s1, char *s2);
char *_strdup(const char *s);
int _strlen(char *s);

/* errors */
void print_error(char *prog, char *cmd);

#endif /* SHELL_H */

