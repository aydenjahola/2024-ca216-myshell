/*
* Utility functions for the shell
* Includes function declarations for command parsing
*/

#include "utility.h"
#include <string.h>

// Parses the command string into an array of arguments
int parse_command(char *command, char *args[]) {
    int i = 0; // Argument count 
    char *token = strtok(command, " \n"); // Tokenize the command string

    while (token != NULL) { // Iterate over tokens
        args[i++] = token; // Store the token in the arguments array
        token = strtok(NULL, " \n"); // Move to the next token
    }

    args[i] = NULL; // Set the last argument to NULL for execvp
    return i; // Return the number of arguments
}

// Online References for the parse_command function:
// - strtok: https://man7.org/linux/man-pages/man3/strtok.3.html alternative run: man 3 strtok
// The strtok function is used to tokenize a string based on delimiters. In this case, it's used
// to split a command string into individual arguments for processing. The tokens are then stored
// in an array of character pointers, making them suitable for functions like execvp that expect
// an array of arguments with a NULL terminator.

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