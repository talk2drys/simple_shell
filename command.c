#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * handle_parent_process - Handles the parent process after forking
 *
 * @ctx: runtime context
 * @pid: The process ID of the child process
 * @command: The command that was executed
 *
 * This function waits for the child process specified by @pid to complete
 * and checks its exit status. If the child process exited normally, it checks
 * if the exit status indicates that the command was not found, and prints an
 * appropriate error message if necessary.
 */
void handle_parent_process(struct Context *ctx, pid_t pid, char *command)
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
			printShellError(ctx, command, "command not found");
		}
	}
}

/**
 * handle_command - Handles the execution of a command in the shell
 *
 * @ctx: runtime context
 * @command_path: The path to the command
 * @pid: Pointer to the process ID of the child process
 */
void handle_command(struct Context *ctx, char *command_path, pid_t *pid)
{
	if (command_path == NULL)
	{
		fprintf(stderr, "%s: command not found\n", ctx->arguments[0]);
		return;
	}

	*pid = fork();

	if (*pid < 0)
	{
		perror("fork");
		exit(1);
	}
	else if (*pid == 0)
		handle_child_process(ctx, command_path);
	else
		handle_parent_process(ctx, *pid, command_path);
}

/**
 * handle_child_process - Handles the child process after forking
 *
 * @ctx: runtime context
 * @command: The command to be executed
 *
 * This function is responsible for executing the specified command
 * with the given arguments in the child process using the `execve`
 * system call.
 */
void handle_child_process(struct Context *ctx, char *command)
{
	int ret = execve(command, ctx->arguments, ctx->envp);

	perror("execve");
	exit(ret);
}
