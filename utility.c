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
char *get_command_path(char *command, char **envp)
{
	char *path_env = NULL;
	char *command_path;
	int i;
	char *h;

	command_path = get_absolute_command_path(command);
	if (command_path != NULL)
	{
		return (command_path);
	}

	for (i = 0; envp[i] != NULL; i++)
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = malloc(strlen(envp[i] + 5) + 1);
			if (path_env == NULL)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			strcpy(path_env, envp[i] + 5);
			break;
		}
	}

	h = search_command_in_path(command, path_env);
	free(path_env);
	return (h);
}

/**
 * print_environment - Prints the environment variables.
 *
 * This function takes an array of strings `envp` that represents the
 * environment variables and prints them to the standard output, each on a
 * separate line.
 *
 * @envp: An array of strings representing the environment variables.
 *             The last element of the array must be a null pointer indicating
 *             the end of the list.
 */
void print_environment(char **envp)
{
	char **env = envp;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}

/**
 * get_absolute_command_path - Get the absolute path to a command if it is
 * already an absolute path.
 *
 * @command: The name or path of the command to check.
 * Return:  the absolute path to the command if it exists and is executable,
 *          or NULL if the command is not an absolute path or is not valid.
 */
char *get_absolute_command_path(char *command)
{
	if (command[0] == '/')
	{
		/* Command is already an absolute path, no need to search in PATH */
		if (access(command, X_OK) == 0)
		{
			/* Command exists and is executable */
			char *command_path = malloc((strlen(command) + 1) * sizeof(char));

			if (command_path == NULL)
			{
				perror("malloc");
				exit(1);
			}
			strcpy(command_path, command);
			return (command_path);
		}
		else
		{
			return (NULL); /* Command does not exist or is not executable */
		}
	}

	return (NULL);
}

/**
 * search_command_in_path - Search for a command in the specified PATH
 * environment variable.
 *
 * @command:   The name of the command to search for.
 * @path_env:  The value of the PATH environment variable.
 * Return:     The full path to the command if found, or NULL otherwise.
 */
char *search_command_in_path(char *command, char *path_env)
{
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
