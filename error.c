#include "context.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * printShellError - Print a shell error message in the format of /bin/sh.
 *
 * @ctx: runtime `Context` structure.
 * @command: The command that caused the error.
 * @error: The specific error message.
 *
 * This function prints an error message in the format used by /bin/sh,
 * indicating the command and the specific error encountered. It uses the
 * provided context structure to access the program name and other necessary
 * information. The error message is printed to the standard error stream.
 */
void printShellError(struct Context *ctx, const char *command,
										 const char *error)
{
	fprintf(stderr, "%s: %s: %s\n", ctx->arguments[0], command, error);
}
