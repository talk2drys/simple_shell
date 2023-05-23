#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * main - Entry point of the simple_shell program
 *
 * This function serves as the entry point for the simple_shell program. It
 * implements a basic command line interpreter that displays a prompt, waits
 * for the user to enter a command, and executes the command by forking a child
 * process. The function continues this loop until the user enters the
 * end-of-file condition (Ctrl+D).
 *
 * Return: Always 0.
 */

int main(int argc, char **argv, char **envp)
{
	char command[MAX_COMMAND_LENGTH];
	char prompt[] = "#cisfun$ ";
	pid_t pid;
	while (1)
	{
		char *arguments[MAX_ARGUMENTS + 1];
		char *token;
		int arg_count = 0;
		printf("%s", prompt);
		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			printf("\n");
			break;
		}
		command[strcspn(command, "\n")] = '\0';
		token = strtok(command, " ");
		while (token != NULL && arg_count < MAX_ARGUMENTS)
		{
			arguments[arg_count++] = token;
			token = strtok(NULL, " ");
		}
		arguments[arg_count] = NULL;
		// Check if command exists in the PATH
		char *command_path = get_command_path(arguments[0], envp);
		if (command_path == NULL)
		{
			fprintf(stderr, "%s: command not found\n", arguments[0]);
			continue;
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0)
		{
			handle_child_process(command_path, arguments, envp);
		}
		else
		{
			handle_parent_process(pid, arguments[0]);
		}
		free(command_path);
	}
	return 0;
}

/**
 * handle_child_process - Handles the child process after forking
 * @command: The command to be executed
 * @arguments: The arguments for the command
 * #envp: pointer of char to environment variables
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
