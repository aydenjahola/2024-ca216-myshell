/*
* shell_commands.h
* Header file for shell_commands.c
* Includes function declarations for command execution and I/O redirection handling
*/

#ifndef SHELL_COMMANDS_H
#define SHELL_COMMANDS_H

// Function declarations
void handle_redirection(char *args[], int *numArgs);
void execute_command(char *args[], int numArgs);

#endif

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