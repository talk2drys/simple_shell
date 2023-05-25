#include "shell.h"
#include <string.h>
#include <stdlib.h>

int is_string_in_array(const char *target, const char **array, int size) {
	int i;
	for (i = 0; i < size; i++) {
		if (strcmp(target, array[i]) == 0) {
			return 1;
		}
	}
	return (0);
}


void handle_built_in_command(char *command)
{
	if (strcmp(command, "exit") == 0) {
		exit(EXIT_SUCCESS);
	}
}
