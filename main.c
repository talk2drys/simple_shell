#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * main - Entry point of the simple shell program
 * @argc: The argument count
 * @argv: The argument vector
 * @envp: The environment variables
 *
 * This function implements a basic command line interpreter, which displays a
 * prompt, waits for the user to enter a command, and executes the command by
 * forking a child process. The function continues this loop until the user
 * enters the end-of-file condition (Ctrl+D). It uses the `get_command_path`
 * function to get the full path of the command based on the directories listed
 * in the PATH environment variable. Then, it calls the `handle_command`
 * function to handle the command execution.
 *
 * Return: Always 0.
 */
int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv,
				 char **envp)
{
	char command[MAX_COMMAND_LENGTH];
	char prompt[] = "#cisfun$ ";
	ssize_t bytesRead;
	struct Context context;

	context.arguments = argv;
	context.envp = envp;

	while (1)
	{
		char *arguments[MAX_ARGUMENTS + 1];

		if (isInputTerminal())
			printPrompt(prompt);

		bytesRead = readCommand(command, MAX_COMMAND_LENGTH);
		if (bytesRead == -1)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		else if (bytesRead == 0)
		{
			exit(EXIT_SUCCESS);
		}
		else if (command[0] == '\n')
			continue;

		handleInput(command, bytesRead, arguments);
		processCommand(&context, command);
	}

	return (0);
}
