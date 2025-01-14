# Pipex
This project will let you discover in detail a UNIX mechanism that you already know by using it in your program.


1. Folder Structure

A clear folder structure will make your project more maintainable and easy to navigate. A typical structure might look like this:

pipex/
│
├── src/                # Source files
│   ├── main.c          # Entry point, handles argument parsing
│   ├── pipex.c         # Functions for handling pipes, forks, and execution
│   ├── utils.c         # Utility functions (error handling, string manipulation, etc.)
│   └── execution.c     # Functions for command execution and file redirection
│
├── include/            # Header files
│   ├── pipex.h         # Common declarations, structs, and function prototypes
│
├── Makefile            # Makefile for compiling the project
└── README.md           # Project description and instructions

2. File Breakdown

    main.c:
    This file should contain your main function, which will:
        Parse the command-line arguments.
        Handle input/output redirection (files).
        Manage pipes between processes.
        Handle errors and edge cases.

    pipex.c:
    This file will contain functions for the core logic of pipe creation, process management (via fork), and piping data between processes using dup2 or similar system calls.

    execution.c:
    This file will handle executing commands using execvp() or execve(). This is where you perform the actual command execution after setting up pipes, file redirections, etc.

    utils.c:
    This file will contain utility functions like:
        Error handling functions (e.g., perror() or custom error messages).
        Helper functions for string manipulation (e.g., splitting commands).
        Functions for opening files (e.g., for redirection).

    pipex.h:
    Header file with declarations for your functions and any necessary structs. This file will be included in your source files.

3. Main Concepts for Pipex

These are the key concepts your project will deal with:

    Pipes:
    You will need to create pipes between commands to allow communication between them. This can be done using pipe() system calls and dup2() for redirecting file descriptors.

    Forking:
    You'll fork processes using fork() and execute commands in those child processes with execvp() or execve().

    Redirection:
    Handling input/output redirection (e.g., using files) will involve opening the files using open() and using dup2() to duplicate file descriptors for the child processes.

4. Key Functions

    Argument Parsing:
    In main.c, parse the arguments and handle redirections. You'll need to check if the command is piped and if redirection files are provided.

int main(int argc, char *argv[]) {
    // Parse arguments for file names and commands
    // Handle input/output redirection
    // Create pipes and fork processes for each command
}

Creating Pipes and Forking:
In pipex.c, create pipes and fork processes. You'll need to ensure each process gets the correct input and output file descriptors.

void pipex(int argc, char *argv[]) {
    int pipefd[2];
    pid_t pid;

    for (int i = 0; i < num_commands; i++) {
        pipe(pipefd);  // Create a pipe
        pid = fork();
        if (pid == 0) {
            // Child process
            // Redirect stdin/stdout and execute command
        } else {
            // Parent process
            // Wait for child to finish
        }
    }
}

Executing Commands:
In execution.c, use execvp() to execute the commands. Ensure you handle the arguments correctly for each command in the pipe chain.

void execute_command(char *cmd, char *envp[]) {
    char **args = parse_args(cmd);
    execvp(args[0], args);
    perror("execvp failed");
    exit(EXIT_FAILURE);
}

Redirection:
Handle input/output redirection in pipex.c or execution.c. If a command should read from a file, use open() to get the file descriptor, and dup2() to redirect the input.

    void redirect_input(char *file) {
        int fd = open(file, O_RDONLY);
        if (fd == -1) {
            perror("open input file");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
    }

    void redirect_output(char *file) {
        int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("open output file");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }

5. Error Handling

You should handle errors throughout the program, especially with system calls like pipe(), fork(), execvp(), and open(). Always check the return values and handle errors gracefully with appropriate messages.
