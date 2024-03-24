/*
* myshell.c
* Main file for the custom shell implementation
* Includes the main function and shell prompt printing
* Handles signal handling for Ctrl+C interrupts
* @author: Ayden Jahola
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <linux/limits.h> // For PATH_MAX, see POSIX definition
#include "shell_commands.h"
#include "utility.h"

// Handles SIGINT signal (Ctrl+C) to prevent shell exit
// Reference: POSIX signal handling (https://pubs.opengroup.org/onlinepubs/9699919799/)
void sigint_handler(int sig) {
    // Print newline to maintain clean shell prompt after interrupt
    printf("\n");
    fflush(stdout); // Ensures immediate prompt display (POSIX standard)
}

// Prints shell prompt including the current working directory
// Uses POSIX getcwd() for directory retrieval (https://pubs.opengroup.org/onlinepubs/9699919799/functions/getcwd.html)
void print_prompt() {
    char cwd[1024];
    char *home_dir = getenv("HOME"); // getenv is part of the C standard library
    char *user = getenv("USER");
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd() error"); // Error handling if getcwd fails
        return;
    }

    // Simplifies prompt by replacing the home directory path with '~'
    if (strncmp(cwd, home_dir, strlen(home_dir)) == 0) {
        printf("%s@~%s$ ", user, cwd + strlen(home_dir));
    } else {
        printf("%s@%s$ ", user, cwd);
    }
}

// Main function: entry point of the shell
// Includes setup for the SHELL environment variable and signal handling
int main(int argc, char *argv[]) {
    // Set SHELL environment variable to the shell's executable path
    // Uses /proc/self/exe for path retrieval, a Linux-specific feature
    // Reference: Linux procfs (https://www.kernel.org/doc/Documentation/filesystems/proc.txt)
    char fullpath[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", fullpath, sizeof(fullpath) - 1);
    if (len != -1) {
        fullpath[len] = '\0'; // Null-terminate the path string
        setenv("SHELL", fullpath, 1); // POSIX setenv function (https://pubs.opengroup.org/onlinepubs/9699919799/functions/setenv.html)
    } else {
        perror("readlink to get full path of shell failed");
        exit(EXIT_FAILURE);
    }

    // Install SIGINT handler to manage Ctrl+C interrupts
    signal(SIGINT, sigint_handler); // POSIX signal function (https://pubs.opengroup.org/onlinepubs/9699919799/functions/signal.html)

    char command[1024];
    char *parsedArgs[64];
    int should_run = 1;
    FILE *input_stream = stdin; // stdin is a standard POSIX stream

    // Batch file mode handling if a file name is provided as an argument
    if (argc > 1) {
        input_stream = fopen(argv[1], "r"); // POSIX fopen (https://pubs.opengroup.org/onlinepubs/9699919799/functions/fopen.html)
        if (input_stream == NULL) {
            perror("Failed to open batch file");
            return 1;
        }
    }

    // Main command-processing loop
    while (should_run) {
        if (input_stream == stdin) {
            print_prompt();
        }
        fflush(stdout);

        // fgets: POSIX function for reading strings from a stream (https://pubs.opengroup.org/onlinepubs/9699919799/functions/fgets.html)
        if (!fgets(command, sizeof(command), input_stream)) {
            if (input_stream != stdin) {
                fclose(input_stream); // Close batch file stream
            } else {
                printf("\nExiting myshell...\n"); // Handle EOF (Ctrl+D)
                break;
            }
        }

        // Command parsing and execution
        int numArgs = parse_command(command, parsedArgs);
        if (numArgs == 0) continue; // Skip empty commands

        if (strcmp(parsedArgs[0], "quit") == 0) {
            should_run = 0; // Exit command loop
        } else {
            execute_command(parsedArgs, numArgs); // Execute parsed command
        }
    }

    return 0;
}

/*
STATEMENT OF NON-PLAGIARISM
    I hereby declare that I have written this submission and that it is all my own work. 
    I understand that my work may be checked for plagiarism and 
    that I would be penalized if it is found to be plagiarized.

    I understand that the University regards breaches of academic integrity and plagiarism as grave and serious. 
    I have read and understood the DCU Academic Integrity and Plagiarism Policy. I accept the penalties that may be 
    imposed should I engage in practice or practices that breach this policy.

    - Student Number: 22406966
    - Student Name: Ayden Jahola
    - Date: 24/03/2024
*/