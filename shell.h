#ifndef _SHELL_H_
#define _SHELL_H_

#include <sys/types.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

char *get_command_path(char *command, char **envp);
void handle_child_process(char *command, char **arguments, char **envp);
void handle_parent_process(pid_t pid, char *command);
void handle_command(char *command_path, char **arguments, pid_t *pid,
										char **envp);
void print_environment(char **envp);

#endif
