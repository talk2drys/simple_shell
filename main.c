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

	while (1)
	{
		char *arguments[MAX_ARGUMENTS + 1];

		if (isInputTerminal())
			printPrompt(prompt);

		bytesRead = readCommand(command);
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
		processCommand(arguments[0], arguments, envp);
	}

	return (0);
}

/**
 * handle_child_process - Handles the child process after forking
 * @command: The command to be executed
 * @arguments: The arguments for the command
 * @envp: pointer of char to environment variables
 *
 * This function is responsible for executing the specified command
 * with the given arguments in the child process using the `execve`
 * system call.
 */
void handle_child_process(char *command, char **arguments, char **envp)
{
	int ret = execve(command, arguments, envp);

	perror("execve");
	exit(ret);
}

/**
 * handle_parent_process - Handles the parent process after forking
 * @pid: The process ID of the child process
 * @command: The command that was executed
 *
 * This function waits for the child process specified by @pid to complete
 * and checks its exit status. If the child process exited normally, it checks
 * if the exit status indicates that the command was not found, and prints an
 * appropriate error message if necessary.
 */
void handle_parent_process(pid_t pid, char *command)
{
	int status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		exit(1);
	}

	if (WIFEXITED(status))
	{
		int exit_status = WEXITSTATUS(status);

		if (exit_status == 127)
		{
			fprintf(stderr, "%s: command not found\n", command);
		}
	}
}

/**
 * handle_command - Handles the execution of a command in the shell
 *
 * @command_path: The path to the command
 * @arguments: The arguments for the command
 * @pid: Pointer to the process ID of the child process
 * @envp: The environment variables
 */
void handle_command(char *command_path, char **arguments, pid_t *pid,
										char **envp)
{
	if (command_path == NULL)
	{
		fprintf(stderr, "%s: command not found\n", arguments[0]);
		return;
	}

	*pid = fork();

	if (*pid < 0)
	{
		perror("fork");
		exit(1);
	}
	else if (*pid == 0)
		handle_child_process(command_path, arguments, envp);
	else
		handle_parent_process(*pid, arguments[0]);
}
