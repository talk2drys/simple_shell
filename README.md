# 0x16. C - Simple Shell

This is a basic implementation of a simple shell in C. It provides a command-line interface 
where users can enter commands, and the shell will execute them by forking a child process.

## Features

- Executes commands entered by the user
- Handles command-line arguments
- Supports PATH resolution to find the full path of a command
- Prints appropriate error messages for invalid commands
- Provides a prompt for user input

## Getting Started

To compile the code, use the following command:
To run the simple shell, execute the compiled binary:



## Usage

Once the simple shell is running, you can enter commands and press Enter to execute them. 
The shell will display the output or any error messages resulting from the command.

Example usage:

```shell
#cisfun$ ls
file1.txt file2.txt directory
#cisfun$ echo "Hello, world!"
Hello, world!
#cisfun$ exit
```

To exit the simple shell, you can use the `exit` command or press Ctrl+C.

## Customization

You can customize the shell prompt by modifying the `prompt` variable in the `main` function of `main.c`.

## Limitations

- The shell currently supports a maximum command length of 100 characters. Longer commands will be truncated.
- The maximum number of command-line arguments supported is 10. Additional arguments will be ignored.
- The shell does not support advanced features such as piping, input/output redirection, or background processes.

## Contributing

Contributions to this simple shell project are welcome! If you find any bugs or have 
suggestions for improvements, please open an issue or submit a pull request.

