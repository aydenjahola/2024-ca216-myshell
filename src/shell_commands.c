/*
    * This file contains the implementation of the built-in shell commands.
    * The built-in commands are:
    *  - cd: Change directory
    *  - clr: Clear the screen
    *  - dir: List files in a directory
    *  - environ: List environment variables
    *  - echo: Print arguments
    *  - help: Display help information
    *  - pause: Pause the shell
    *  - quit: Quit the shell
    * 
    * The execute_command function handles the execution of these commands.
    * It also handles I/O redirection and background execution of external commands. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <dirent.h>
#include "shell_commands.h"


// This function adjusts file descriptors to handle input (<) and output (>, >>) redirections.
// It iterates through the command arguments to find and process redirection symbols.
void handle_redirection(char *args[], int *numArgs) {
    for (int i = 0; i < *numArgs; ++i) {
        int fd; // File descriptor for the target file
        
        // Handle input redirection symbol '<'
        if (strcmp(args[i], "<") == 0) {
            // Open the specified input file for reading only
            fd = open(args[i + 1], O_RDONLY);
            if (fd < 0) {
                perror("Failed to open input file"); // Print error if the file cannot be opened
                exit(EXIT_FAILURE); // Exit the shell due to this critical error
            }
            dup2(fd, STDIN_FILENO); // Redirect standard input to the file
            close(fd); // Close the file descriptor as it's no longer needed directly
            
            // Remove the redirection symbol and the filename from the command arguments
            // This prevents them from being treated as regular arguments by the executing command
            memmove(&args[i], &args[i + 2], (*numArgs - i - 2) * sizeof(char *));
            *numArgs -= 2; // Adjust the count of arguments accordingly
            i--; // Adjust the loop index to account for the removed arguments
        }
        // Handle output redirection symbols '>' and '>>'
        else if (strcmp(args[i], ">") == 0 || strcmp(args[i], ">>") == 0) {
            // Open/Create the specified output file with appropriate flags for writing
            // 'O_CREAT' ensures the file is created if it does not exist.
            // 'O_TRUNC' truncates the file's length to 0 if it already exists (for '>').
            // 'O_APPEND' sets the write operation to append to the file (for '>>').
            fd = open(args[i + 1], O_WRONLY | O_CREAT | (strcmp(args[i], ">>") == 0 ? O_APPEND : O_TRUNC), 0644);
            if (fd < 0) {
                perror("Failed to open output file"); // Print error if the file cannot be opened/created
                exit(EXIT_FAILURE); // Exit the shell due to this critical error
            }
            dup2(fd, STDOUT_FILENO); // Redirect standard output to the file
            close(fd); // Close the file descriptor as it's no longer needed directly
            
            // Similar to input redirection, remove the symbols and filename from arguments
            memmove(&args[i], &args[i + 2], (*numArgs - i - 2) * sizeof(char *));
            *numArgs -= 2; // Adjust the count of arguments accordingly
            i--; // Adjust the loop index to account for the removed arguments
        }
    }
}


void execute_command(char *args[], int numArgs) {
    // Handle I/O redirection
    handle_redirection(args, &numArgs);

    // Check if the command should run in the background
    int runInBackground = 0; // Default to running in the foreground
    if (numArgs > 0 && strcmp(args[numArgs - 1], "&") == 0) { // Check if the last argument is '&'
        runInBackground = 1; // Set the flag to run in the background
        args[--numArgs] = NULL; // Remove the '&' and update the number of arguments
    }

    // Handle built-in commands
    if (strcmp(args[0], "cd") == 0) {  // Change directory
        if (numArgs == 1) { // No arguments provided, change to home directory
            char cwd[1024]; // Buffer to store the current working directory
            if (getcwd(cwd, sizeof(cwd)) != NULL) { // Get the current working directory
                printf("%s\n", cwd); // Print the current working directory
            } else { // Error handling for getcwd() failure
                perror("getcwd() error"); // Print an error message
            }
        } else { // Change to the specified directory
            if (chdir(args[1]) != 0) { // Attempt to change the directory
                perror("chdir() failed");  // Print an error message if chdir() fails
            } else { // Directory change successful
                setenv("PWD", args[1], 1); // Update PWD environment variable
            }
        }
    } else if (strcmp(args[0], "clr") == 0) { // Clear the screen
        printf("\033[H\033[J"); // ANSI escape code to clear screen
    } else if (strcmp(args[0], "dir") == 0) { // List files in a directory
        char *dir = numArgs > 1 ? args[1] : "."; // Default to current directory if no argument provided
        DIR *d; // Directory stream
        struct dirent *dirEntry; // Directory entry
        d = opendir(dir); // Open the directory
        if (d) { // Directory opened successfully
            while ((dirEntry = readdir(d)) != NULL) { // Read each directory entry
                printf("%s\n", dirEntry->d_name); // Print the name of the entry
            }
            closedir(d); // Close the directory stream
        } else { // Error handling for opendir() failure
            perror("opendir() failed"); // Print an error message
        } 
    } else if (strcmp(args[0], "environ") == 0) { // List environment variables
        extern char **environ; // External environment variables
        int i = 0; // Index for environment variables
        while (environ[i]) { // Iterate through the environment variables
            printf("%s\n", environ[i++]); // Print each environment variable
        }
    } else if (strcmp(args[0], "echo") == 0) { // Print arguments
        for (int i = 1; i < numArgs; i++) { // Iterate through the arguments
            printf("%s ", args[i]); // Print each argument
        }
        printf("\n"); // Print a newline at the end
    } else if (strcmp(args[0], "help") == 0) { // Display help information
        int pid = fork(); // Fork a child process
        if (pid == 0) { 
            // Child process
            execlp("more", "more", "../manual/readme.md", NULL); // Execute more command to display help information
            // If execlp returns, it must have failed
            perror("execlp failed"); // Print an error message
            exit(1);
        } else if (pid > 0) { 
            // Parent process
            wait(NULL); // Wait for child process to finish
        } else {
            // Fork failed
            perror("fork() failed");
        }
    } else if (strcmp(args[0], "pause") == 0) { // Pause the shell
        printf("Press Enter to continue..."); // Prompt the user to press Enter
        while (getchar() != '\n'); // Wait for the user to press Enter
    } else if (strcmp(args[0], "quit") == 0) { // Quit the shell
        exit(0); // Exit the shell with success status
    } else {
        // Handling external (system) commands with possible background execution
        int pid = fork(); // Fork a child process
        if (pid == -1) { // Fork failed
            perror("fork failed"); // Print an error message
            exit(EXIT_FAILURE); // Exit the shell due to this critical error
        } else if (pid == 0) { 
            // Child process: Attempt to execute the command
            if (execvp(args[0], args) == -1) { // Execute the command
                perror("execvp failed"); // Print an error message if execvp fails
                exit(EXIT_FAILURE); // Exit the child process due to this critical error
            }
        } else {
            // Parent process
            if (!runInBackground) { // Check if the command should run in the background
                int status; // Status of the child process
                waitpid(pid, &status, 0); // Wait for the child process to complete
            } else { // Running in the background
                printf("[Running in background] PID: %d\n", pid); // Print the background process ID
            }
        }
    }
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