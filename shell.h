#ifndef _SHELL_H_
#define _SHELL_H_

#include "context.h"
#include <sys/types.h>

#define MAX_COMMAND_LENGTH 256
#define MAX_ARGUMENTS 10

char *get_command_path(char *command, char **envp);
void print_environment(char **envp);
char *get_command_path(char *command, char **envp);

char *get_absolute_command_path(char *command);
char *search_command_in_path(char *command, char *path_env);
int is_string_in_array(const char *target, const char **array, int size);
int isInputTerminal(void);
void handleInput(char *input, int size, char **arguments);
void printPrompt(const char *prompt);
ssize_t readCommand(char *command, size_t size);
int get_array_length(char **array);
void printShellError(struct Context *ctx, const char *command,
										 const char *error);

/* Command Handler */
void handle_command(struct Context *ctx, char *command_path, pid_t *pid);
void handle_child_process(struct Context *ctx, char *command);
void handle_parent_process(struct Context *ctx, pid_t pid, char *command);
void handle_built_in_command(struct Context *ctx, char *command);
void processCommand(struct Context *ctx, char *command);

void stripSurroundingSpaces(char *str);
#endif
