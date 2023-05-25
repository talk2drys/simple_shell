#include "shell.h"
#include <stdlib.h>
#include <string.h>

/**
 * is_string_in_array - Check if a string is present in an array of strings.
 *
 * @target: The string to search for.
 * @array: The array of strings.
 * @size: The size of the array.
 *
 * Return: 1 if the string is found in the array, 0 otherwise.
 */
int is_string_in_array(const char *target, const char **array, int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		if (strcmp(target, array[i]) == 0)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * handle_built_in_command - Handle built-in commands.
 *
 * @command: The command to handle.
 * @envp: environmental variable
 *
 * This function handles built-in commands specific to the shell. Currently,
 * it only supports the "exit" command, which terminates the shell process.
 */
void handle_built_in_command(char *command, char **envp)
{
	if (strcmp(command, "exit") == 0)
		exit(EXIT_SUCCESS);
	if (strcmp(command, "env") == 0)
		print_environment(envp);
}
