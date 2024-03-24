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