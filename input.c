#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * isInputTerminal - Check if the input is coming from a terminal.
 *
 * Return: 1 if the input is from a terminal, 0 otherwise.
 */
int isInputTerminal(void) { return (isatty(STDIN_FILENO)); }

/**
 * printPrompt - Print the specified prompt to the standard output.
 *
 * @prompt: The prompt string to be printed.
 */
void printPrompt(const char *prompt)
{
	printf("%s", prompt);
	fflush(stdout);
}

/**
 * readCommand - Read input from the standard input into the specified buffer.
 *
 * @command: Buffer to store the read input.
 * @size: size of buffer
 *
 * Return: The number of bytes read, or -1 if an error occurred.
 */
ssize_t readCommand(char *command, size_t size)
{
	memset(command, 0, size - 1);
	return (read(STDIN_FILENO, command, size - 1));
}

/**
 * handleInput - Handle the input by tokenizing it into arguments.
 *
 * @input: The input string to be processed.
 * @size: The size of the input buffer.
 * @arguments: An array to store the tokenized arguments.
 */
void handleInput(char *input, __attribute__((unused)) int size,
								 char **arguments)
{
	char *token;
	int arg_count = 0;

	if (input[0] == '\n')
		return;

	input[strcspn(input, "\n")] = '\0';

	token = strtok(input, " ");

	while (token != NULL && arg_count < MAX_ARGUMENTS)
	{
		stripSurroundingSpaces(token);
		arguments[arg_count++] = token;
		token = strtok(NULL, " ");
	}
	arguments[arg_count] = NULL;
}

/**
 * processCommand - Process the command by determining if it is a built-in
 * command or an external command and handle it accordingly.
 *
 * @ctx: runtime context
 * @command: The command to be processed.
 */
void processCommand(struct Context *ctx, char *command)
{
	char *command_path;
	pid_t pid;
	const char *array[] = {"exit"};
	const int size = sizeof(array) / sizeof(array[0]);

	if (is_string_in_array(command, array, size))
	{
		handle_built_in_command(ctx, command);
	}
	else
	{
		command_path = get_command_path(command, ctx->envp);
		handle_command(ctx, command_path, &pid);
		free(command_path);
	}
}
