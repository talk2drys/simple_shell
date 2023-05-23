#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * get_command_path - Get the full path of a command
 * @command: The command to find the path for
 * @envp: The environment variables
 *
 * This function retrieves the full path of the specified command by searching
 * through the directories listed in the PATH environment variable.
 *
 * Return: The full path of the command if found, NULL otherwise.
 */
char *get_command_path(char *command, __attribute__((unused)) char **envp)
{
	char *path_env = getenv("PATH");
	char *token;
	char *path;
	char *command_path = malloc(MAX_COMMAND_LENGTH * sizeof(char));

	if (command_path == NULL)
	{
		perror("malloc");
		exit(1);
	}

	token = strtok(path_env, ":");
	while (token != NULL)
	{
		path = malloc((strlen(token) + strlen(command) + 2) * sizeof(char));
		if (path == NULL)
		{
			perror("malloc");
			exit(1);
		}
		sprintf(path, "%s/%s", token, command);
		if (access(path, X_OK) == 0)
		{
			strncpy(command_path, path, MAX_COMMAND_LENGTH);
			free(path);
			return (command_path);
		}
		free(path);
		token = strtok(NULL, ":");
	}

	free(command_path);
	return (NULL);
}
