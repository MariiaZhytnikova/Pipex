![image](https://github.com/user-attachments/assets/84e2b236-69ef-4eae-a9d6-6f24ad3516f1)

###### (Pipe Zombie is a zombie in Plants vs. Zombies: The Wacky House.)

## Pipex
This project will let you discover in detail a UNIX mechanism that you already know by using it in your program.

Pipex is a project for the 42 curriculum that implements a simplified version of the Unix piping mechanism. The goal is to execute a command with its input and output piped together, managing multiple processes and file descriptors effectively.
Features

-    Simulates the behavior of a Unix pipeline.
-    Allows the execution of commands using input and output redirection.
-    Supports piping multiple commands together.
-    Handles file descriptors and system calls efficiently.

### Compilation

To compile the project, use:

    make

This will generate the pipex executable.

### Usage

To run the program:

    ./pipex infile "cmd1" "cmd2" outfile

Where:

-    infile is the input file.
-    cmd1 and cmd2 are the commands to execute in the pipe.
-    outfile is the output file.

### Example

    ./pipex input.txt "cat" "grep 42" output.txt

This will:

-    Read input.txt as the input.
-    Pipe the output of cat into grep 42.
-    Write the final output to output.txt.

## Some useful sources:
https://ics.uci.edu/~aburtsev/238P/discussions/d02/discussion02-fork-exec-pipe.pdf
https://www.codequoi.com/en/creating-and-killing-child-processes-in-c/
