#ifndef _SHELL_H_
#define _SHELL_H_

#include <sys/types.h>

#define MAX_COMMAND_LENGTH 256
#define MAX_ARGUMENTS 10

char *get_command_path(char *command, char **envp);
void handle_child_process(char *command, char **arguments, char **envp);
void handle_parent_process(pid_t pid, char *command);
void handle_command(char *command_path, char **arguments, pid_t *pid,
										char **envp);
void print_environment(char **envp);
char *get_command_path(char *command, char **envp);

char *get_absolute_command_path(char *command);
char *search_command_in_path(char *command, char *path_env);
int is_string_in_array(const char *target, const char **array, int size);
void handle_built_in_command(char *command);
int isInputTerminal(void);
void handleInput(char *input, int size, char **arguments);
void processCommand(char *command, char **arguments, char **envp);
void printPrompt(const char *prompt);
ssize_t readCommand(char *command, size_t size);
#endif
